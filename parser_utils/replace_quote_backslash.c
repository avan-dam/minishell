/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   replace_quote_backslash.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 20:06:59 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/03/15 14:08:49 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_correct_backslash(t_line *s, int i)
{
	if (s->str[i + 1] == '>' || s->str[i + 1] == '<')
		return (i + 2);
	if (s->str[i + 1] != '>' && s->str[i + 1] != '<'
		&& ((s->str[i + 1] == '`') || (s->str[i + 1] == '"')
			|| ((s->str[i + 1] == '\'') && (s->d % 2 == 0))
			|| s->str[i + 1] == '$' || s->str[i + 1] == '\\'))
	{
		ft_memmove(&s->str[i], &s->str[i + 1], ft_strlen(s->str) - i);
		if (s->str[i] != '\0' && ((s->str[i] == '$'
					&& ((i == 0) || ((i > 0) && (s->str[i - 1] != '\\'))))
				|| s->str[i] == '\'' || s->str[i] == '"'))
		{
			// printf("in here\n");
			if (s->str[i] == '\'')
				i++;
			i++;
		}
	}
	else if ((s->s % 2 == 0) && (s->d % 2 == 0)
		&& (s->str[i + 1] != '>') && (s->str[i + 1] != '<'))
		ft_memmove(&s->str[i], &s->str[i + 1], ft_strlen(s->str) - i);
	return (i);
}

static int	ft_single_quotes(t_line *s, int i)
{
	if (s->d % 2 == 1)
	{
		// printf("in this s->str[i + 1][%c]\n", s->str[i + 1]);
		if ((s->str[i + 1] == '\\') || ((s->str[i + 1] == '"')
				&& (s->d % 2 == 1)) || (i + 2 == (int)ft_strlen(s->str)))
		{
			// printf("returning here\n");
			return (i);
		}
		if (s->str[i + 1] == '$') // add condition abocve
			return (i);
		return (i + 2);
	}
	ft_memmove(&s->str[i], &s->str[i + 1], ft_strlen(s->str) - i);
	if (i != 0)
		i--;
	s->s++;
	while ((s->str[i] != '\'') && (s->str[i] != '\0'))
		i++;
	if (s->str[i] == '\'')
	{
		ft_memmove(&s->str[i], &s->str[i + 1], ft_strlen(s->str) - i);
		i--;
		s->s++;
	}
	return (i);
}

int	ft_replace_quotes(t_line *s, int i, int j)
{
	// printf("in replace quotes with char[%c] s->str[%s]\n", s->str[i], s->str);
	if ((numb_char(s->str, '>') != 0 || numb_char(s->str, '<') != 0) && j != 4)
	{
		s->d++;
		return (i);
	}
	if (s->str[i] == '\'')
		i = ft_single_quotes(s, i);
	else if (s->str[i] == '"')
	{
		ft_memmove(&s->str[i], &s->str[i + 1], ft_strlen(s->str) - i);
		i--;
		if (s->s % 2 == 0)
			s->d++;
	}
	// while (i > (int)ft_strlen(s->str))
	// 	i--;
	// i--;
	// printf("OUT replace quotes with char[%c] s->str[%s] ft_stlen(s->str)(%zu) i is %d\n", s->str[i], s->str, ft_strlen(s->str), i);
	return (i);
}
