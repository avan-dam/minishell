/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 16:10:02 by salbregh      #+#    #+#                 */
/*   Updated: 2020/11/15 16:10:04 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = (char *)malloc(sizeof(*ptr) * (ft_strlen(s1) + 1));
	if (ptr == NULL)
		return (NULL);
	while (i <= ft_strlen(s1))
	{
		ptr[i] = s1[i];
		i++;
	}
	return ((char*)ptr);
}
