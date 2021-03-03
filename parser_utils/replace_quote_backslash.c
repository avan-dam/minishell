/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   replace_quote_backslash.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 20:06:59 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/03/02 19:22:43 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "string.h"

int	ft_correct_backslash(t_line *s, int i)
{
	char *tmp;// printf("VALUE OF S.STR FFS: %s\n", s->str);
	if (i == 0 && s->str[1] == '$')
	{
		// printf("GOES IN 1\n");
		return (i + 2);
	}
	if (s->str[i + 1] != '>' && s->str[i + 1] != '<'
		&& ((s->str[i + 1] == '`') || (s->str[i + 1] == '"')
			|| ((s->str[i + 1] == '\'') && (s->d % 2 == 0))
			|| s->str[i + 1] == '$' || s->str[i + 1] == '\\'))
	{
		// printf("GOES IN 2\n");
		ft_memmove(&s->str[i], &s->str[i + 1], ft_strlen(s->str) - i);
		if (s->str[i] != '\0' && ((s->str[i] == '$'
					&& ((i == 0) || ((i > 0) && (s->str[i - 1] != '\\'))))
				|| s->str[i] == '\'' || s->str[i] == '"'))
			i++;
	}
	else if ((s->s % 2 == 0) && (s->d % 2 == 0)
		&& (s->str[i + 1] != '>') && (s->str[i + 1] != '<'))
	{
		// printf("GOES IN 3\n");
		tmp = s->str;
		ft_memmove(&tmp[i], &tmp[i + 1], ft_strlen(tmp) - i);
		// free(tmp);
		// memmove(&s->str[i], &s->str[i + 1], ft_strlen(s->str) - i);
	}
	// printf("VALUE OF S.STR FFS AFTER: %s\n", s->str);
	return (i);
}

static int	ft_single_quotes(t_line *s, int i)
{
	if (s->d % 2 == 1)
	{
		if ((s->str[i + 1] == '\\') || ((s->str[i + 1] == '"')
					&& (s->d % 2 == 1)) || (i + 2 == (int)ft_strlen(s->str)))
			return (i);
		return (i + 2);
	}
	ft_memmove(&s->str[i], &s->str[i + 1], ft_strlen(s->str) - i);
	if (i != 0)
		i--;
	s->s++;
	if (s->str[i] == '\\' && s->d % 2 == 0 && s->str[i + 1] == '$')
	{
		ft_memmove(&s->str[i], &s->str[i + 1], ft_strlen(s->str) - i);
		i++;
	}
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

int	ft_replace_quotes(t_line *s, int i)
{
	if (s->str[i] == '\'')
		i = ft_single_quotes(s, i);
	else if (s->str[i] == '"')
	{
		ft_memmove(&s->str[i], &s->str[i + 1], ft_strlen(s->str) - i);
		if (i != 0)
			i--;
		if (s->s % 2 == 0)
			s->d++;
	}
	return (i);
}
