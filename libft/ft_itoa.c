/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 16:08:33 by salbregh      #+#    #+#                 */
/*   Updated: 2020/11/15 16:08:34 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len_itoa(int n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n >= 10)
	{
		len++;
		n = n / 10;
	}
	len++;
	return (len);
}

static void	ft_fill_array(char *str, int n, int len)
{
	int i;

	i = 0;
	str[len] = '\0';
	if (n < 0)
	{
		str[i] = '-';
		i++;
		n = -n;
	}
	while ((len - 1) >= i)
	{
		str[len - 1] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
}

char		*ft_itoa(int n)
{
	int		len;
	char	*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_len_itoa(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (0);
	ft_fill_array(str, n, len);
	return (str);
}
