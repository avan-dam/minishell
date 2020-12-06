/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 16:09:58 by salbregh      #+#    #+#                 */
/*   Updated: 2020/11/15 16:09:59 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(s);
	if ((char)c == '\0')
		return ((char *)&s[len]);
	while (i < len)
	{
		if (s[i] == (char)c)
			return ((char*)&s[i]);
		i++;
	}
	return (0);
}
