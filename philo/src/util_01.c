/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpandya <tpandya@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:37:51 by tpandya           #+#    #+#             */
/*   Updated: 2025/10/06 19:37:52 by tpandya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dining_philosophers.h"

static int	skip_spaces(const char *str, int i)
{
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (i);
}

static int	check_sign(const char *str, int *i)
{
	if (str[*i] == '+')
		(*i)++;
	else if (str[*i] == '-')
		return (0);
	return (1);
}

static int	parse_number(const char *str, int i, long *result)
{
	while (str[i] >= '0' && str[i] <= '9')
	{
		*result = *result * 10 + (str[i] - '0');
		if (*result > INT_MAX)
			return (-1);
		i++;
	}
	return (i);
}

int	parse(const char *str)
{
	long	result;
	int		i;

	if (!str || !str[0])
		return (-1);
	result = 0;
	i = skip_spaces(str, 0);
	if (!check_sign(str, &i) || str[i] < '0' || str[i] > '9')
		return (-1);
	i = parse_number(str, i, &result);
	if (i == -1)
		return (-1);
	i = skip_spaces(str, i);
	if (str[i] != '\0')
		return (-1);
	return ((int)result);
}
