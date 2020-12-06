/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 16:11:11 by salbregh      #+#    #+#                 */
/*   Updated: 2020/11/15 16:11:12 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*end;

	end = (char *)s + ft_strlen(s);
	while (*end != c)
	{
		if (end == s)
			return (NULL);
		end--;
	}
	return (end);
}
