/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   replace_specials.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/07 16:29:41 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/03/02 19:19:29 by salbregh      ########   odam.nl         */
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
	// printf("goes in with str: %s\n", str);
	// printf("value of s.str: %s\n", s->str);
	backslash = no_org_backslash(str, 0);
	if ((((str[i] == '<') || (str[i] == '>')) && str[i - 1] != '\\')
		&& (j == 0))
	{
		ft_printf_error(0, mini);
		return (NULL);
	}
	if (s->s % 2 != 0 || s->d % 2 != 0 || backslash % 2 != 0)
	{
		if (j == 0)
			ft_printf_error(1, mini);
		if (j != 2)
			return (NULL);
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
	free(s.str);
	s.str = ft_strdup(str);

	// printf("Goes in with: %s\n", str);
	if ((numb_char(s.str, '>') != 0 || numb_char(s.str, '<') != 0) && j != 2)
		return (s.str);
	while (s.str[i] != '\0')
	{
		if (s.str[i] == '\\' && numb_char(s.str, '>') == 0
			&& numb_char(s.str, '<') == 0)
		{
			// printf("Goes in 1 with: %s\n", str);
			// LEAK IN HERE
			// printf("value of s.str before: %s<\n", s.str);
			i = ft_correct_backslash(&s, i);
			// printf("value of s.str after: %s<\n", s.str);
			// free(str);
			// str = s.str;
		}
		if ((s.str[i] == '$') && (s.str[i + 1] != '/') && (s.str[i + 1] != '\\')
			&& (s.str[i + 1] != '\0') && (s.str[i + 1] != '?'))
		{
			// printf("Goes in 2 with: %s\n", str);
			i = i + ft_find_dolla(i + 1, i + 1, mini, &s);
		}
		else if ((s.str[i] == '\'') || (s.str[i] == '"'))
		{
			// printf("Goes in 3 with: %s\n", str);
			i = ft_replace_quotes(&s, i);
		}
		else if (s.str[i] == '$' && s.str[i + 1] == '?' && i != 0
			&& (s.d == 0 || s.d % 2 == 1) && (s.s == 0 || s.s % 2 == 0))
		{
			// printf("Goes in 4 with: %s\n", str);
			ft_exit_status_replace(&s, i, mini);
		}
		if (s.str[i] != '\0' || i == -1)
		{
			// printf("Goes in 5 with: %s\n", str);
			i++;
		}
	}
	
	// return (check_line_valid(&s, mini, j, str));
	if (check_line_valid(&s, mini, j, str) == NULL)
		return (NULL);
	return (s.str);
}
