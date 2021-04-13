/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 16:10:48 by salbregh      #+#    #+#                 */
/*   Updated: 2021/04/13 10:42:00 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL || ft_strcmp("", s) == 0)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}
