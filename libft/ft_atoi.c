/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-dam <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/06 13:03:21 by avan-dam      #+#    #+#                 */
/*   Updated: 2021/03/23 21:16:58 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

static long int	ft_check_atoi(unsigned long int res, const char *str, int neg)
{
	while (*str != '\0' && *str > 47 && *str < 58)
	{
		res = res * 10 + (*str - '0');
		str++;
		if (res > 9223372036854775807)
		{
			if (neg == 1)
				return (-1);
			return (0);
		}
	}
	return (res);
}

int	ft_atoi(const char *str)
{
	unsigned long int	result;
	int					neg;

	result = 0;
	neg = 1;
	while (*str == 32 || *str == 9 || *str == 10
		|| *str == 11 || *str == 12 || *str == 13)
		str++;
	if (*str == '-')
	{
		neg = -1;
		str++;
		if (*str == '+' || *str == '-')
			return (0);
	}
	if (*str == '+')
	{
		str++;
		if (*str == '+' || *str == '-')
			return (0);
	}
	result = (ft_check_atoi(result, str, neg));
	return (neg * result);
}
