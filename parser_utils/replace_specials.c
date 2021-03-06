/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   replace_specials.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/07 16:29:41 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/04/15 16:04:42 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static char	*check_line_valid(t_line *s, t_mini *mini, int j, char *str)
{
	int	backslash;

	backslash = no_org_backslash(str, 0);
	if (s->s % 2 != 0 || s->d % 2 != 0 || backslash % 2 != 0)
	{
		if (j == 0 || j == 7)
			ft_print_error(mini);
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
	free(s->str);
	s->str = ft_strjoin_three(start, middle, end);
}

static void	start_struct(t_line *s, char *str)
{
	ft_memset(s, 0, sizeof(t_line));
	s->str = ft_strdup(str);
}

char	*check_tokens(char *str, t_mini *mini, int i, int j)
{
	t_line	s;

	if (str == NULL || ft_strcmp(str, "") == 0)
		return (NULL);
	start_struct(&s, str);
	while (s.str[i] != '\0')
	{
		if (s.str[i] == '\\' && ((j == 7) || (j == 8) || (j == 5)
				|| (nb_str(s.str, '>') == 0 && nb_str(s.str, '<') == 0)))
			i = ft_correct_backslash(&s, i);
		else if ((s.str[i] == '$') && (s.str[i + 1] != '/')
			&& (s.str[i + 1] != '\\') && (s.str[i + 1] != '\0')
			&& (s.str[i + 1] != '?') && (j == 6 || j == 9))
			i = i + ft_find_dolla(i + 1, i + 1, mini, &s);
		else if ((s.str[i] == '\'') || (s.str[i] == '"'))
			i = ft_replace_quotes(&s, i, j);
		else if (s.str[i] == '~' && i == 0 && s.d % 2 == 0 && s.s == 0)
			i = ft_replace_tilda(&s, i, mini);
		else if (s.str[i] == '$' && s.str[i + 1] == '?'
			&& (s.d == 0 || s.d % 2 == 1) && (s.s == 0 || s.s % 2 == 0))
			ft_exit_status_replace(&s, i, mini);
		if (s.str[i] != '\0' || i == -1)
			i++;
	}
	return (check_line_valid(&s, mini, j, str));
}
