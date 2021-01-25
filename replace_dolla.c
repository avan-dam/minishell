/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   replace_dolla.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/07 16:29:41 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/01/25 15:07:50 by ambervandam   ########   odam.nl         */
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

static int		ft_redir_n_dolla(char *line, int i)
{
	i--;
	while (i >=0)
	{
		if (line[i] == ' ')
			i--;
		else if (line[i] == '>' || line[i] == '<')
			return (-1);
		else
			return (1);
	}
	return (1);
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
	newvar = ft_check_var_tlist(mini, oldvar);
	if ((ft_redir_n_dolla(line, j - 1) != -1) || (ft_strcmp("", newvar) != 0))
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
	if (s->line[ft_strlen(s->line) - 1] == '"' && numb_char(s->line, '"') == 1)
	{
		s->t++;
		ft_memmove(&s->line[ft_strlen(s->line) - 1], &s->line[ft_strlen(s->line)], ft_strlen(s->line) - 1);
	}
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
		// printf("Check is t is %d o is %d line is %s\n", s.t, s.o, s.line);
		if (s.line[i] == '\\' && (s.o % 2 == 0) && (s.t % 2 == 0))
		{
			ft_memmove(&s.line[i], &s.line[i+1], ft_strlen(s.line) - 1);
			// is it -1 or -i
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
		else if (s.line[i] == '$' && s.line[i + 1] == '?' && (s.t == 0 || s.t % 2 == 1) && (s.o == 0 ||s.o % 2 == 0))
		{
			ft_memmove(&s.line[i + 1], &s.line[i + 2], ft_strlen(s.line) - (i + 1));
			i--;
			ft_memmove(&s.line[i + 1], &s.line[i + 2], ft_strlen(s.line) - (i + 1));
			i--;
            s.line = ft_string_insert(s.line, i + 1, ft_itoa(mini->exit));	
		}
		i++;
	}
	mini->singlequote = s.o;
	return (ft_check_quotes_in_order(&s, mini));
}
