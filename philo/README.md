# Dining Philosophers Simulation

This project implements the classic Dining Philosophers problem using POSIX threads and mutexes. The code models each philosopher as an independent thread that cycles through **thinking → taking sticks → eating → sleeping** while avoiding deadlocks and detecting starvation.

---

## High-level architecture

| Component | Responsibility |
|-----------|----------------|
| `main.c` | Parses CLI arguments, coordinates initialization, launch, termination, and cleanup. |
| `initialization.c` | Allocates philosophers and stick mutexes, prepares global synchronisation primitives. |
| `simulation_runner.c` | Spawns the philosopher threads, starts monitoring threads, and joins everything on shutdown. |
| `philosopher_actions.c` | Contains the philosopher Lifecycle routine and helper actions (taking sticks, eating, resting, thinking). |
| `monitoring.c` | Supervises philosophers for starvation and enforces the optional "max meals" end condition. |
| `synchronization.c` | Provides safe accessors/mutators for per-philosopher timing and meal counters. |
| `utilities.c` | Miscellaneous helpers: timestamp retrieval, event logging, argument parsing, and millisecond sleep. |
| `cleanup.c` | Tears down mutexes and releases allocated memory. |

Two core structs tie everything together:

* `t_thinker` – Represents a single philosopher, including identifiers, meal-tracking fields, dedicated mutexes, and the owning `t_simulation` pointer.
* `t_simulation` – Global simulation state: configuration (counts, timings), arrays of philosophers and stick mutexes, global control flags, and monitoring threads.

---

## Data structures

### `struct s_thinker`

| Field | Purpose |
|-------|---------|
| `philo_id` | 1-based index to identify the philosopher in logs and calculations. |
| `last_eatten` | Timestamp (ms) of the last time the philosopher started eating. Guarded by `eat_time_mutex`. |
| `times_eaten` | Number of completed meals. Guarded by `eat_count_mutex`. |
| `finished_eating` | Flag set when the philosopher reaches the optional `max_eat_count`. |
| `sim` | Back-reference to the owning `t_simulation`. |
| `life_thread` | `pthread_t` handle for the philosopher thread. |
| `eat_time_mutex` | Protects reads/writes of `last_eatten`. |
| `eat_count_mutex` | Protects reads/writes of `times_eaten`. |

### `struct s_simulation`

| Field | Purpose |
|-------|---------|
| `no_philo` | Number of philosophers (and sticks). |
| `death_timer` | Maximum allowed idle time (ms) before a philosopher is declared dead. |
| `time_to_eat` | Duration (ms) spent eating each cycle. |
| `time_to_sleep` | Duration (ms) spent sleeping each cycle. |
| `max_eat_count` | Optional limit for how many times each philosopher must eat before ending; `-1` disables the requirement. |
| `simulation_start` | Epoch timestamp (ms) captured when threads launch; used for relative logging. |
| `simulation_over` | Global flag signalling shutdown. Guarded by `end_simulation_mutex`. |
| `monitor_thread` | Thread handle for death monitoring. |
| `completion_thread` | Thread handle for the optional completion watcher. |
| `philos` | Array of `t_thinker` structs. |
| `end_simulation_mutex` | Serialises access to `simulation_over`. |
| `output_mutex` | Serialises console output to avoid interleaved logs. |
| `sticks` | Array of mutexes representing the shared sticks between philosophers. |

### `enum e_action`
Defines the set of loggable actions:

* `STICK` – Philosopher has picked up a stick.
* `EAT` – Philosopher is currently eating.
* `SLEEP` – Philosopher is sleeping.
* `THINK` – Philosopher is thinking.
* `DIE` – Philosopher died (starved).

---

## Control flow overview

1. **Argument parsing (`main.c`)**
   * `validate_and_parse_args` converts CLI parameters with `parse`, fills `t_simulation`, and validates ranges.
   * Edge case: if only one philosopher (`no_philo == 1`), `handle_single_philosopher` prints the inevitable death scenario and exits early.

2. **Initialization (`initialize_simulation`)**
   * `allocate_resources` allocates `philos` and `sticks` arrays.
   * `setup_utensils` initialises each stick mutex.
   * `setup_philosophers` populates per-philosopher fields and init their mutexes.
   * `setup_global_mutexes` creates the control/output mutexes.

3. **Simulation launch (`launch_simulation`)**
   * `create_philosopher_threads` records the common start time, seeds each philosopher’s `last_eatten` via `update_time`, and spawns threads executing `routine`.
   * `create_monitoring_threads` spawns the always-on `death_checker` and the optional `completion_watch` (only if `max_eat_count > 0`).

4. **Philosopher lifecycle (`philosopher_actions.c`)**
   * `routine` loops while the simulation is active and the philosopher hasn’t met `max_eat_count`.
   * Each iteration:
     1. `eatting` → orchestrates taking sticks, updates timers, logs, sleeps for `time_to_eat`, increments `times_eaten`, and drops sticks. If sticks couldn’t be acquired (e.g., shutdown triggered), it returns immediately.
     2. `take_rest` → logs and sleeps for `time_to_sleep`.
     3. `thinking` → logs and performs a brief pause (`usleep(1000)`) to stagger contention.
   * Stick handling:
     * `take_sticks` attempts to lock the two adjacent stick mutexes, using alternating lock order (left-first for odd IDs, right-first for even) to avoid deadlock.
     * It returns `false` if a shutdown occurs mid-acquisition, allowing `eatting` to skip `drop` safely.
     * `drop` unlocks the sticks in the opposite order, matching whichever pair the philosopher holds.

