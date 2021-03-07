/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 16:11:06 by salbregh      #+#    #+#                 */
/*   Updated: 2020/11/15 16:11:06 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	while ((j < ft_strlen(haystack)) && (j < len))
	{
		while (haystack[i + j] == needle[i] && (i + j) < len)
		{
			if (needle[i + 1] == '\0')
				return ((char *)&haystack[j]);
			i++;
		}
		i = 0;
		j++;
	}
	return (0);
}
