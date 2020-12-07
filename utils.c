/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/04 12:06:37 by ambervandam   #+#    #+#                 */
/*   Updated: 2020/12/07 08:39:53 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	write(1, s, ft_strlen(s));
}

int		ft_strchr_numb(const char *s, int c)
{
	int		length;
	int		i;

	i = 0;
	length = ft_strlen(s);
	if ((char)c == '\0')
		return (length);
	while (i < length)
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (0);
}
