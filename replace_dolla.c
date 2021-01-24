/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   replace_dolla.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/07 16:29:41 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/01/24 11:16:32 by Amber         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		line_replaced(char *start, char *newvar, char *end, t_line *s)
{
	char	*temp;
	char	*newline;

	temp = ft_strjoin(start, newvar);
	newline = ft_strjoin(temp, end);
	s->line = newline;
	s->k = ft_len(newvar) - 1;
	return ;
}

static char		*ft_check_var_tlist(t_mini *mini, char *oldvar)
{
	t_list	*tlist;

	// looking through environmental variables to see if needs to be replace
	// so only loop through env1 tlist not run tlist
	tlist = mini->env1;
	while (tlist != NULL)
	{
		if (ft_strcmp(tlist->var1, oldvar) == 0)
			return (tlist->var2);
		tlist = tlist->next;
	}
	return (ft_strdup(""));
}

static t_line	*ft_find_dolla(char *line, int i, t_mini *mini, t_line *s)
{
	int		j;
	char	*start;
	char	*oldvar;
	char	*newvar;
	char	*end;

	j = i;
	while (line[i] != '\0' && line[i] != '#' && line[i] != '$' && \
	line[i] != '-' && line[i] != '=' && line[i] != ' ' && line[i] != 39 \
	&& line[i] != '"')
		i++;
	if (line[i - 1] == '"')
		return (NULL);
	oldvar = ft_substr(line, j, i - j);
	start = ft_substr(line, 0, j - 1);
	end = ft_substr(line, i, ft_strlen(line) - i);
	if (start[ft_len(start) - 1] == 39 && end[0] == 39 && ft_len(end) > 1)
	{
		if (end[1] == '"')
			ft_memmove(&end[1], &end[2], ft_strlen(end) - 1);
	}
	newvar = ft_check_var_tlist(mini, oldvar);
	line_replaced(start, newvar, end, s);
	return (s);
}

static void		set_tline(t_line *s, char *line)
{
	s->line = ft_strdup(line);
	// free line?
	s->o = 0;
	s->t = 0;
	s->k = 0;
}

static int		ft_double_quotes(t_line *s, int i)
{
	ft_memmove(&s->line[i], &s->line[i+1], ft_strlen(s->line) - i);
	i--;
	// if going wrong remove if statement here and just t++ always
	if (s->o % 2 == 0)
		s->t++;
	return (i);
}

static int		ft_single_quotes(t_line *s, int i)
{
	// printf("in single with line %s and t %d\n", s->line, s->t);
	// if inside double quotes we keep the single quotes and then covert
	if (s->t % 2 == 1)
	{
		// printf("i is %d an strlen is %zu ", i , ft_strlen(s->line));
		if (i + 2 == (int)ft_strlen(s->line))
			return (i);
		return (i + 1);
	}
	// remove single quotes and print exactly what is inside without changing
	ft_memmove(&s->line[i], &s->line[i+1], ft_strlen(s->line) - i);
	i--;
	s->o++;
	while ((s->line[i] != '\'') && (s->line[i] != '\0'))
		i++;
	if (s->line[i] == '\'')
	{
		ft_memmove(&s->line[i], &s->line[i+1], ft_strlen(s->line) - i);
		i--;
		s->o++;
	}
	return (i);
}

static char		*ft_check_quotes_in_order(t_line *s, t_mini *mini)
{
	// printf("Check is t is %d o is %d line is %s\n", s->t, s->o, s->line);
	if (s->o % 2 != 0 || s->t % 2 != 0)
	{
		// is this stdout or stderror
		ft_putstr_fd("minishell does not support multiline quotes\n", mini->stdout);
		return (NULL);
	}
	return (s->line);
}

char			*ft_check_dolla_quotes(char *line, t_mini *mini, int i)
{
	t_line	s;

	if (line == NULL)
		return (NULL);
	set_tline(&s, line);
	while (s.line[i] != '\0')
	{
		if (s.line[i] == '\\' && (s.o % 2 == 0) && (s.t % 2 == 0))
		{
			ft_memmove(&s.line[i], &s.line[i+1], ft_strlen(s.line) - 1);
			i--;
		}
		if (s.line[i] == '\'')
			i = ft_single_quotes(&s, i);
		else if (s.line[i] == '"')
			i = ft_double_quotes(&s, i);
		else if ((s.line[i] == '$') && (s.line[i + 1] != '/') && \
		(s.line[i + 1] != '\\') && (s.line[i + 1] != '\0') && (s.line[i + 1] != '?'))
		{
			ft_find_dolla(s.line, i + 1, mini, &s);
			i = i + s.k;
		}
		i++;
	}
	return (ft_check_quotes_in_order(&s, mini));
}
