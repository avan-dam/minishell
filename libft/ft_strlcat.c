/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 16:10:32 by salbregh      #+#    #+#                 */
/*   Updated: 2020/11/15 16:10:34 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	d;
	size_t	s;

	i = 0;
	d = ft_strlen(dst);
	s = ft_strlen(src);
	if (dstsize == 0)
		return (s);
	if (d >= dstsize)
		return (s + dstsize);
	while (i < (dstsize - d - 1) && (src[i] != '\0'))
	{
		dst[d + i] = src[i];
		i++;
	}
	dst[i + d] = '\0';
	return (d + s);
}
