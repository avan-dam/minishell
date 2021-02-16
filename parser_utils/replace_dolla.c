/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   replace_dolla.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/07 16:29:41 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/02/15 16:12:25 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char		*ft_check_envar(t_mini *mini, char *oldvar)
{
	t_list	*tlist;

	tlist = mini->env1;
	while (tlist != NULL)
	{
		if (ft_strcmp(tlist->var1, oldvar) == 0)
			return (ft_strdup(tlist->var2));
		tlist = tlist->next;
	}
	return (ft_strdup(""));
}

static int change_var(int j, int i, char *str, t_line *s, t_mini *mini)
{
	char	*start;
	char	*oldvar;
	char	*newvar;
	char	*end;
	int		retval;

	oldvar = ft_substr(str, j, i - j);
	start = ft_substr(str, 0, j - 1);
	end = ft_substr(str, i, ft_strlen(str) - i);
	if (start[ft_len(start) - 1] == 39 && end[0] == 39 && ft_len(end) > 1)
	{
		if (end[1] == '"')
			ft_memmove(&end[1], &end[2], ft_strlen(end) - 1);
	}
	newvar = ft_check_envar(mini, oldvar);
	if (ft_strcmp(oldvar, "#") == 0)
		newvar = ft_strdup("0");
	if (ft_strcmp(oldvar, "") == 0 && end[0] != '\'' && end[0] != '"')
		newvar = ft_strdup("$");
	if (ft_strcmp(oldvar, "") == 0 && (start[ft_strlen(start)] == '"'
	|| s->d % 2 == 1) && end[0] == '"')
		newvar = ft_strdup("$");
	retval = ft_len(newvar) - 1;
	s->str = ft_strjoin_three(start, newvar, end);
	free(oldvar);
	return (retval);
}

