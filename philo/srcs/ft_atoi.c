#include "philo.h"

static const char	*skip_spaces_and_sign(const char *str, int *sign)
{
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			*sign = -1;
		str++;
	}
	if (*str < '0' || *str > '9')
		return (NULL);
	return (str);
}

static int	parse_number(const char *str, int sign, long *out)
{
	long	result = 0;

	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		if (sign == 1 && (result > (LONG_MAX - (*str - '0')) / 10))
			return (0);
		if (sign == -1 && (-result < (LONG_MIN + (*str - '0')) / 10))
			return (0);

		result = result * 10 + (*str - '0');
		str++;
	}
	*out = result * sign;
	return (1);
}

int	ft_atol(const char *str, long *res)
{
	int	sign = 1;

	if (!str || !res)
		return (0);
	str = skip_spaces_and_sign(str, &sign);
	if (!str)
		return (0);
	if (!parse_number(str, sign, res))
		return (0);
	return (1);
}

