#include "philo.h"

static int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static const char *check_number(const char *str)
{
	int	len;
	const char	*num;

	len = 0;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if(*str == '-')
		error_exit("NO negative\n");
	if(!is_digit(*str))
		error_exit("No digit");
	num = str;
	while (is_digit(*str++))
		++len;
	if (len > 10)
		error_exit("Too BIg");
	return num;
}

long	ft_atol(const char *str)
{
	printf("Entering atol\n");
	long	num;

	num = 0;
	str = check_number(str);
	while (is_digit(*str))
		num = (num * 10) + (*str++ - 48);
	if (num > INT_MAX)
		return FAILURE;
	printf("exiting atol\n");
	return (num);
}
