/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   replace_dolla.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/07 16:29:41 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/02/04 14:18:38 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	ft_find_dolla(char *line, int i, t_mini *mini, t_line *s)
{
	int		j;
	char	*start;
	char	*oldvar;
	char	*newvar;
	char	*end;
	int		k;

	j = i;
	while (line[i] != '\0' && line[i] != '$' && \
	line[i] != '-' && line[i] != '=' && line[i] != ' ' && line[i] != '\'' \
	&& line[i] != '"' && line[i] != '\\' && line[i] != '/' && line[i] != '%' ) // took out && '*" for echo "$2$*""
	{	
		if (line[i] == '@' || line[i] == '#')
		{
			i++;
			break ;
		}
		if (line[i] >= '0' && line[i] <= '9' && line[j + 1] >= '0' && line[i] <= '9')
		{
			k = i;
			while (line[i] >= '0' && line[i] <= '9')
				i++; 
			if (line[i] == '\0' && k != j)
				break ;
			if (k == j)
			{	
				i = k + 1;
				break ;
			}
			i = k;
		}
		i++;
	}
	if (line[i - 1] == '"')
		return (0);
	oldvar = ft_substr(line, j, i - j);
	start = ft_substr(line, 0, j - 1);
	end = ft_substr(line, i, ft_strlen(line) - i);
	if (start[ft_len(start) - 1] == 39 && end[0] == 39 && ft_len(end) > 1)
	{
		if (end[1] == '"')
			ft_memmove(&end[1], &end[2], ft_strlen(end) - 1);
	}
	newvar = ft_check_var_tlist(mini, oldvar);
	if (ft_strcmp(oldvar, "#") == 0)
		newvar = ft_strdup("0");
	// printf("start[%s] end[%s] oldbvar[%s] newvar[%s]\n", start, end, oldvar, newvar);
	if (ft_strcmp(oldvar, "") == 0 && end[0] != '\'' && end[0] != '"')
		newvar = ft_strdup("$");
	if (ft_strcmp(oldvar, "") == 0 && (start[ft_strlen(start)] == '"' || s->d % 2 == 1) && end[0] == '"')
		newvar = ft_strdup("$");
	s->line = ft_strjoin_three(start, newvar, end);
	free(oldvar);
	return (ft_len(newvar) - 1);
}

static int 			ft_check_backslash(t_line *s, int i)
{
	// printf("in backslash function with s->line[i]%c s->line[i + 1]%c s->s%d s->d%d\n", s->line[i], s->line[i + 1], s->s, s->d);
	if (((s->line[i + 1] == '`') || (s->line[i + 1] == '"') || ((s->line[i + 1] == '\'') && (s->d % 2 == 0))|| s->line[i + 1] == '$'|| s->line[i + 1] == '\\') && s->line[i + 1] != '>' && s->line[i + 1] != '<')
	{
		ft_memmove(&s->line[i], &s->line[i+1], ft_strlen(s->line) - i);
		if (s->line[i] != '\0' && ((s->line[i] == '$' && ((i == 0) || ((i >0) && (s->line[i - 1] != '\\')))) || s->line[i] == '\''||(s->line[i] == '\\')|| s->line[i] == '"'))
				i++;
	}
	else if ((s->s % 2 == 0) && (s->d % 2 == 0) && (s->line[i + 1] != '>') && (s->line[i + 1] != '<'))
		ft_memmove(&s->line[i], &s->line[i+1], ft_strlen(s->line) - i);
	return (i);
}

static int		ft_double_quotes(t_line *s, int i)
{
	// printf("in double wxith line %s and t %d\n", s->line, s->d);
	ft_memmove(&s->line[i], &s->line[i+1], ft_strlen(s->line) - i);
	i--;
	if (s->s % 2 == 0)
		s->d++;
	// printf("out double wxith line %s and t %d line[i]\n", s->line, s->d);
	return (i);
}