5. **Monitoring (`monitoring.c`)**
   * `death_checker` continuously scans philosophers. For each, it fetches `eat_time` (protected by `eat_time_mutex`) and compares with `death_timer`. On starvation: it calls `end_simulation`, logs `DIE`, and exits.
   * `completion_watch` runs when `max_eat_count > 0`. It uses `get_bite_count` to check if every philosopher reached the required meals; once true, it ends the simulation.
   * Both helpers respect `check_simulation_end`, which reads the shared termination flag under `end_simulation_mutex`.

6. **Termination (`terminate_simulation`)**
   * `pthread_join` synchronises with monitoring threads (if they were created) and every philosopher thread.
   * Errors propagate to the caller so `main` can handle cleanup gracefully.

7. **Cleanup (`cleanup_simulation`)**
   * Destroys per-philosopher mutexes, frees `philos`, destroys stick mutexes, frees `sticks`, and releases global mutexes.

Throughout the run, `logging` prints timestamped events while holding `output_mutex` to keep output human readable. Timestamps are derived from `get_current_time_ms` minus the common `simulation_start`. All sleep durations use `sleep` (backed by `usleep`) to stay in milliseconds.

---

## Function reference by module

### `main.c`
- `handle_single_philosopher` – Simulates the trivial single-philosopher case: picks one stick, waits `death_timer`, prints death.
- `validate_and_parse_args` – Validates argument count and ranges; fills `t_simulation` fields with parsed integers (using `parse`).
- `main` – Entry point orchestrating validation, initialization, launching, termination, and cleanup. Ensures cleanup even on failure paths.

### `initialization.c`
- `allocate_resources` – Allocates arrays for philosophers and sticks.
- `setup_utensils` – Initialises stick mutexes; unwinds partial success on failure.
- `setup_philosophers` – Sets base values (`philo_id`, counters) and initialises per-philosopher mutexes; cleans up on error.
- `setup_global_mutexes` – Initialises global control and logging mutexes.
- `initialize_simulation` – Top-level initializer combining the previous helpers, tracking failures to guarantee cleanup.

### `cleanup.c`
- `cleanup_simulation` – Destroys every mutex (per-philosopher and global) and frees allocated arrays.

### `simulation_runner.c`
- `create_philosopher_threads` – Records `simulation_start`, primes each philosopher’s timestamp via `update_time`, and spawns their threads.
- `create_monitoring_threads` – Spawns `death_checker` and optionally `completion_watch`; rolls back cleanly on failure.
- `launch_simulation` – High-level launcher calling the two helpers and handling error unwinding.
- `terminate_simulation` – Joins monitoring threads (if present) and every philosopher thread.

### `philosopher_actions.c`
- `take_sticks` – Locks the two adjacent sticks with alternating order to avoid deadlocks; returns `true` on success.
- `drop` – Unlocks sticks held by the philosopher in the correct order.
- `eatting` – Orchestrates acquiring sticks, logging, timekeeping, meal counting, and releasing sticks.
- `take_rest` – Logs and sleeps for `time_to_sleep`.
- `thinking` – Logs and performs a short pause to reduce contention.
- `routine` – Main philosopher loop combining the above helpers and enforcing `max_eat_count`.

### `monitoring.c`
- `check_simulation_end` – Thread-safe check of the global shutdown flag.
- `end_simulation` – Sets the shutdown flag under lock.
- `death_checker` – Watches philosophers for starvation and terminates the simulation upon death.
- `completion_watch` – Ends the simulation once every philosopher reaches `max_eat_count` (when enabled).

### `synchronization.c`
- `eat_time` – Reads `last_eatten` under mutex.
- `update_time` – Writes current time to `last_eatten` under mutex.
- `get_bite_count` – Reads `times_eaten` under mutex.
- `increment_bites` – Increments `times_eaten` under mutex.

### `utilities.c`
- `get_current_time_ms` – Returns current time in milliseconds.
- `logging` – Serialises console output, maps `t_action` to human-readable strings, and prints timestamped events.
- `parse` – Robust positive integer parser with overflow and formatting checks.
- `sleep` – Millisecond sleep wrapper using `usleep` (returns 0 for compatibility with standard `sleep` signature).

---

## Execution walkthrough

1. **Build**
   ```bash
   make
   ```

2. **Run**
   ```bash
   ./philo <philosophers> <die_time_ms> <eat_time_ms> <sleep_time_ms> [max_meals]
   ```
   *Example*: `./philo 4 310 200 100 3`

3. **Lifecycle**
   - `main` starts the simulation and spawns threads.
   - Each philosopher thread enters `routine` and cycles through thinking, taking sticks, eating, and sleeping until the simulation ends.
   - `death_checker` kills the simulation if any philosopher starves; `completion_watch` ends it when everyone has eaten enough (if `max_meals` supplied).
   - `terminate_simulation` joins all threads and triggers `cleanup_simulation`, ensuring every mutex is released.

---

## Notes for evaluation

* **Deadlock avoidance** – Alternating the acquisition order in `take_sticks` prevents circular wait.
* **Race protection** – Every shared state (`simulation_over`, per-philosopher timestamps/counts, console output) is protected by mutexes.
* **Graceful shutdown** – `take_sticks` returns `false` if shutdown begins mid-acquisition, preventing unlock errors and guaranteeing clean teardown.
* **Robust parsing** – `parse` rejects malformed inputs, leading spaces, negative numbers, and values beyond `INT_MAX`.
* **Extensibility** – The modular file layout and accessor helpers make it straightforward to add enhancements (e.g., new monitoring heuristics or alternate logging sinks).
