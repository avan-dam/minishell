/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   replace_specials.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/07 16:29:41 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/03/03 08:33:46 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	struct t_line contains line as it is being changed
**	and make sure that it is valid i.e. not multiline quotes
**	and contains the number of valid/registered single(s) quotes
**	and double(d)quotes
*/

static int	no_org_backslash(char *str, int backslash)
{
	int	i;

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
	return (backslash);
}

static void	ft_printf_error(int i, t_mini *mini)
{
	if (i == 0)
	{
		ft_putstr_fd("bash: syntax error near ", mini->stderr);
		ft_putstr_fd("unexpected token `newline'\n", mini->stderr);
		mini->exit = 258;
	}
	if (i == 1)
	{
		ft_putstr_fd("minishell does not ", mini->stderr);
		ft_putstr_fd("support multiline quotes\n", mini->stderr);
		mini->exit = 2;
	}
}

static char	*check_line_valid(t_line *s, t_mini *mini, int j, char *str)
{
	int	i;
	int	backslash;

	i = 0;
	backslash = no_org_backslash(str, 0);
	if ((((str[i] == '<') || (str[i] == '>')) && str[i - 1] != '\\')
		&& (j == 0))
	{
		ft_printf_error(0, mini);
		printf("here\n");
		if (s->str)
			free(s->str);
		return (NULL);
	}
	if (s->s % 2 != 0 || s->d % 2 != 0 || backslash % 2 != 0)
	{
		if (j == 0)
			ft_printf_error(1, mini);
		if (j != 2)
		{	
			if (s->str)
				free(s->str);
			return (NULL);
		}
	}
	s->s = 0;
	s->d = 0;
	return (s->str);
}

void	ft_exit_status_replace(t_line *s, int i, t_mini *mini)
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

char	*check_tokens(char *str, t_mini *mini, int i, int j)
{
	t_line	s;

	if (str == NULL || ft_strcmp(str, "") == 0)
		return (NULL);
	ft_memset(&s, 0, sizeof(t_line));
	s.str = ft_strdup(str);
	if ((numb_char(s.str, '>') != 0 || numb_char(s.str, '<') != 0) && j != 2)
		return (s.str);
	while (s.str[i] != '\0')
	{
		if (s.str[i] == '\\' && numb_char(s.str, '>') == 0
			&& numb_char(s.str, '<') == 0)
			i = ft_correct_backslash(&s, i);
		if ((s.str[i] == '$') && (s.str[i + 1] != '/') && (s.str[i + 1] != '\\')
			&& (s.str[i + 1] != '\0') && (s.str[i + 1] != '?'))
			i = i + ft_find_dolla(i + 1, i + 1, mini, &s);
		else if ((s.str[i] == '\'') || (s.str[i] == '"'))
			i = ft_replace_quotes(&s, i);
		else if (s.str[i] == '$' && s.str[i + 1] == '?' && i != 0
			&& (s.d == 0 || s.d % 2 == 1) && (s.s == 0 || s.s % 2 == 0))
			ft_exit_status_replace(&s, i, mini);
		if (s.str[i] != '\0' || i == -1)
			i++;
	}
	return (check_line_valid(&s, mini, j, str));
}