static int	ft_find_dolla(char *str, int i, t_mini *mini, t_line *s)
{
	int		j;
	int		k;

	j = i;
	while (str[i] != '\0' && str[i] != '$' && str[i] != '-' && str[i] != '=' &&
	str[i] != ' ' && str[i] != '\'' && str[i] != '"' && str[i] != '\\' &&
	str[i] != '/' && str[i] != '%' && str[i] != '*')
	{
		if (str[i] == '@' || str[j] == '#')
		{
			i++;
			break ;
		}
		if (str[i] == '#')
			break ;
		if (str[i] >= '0' && str[i] <= '9' &&
		str[j + 1] >= '0' && str[i] <= '9')
		{
			k = i;
			while (str[i] >= '0' && str[i] <= '9')
				i++;
			if (str[i] == '\0' && k != j)
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
	if (str[j] == '*')
		i++;
	if (str[i - 1] == '"')
		return (0);
	return (change_var(j, i, str, s, mini));
}

static int		ft_check_backslash(t_line *s, int i)
{
	if (i == 0 && s->str[1] == '$')
		return (i + 2);
	if (((s->str[i + 1] == '`') || (s->str[i + 1] == '"') ||
	((s->str[i + 1] == '\'') && (s->d % 2 == 0)) || s->str[i + 1] == '$' ||
	s->str[i + 1] == '\\') && s->str[i + 1] != '>' && s->str[i + 1] != '<')
	{
		ft_memmove(&s->str[i], &s->str[i + 1], ft_strlen(s->str) - i);
		if (s->str[i] != '\0' && ((s->str[i] == '$' && ((i == 0) ||
		((i > 0) && (s->str[i - 1] != '\\')))) ||
		s->str[i] == '\'' || s->str[i] == '"'))
			i++;
	}
	else if ((s->s % 2 == 0) && (s->d % 2 == 0)
	&& (s->str[i + 1] != '>') && (s->str[i + 1] != '<'))
		ft_memmove(&s->str[i], &s->str[i + 1], ft_strlen(s->str) - i);
	return (i);
}

static int		ft_double_quotes(t_line *s, int i)
{
	ft_memmove(&s->str[i], &s->str[i + 1], ft_strlen(s->str) - i);
	if (i != 0)
		i--;
	if (s->s % 2 == 0)
		s->d++;
	return (i);
}

static int		ft_single_quotes(t_line *s, int i)
{
	if (s->d % 2 == 1)
	{
		if ((s->str[i + 1] == '\\') || ((s->str[i + 1] == '"') &&
		(s->d % 2 == 1)) || (i + 2 == (int)ft_strlen(s->str)))
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

static char		*check_line_valid(t_line *s, t_mini *mini, int j, char *str)
{
	int i;
	int backslash;

	backslash = 0;
	i = (int)ft_strlen(str) - 1;
	if (str[i] == '\\')
	{
		while (i >= 0)
		{
			if (str[i] == '\\')
				backslash++;
			i--;
		}
	}
	if ((((str[i] == '<') || (str[i] == '>')) && str[i - 1] != '\\')
	&& (j == 0))
	{
		ft_putstr_fd("bash: syntax error near ", mini->stderr);
		ft_putstr_fd("unexpected token `newline'\n", mini->stderr);
		mini->exit = 258;
		return (NULL);
	}
	if (s->s % 2 != 0 || s->d % 2 != 0 || backslash % 2 != 0)
	{
		if (j == 0)
		{
			ft_putstr_fd("minishell does not ", mini->stderr);
			ft_putstr_fd("support multiline quotes\n", mini->stderr);
			mini->exit = 2;
		}
		if (j != 2)
			return (NULL);
	}
	s->s = 0;
	s->d = 0;
	// str = s->str;
	return (s->str);
}

void		ft_exit_status_replace(t_line *s, int i, t_mini *mini)
{
	char	*start;
	char	*middle;
	char	*end;

	ft_memmove(&s->str[i + 1], &s->str[i + 2], ft_strlen(s->str) - (i + 1));
	i--;
	ft_memmove(&s->str[i + 1], &s->str[i + 2], ft_strlen(s->str) - (i + 1));
	middle = ft_itoa(mini->exit);
	start = ft_substr(s->str, 0, i + 1);
	end = ft_substr(s->str, i + 1, ft_strlen(s->str) - i - 1);
	s->str = ft_strjoin_three(start, middle, end);
}

char			*check_tokens(char *str, t_mini *mini, int i, int j)
{
	t_line	s;

	if (str == NULL || ft_strcmp(str, "") == 0)
		return (NULL);
	ft_memset(&s, 0, sizeof(t_line));
	s.str = ft_strdup(str); // free this in some way
	if ((numb_char(s.str, '>') != 0 || numb_char(s.str, '<') != 0) && j != 2)
		return (s.str);
	while (s.str[i] != '\0')
	{
		if (s.str[i] == '\\' && numb_char(s.str, '>') == 0
		&& numb_char(s.str, '<') == 0)
			i = ft_check_backslash(&s, i);
		if (s.str[i] == '\'')
			i = ft_single_quotes(&s, i);
		else if (s.str[i] == '"')
			i = ft_double_quotes(&s, i);
		else if ((s.str[i] == '$') && (s.str[i + 1] != '/') && (s.str[i + 1] != '\\')
		&& (s.str[i + 1] != '\0') && (s.str[i + 1] != '?'))
			i = i + ft_find_dolla(s.str, i + 1, mini, &s);
		else if (s.str[i] == '$' && s.str[i + 1] == '?' && i != 0 &&
		(s.d == 0 || s.d % 2 == 1) && (s.s == 0 || s.s % 2 == 0))
			ft_exit_status_replace(&s, i, mini);
		if (s.str[i] != '\0' || i == -1)
			i++;
	}
	// printf("Leak in check_tokens\n");
	// system("leaks minishell");
	return (check_line_valid(&s, mini, j, s.str)); // maybe change s.str back to str
}
