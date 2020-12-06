/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 16:10:40 by salbregh      #+#    #+#                 */
/*   Updated: 2020/11/15 16:10:41 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	d;
	size_t	s;

	i = 0;
	if (src == NULL)
		return (0);
	if (dstsize == 0)
		return (ft_strlen(src));
	d = ft_strlen(dst);
	s = ft_strlen(src);
	while ((i < (dstsize - 1)) && ((i < (s - 1)) || (i < (d - 1))) && \
	(src[i] != '\0'))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (s);
}
