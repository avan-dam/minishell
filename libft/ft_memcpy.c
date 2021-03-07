/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 16:09:06 by salbregh      #+#    #+#                 */
/*   Updated: 2020/11/15 16:09:07 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*csrc;
	unsigned char	*cdst;
	size_t			i;

	csrc = (unsigned char *)src;
	cdst = (unsigned char *)dst;
	i = 0;
	if (n == 0 || (cdst == 0 && csrc == 0))
		return (dst);
	while (i < n)
	{
		cdst[i] = csrc[i];
		i++;
	}
	return (dst);
}
