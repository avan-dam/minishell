/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/04 12:06:37 by ambervandam   #+#    #+#                 */
/*   Updated: 2020/12/09 12:26:16 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	int i;
	
	if (s == NULL)
		return ;
	i = 0;
	while (i < (int)ft_strlen(s))
	{
		// so that if you type \ once nothing happens only 
		// if twice in a row
		if (s[i] == 92)
			i++;
		write(1, &s[i], 1);
		i++;
	}
}

// int		ft_strchr_numb(const char *s, int c)
// {
// 	int		length;
// 	int		i;

// 	i = 0;
// 	length = ft_strlen(s);
// 	if ((char)c == '\0')ho h
// 		return (length);
// 	while (i < length)
// 	{
// 		if (s[i] == (char)c)
// 			return (i);
// 		i++;
// 	}
// 	return (0);
// }