static int		ft_single_quotes(t_line *s, int i)
{
	// printf("in single with line %s and t %d i is %d and char is %c \n", s->line, s->d, i, s->line[i]);
	// if inside double quotes we keep the single quotes and then covert
	if (s->d % 2 == 1)
	{
		if ((s->line[i + 1] == '\\') || (i + 2 == (int)ft_strlen(s->line)))
			return (i);
		return (i + 1);
	}
	// remove single quotes and print exactly what is inside without changing
	ft_memmove(&s->line[i], &s->line[i+1], ft_strlen(s->line) - i);
	i--;
	s->s++;
	if (s->line[i] == '\\' && s->d % 2 == 0)
	{
		if (s->line[i + 1] == '$')
		{
			ft_memmove(&s->line[i], &s->line[i+1], ft_strlen(s->line) - i);
			i++;
		}
	}
	while ((s->line[i] != '\'') && (s->line[i] != '\0'))
		i++;
	if (s->line[i] == '\'')
	{
		ft_memmove(&s->line[i], &s->line[i+1], ft_strlen(s->line) - i);
		i--;
		s->s++;
	}
	return (i);
}

static char		*ft_check_quotes_in_order(t_line *s, t_mini *mini, int j, char *line)
{
	int i;
	int backslash; //number of backslash at end

	backslash = 0;
	i = (int)ft_strlen(line) - 1;
	if (line[i] == '\\')
	{
		while (i >= 0)
		{
			if (line[i] == '\\')
				backslash++;
			i--;
		}
	}
	if ((((line[i] == '<') || (line[i] == '>') )&& line[i - 1] != '\\')&& (j == 0))
	{
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", mini->stderr);
		mini->exit = 258;
		return (NULL);
	}
	if (s->s % 2 != 0 || s->d % 2 != 0 || backslash % 2 != 0)
	{
		if (j == 0)
		{
			ft_putstr_fd("minishell does not support multiline quotes\n", mini->stderr);
			mini->exit = 2;
		}
		if (j != 2)
			return (NULL);
	}
	return (s->line);
}

void		ft_exit_status_replace(t_line *s, int i, t_mini *mini)
{
	char	*start;
	char	*middle;
	char	*end;

	ft_memmove(&s->line[i + 1], &s->line[i + 2], ft_strlen(s->line) - (i + 1));
	i--;
	ft_memmove(&s->line[i + 1], &s->line[i + 2], ft_strlen(s->line) - (i + 1));
	middle = ft_itoa(mini->exit);
	start = ft_substr(s->line, 0, i + 1);
	end = ft_substr(s->line, i + 1, ft_strlen(s->line) - i - 1);
	s->line = ft_strjoin_three(start, middle, end);
}

// CANNOT DIVIDE ON SEMI COLON IF THE THE SEMICOLON IS WITHIN QUOTES!!
char			*ft_check_dolla_quotes(char *line, t_mini *mini, int i, int j)
{
	t_line	s;

	// printf("line checking for is [%s]\n", line);
	if (line == NULL || ft_strcmp(line, "") == 0)
		return (NULL);
	ft_memset(&s, 0, sizeof(t_line));
	s.line = ft_strdup(line);
	if ((numb_char(s.line, '>') != 0 || numb_char(s.line, '<') != 0) && j != 2)
		return (s.line);
	while (s.line[i] != '\0')
	{
		// printf("line [%s] char is line->i[%c] s.d%d s.s%d\n", s.line, s.line[i], s.d, s.s);
		if (s.line[i] == '\\' && numb_char(s.line, '>') == 0 && numb_char(s.line, '<') == 0)
			i = ft_check_backslash(&s, i);
		if (s.line[i] == '\'')
			i = ft_single_quotes(&s, i);
		else if (s.line[i] == '"')
			i = ft_double_quotes(&s, i);
		else if ((s.line[i] == '$') && (s.line[i + 1] != '/') && \
		(s.line[i + 1] != '\\') && (s.line[i + 1] != '\0') && (s.line[i + 1] != '?'))
			i = i + ft_find_dolla(s.line, i + 1, mini, &s);
		else if (s.line[i] == '$' && s.line[i + 1] == '?' && (s.d == 0 || s.d % 2 == 1) && (s.s == 0 ||s.s % 2 == 0))
			ft_exit_status_replace(&s, i, mini);
		if (s.line[i] != '\0')
			i++;
	}
	// s.line = ft_strtrim(s.line, " ");
	// printf("ending woo if no error leaving with [%s]\n", s.line);
	return (ft_check_quotes_in_order(&s, mini, j, line));
}
