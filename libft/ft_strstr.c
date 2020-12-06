/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strstr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 16:11:16 by salbregh      #+#    #+#                 */
/*   Updated: 2020/11/15 16:11:17 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	while ((j < ft_strlen(haystack)))
	{
		while (haystack[i + j] == needle[i])
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
