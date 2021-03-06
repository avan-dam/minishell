/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   replace_quote_backslash.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 20:06:59 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/04/15 16:05:14 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	backslash_i_val(t_line *s, int i)
{
	if (s->str[i] == '\'' && s->str[i + 1] != ' ')
		i++;
	if (s->str[i] != '"' && (i == 0
			|| s->str[i - 1] != ' ' || s->str[i - 1] != '"'))
		i++;
	return (i);
}

int	ft_correct_backslash(t_line *s, int i)
{
	if (s->str[i + 1] == '>' || s->str[i + 1] == '<'
		|| (s->str[i + 1] == '~' && s->d % 2 == 1))
	{
		if (s->str[i + 2] == '"' || s->str[i + 2] == '\'')
			return (i + 1);
		return (i + 2);
	}
	if (s->str[i + 1] != '>' && s->str[i + 1] != '<'
		&& ((s->str[i + 1] == '`') || (s->str[i + 1] == '~')
			|| (s->str[i + 1] == '"') || ((s->str[i + 1] == '\'')
				&& (s->d % 2 == 0)) || s->str[i + 1] == '$'
			|| s->str[i + 1] == '\\'))
	{
		ft_memmove(&s->str[i], &s->str[i + 1], ft_strlen(s->str) - i);
		if (s->str[i] != '\0' && ((s->str[i] == '$'
					&& ((i == 0) || ((i > 0) && (s->str[i - 1] != '\\'))))
				|| s->str[i] == '\'' || s->str[i] == '"' || s->str[i] == '~'))
			i = backslash_i_val(s, i);
		remove_space_end(s, i);
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
		if ((s->str[i + 1] == '\\') || (s->str[i + 1] == '$')
			|| ((s->str[i + 1] == '"') && (s->d % 2 == 1))
			|| (i + 2 == (int)ft_strlen(s->str)))
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
	if ((nb_str(s->str, '>') != 0 || nb_str(s->str, '<') != 0)
		&& (j != 6 && j != 9 && j != 8 && j != 7 && j != 5))
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
		if (i == (int)ft_strlen(s->str))
			i--;
		if (s->s % 2 == 0)
			s->d++;
		if (i == -1 && (ft_strlen(s->str) == 1 || ft_strlen(s->str) == 0))
			i++;
	}
	return (i);
}

int	ft_replace_tilda(t_line *s, int i, t_mini *mini)
{
	char	*start;
	char	*end;
	int		ret;

	if (s->str[i + 1] == ' ' || s->str[i + 1] == '\0' || s->str[i + 1] == '/')
	{
		ft_memmove(&s->str[i], &s->str[i + 1], ft_strlen(s->str) - i);
		end = ft_substr(s->str, i, ft_strlen(s->str) - i);
		start = mini->home;
		ret = i + ft_strlen(start);
		free(s->str);
		s->str = ft_strjoin(start, end);
		free(end);
		if (s->str[ret] == '\\' || s->str[ret] == ' ')
			ret++;
		ret--;
		return (ret);
	}
	return (i + 1);
}
