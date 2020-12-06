/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 16:08:40 by salbregh      #+#    #+#                 */
/*   Updated: 2020/11/15 16:08:42 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	void			*ptr;
	unsigned char	*csrc;
	unsigned char	*cdst;

	csrc = (unsigned char *)src;
	cdst = (unsigned char *)dst;
	ptr = 0;
	i = 0;
	while (i < n)
	{
		cdst[i] = csrc[i];
		if (csrc[i] == (unsigned char)c)
		{
			ptr = cdst + i + 1;
			return (ptr);
		}
		i++;
	}
	return (ptr);
}
