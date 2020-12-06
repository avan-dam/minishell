/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 16:06:50 by salbregh      #+#    #+#                 */
/*   Updated: 2020/11/30 19:10:52 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	check_atoi(unsigned long int result, const char *str, int neg)
{
	while (*str != '\0' && *str > 47 && *str < 58)
	{
		if (result >= 922337203685477580 && (*str - '0') < '7' && (neg == 1))
			return (-1);
		if (result >= 922337203685477580 && (*str - '0') < '8' && (neg == -1))
			return (0);
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result);
}

intmax_t		ft_atoi(const char *str)
{
	intmax_t	result;
	int			neg;

	result = 0;
	neg = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+')
	{
		str++;
		if (*str == '-' || *str == '+')
			return (0);
	}
	if (*str == '-')
	{
		neg = -1;
		str++;
		if (*str == '-' || *str == '+')
			return (0);
	}
	result = (check_atoi(result, str, neg));
	return (result * neg);
}
