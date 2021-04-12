/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   replace_dolla.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 20:04:37 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/04/06 13:27:11 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_check_envar(t_mini *mini, char *oldvar)
{
	t_list	*tlist;

	tlist = mini->env1;
	if (ft_strcmp(oldvar, "#") == 0)
		return (ft_strdup("0"));
	while (tlist != NULL)
	{
		if (ft_strcmp(tlist->var1, oldvar) == 0)
		{
			if (tlist->var2 == NULL)
				return (NULL);
			return (ft_strdup(tlist->var2));
		}
		tlist = tlist->next;
	}
	return (ft_strdup(""));
}

static char	*find_newvar(char *oldvar, char *end, t_mini *mini)
{
	char	*newvar;
	char	*tempptr;

	newvar = ft_check_envar(mini, oldvar);
	tempptr = newvar;
	newvar = ft_strtrim_backslash(tempptr, ' ');
	free(tempptr);
	if (ft_strcmp(oldvar, "") == 0 && end[0] != '\'' && end[0] != '"')
	{
		free(newvar);
		newvar = ft_strdup("$");
	}
	return (newvar);
}

static int	ft_len_replace_dolla(int j, int i, char *s, int k)
{
	while (dolla_while_checker(s, i) == 1)
	{
		if (s[i] == '@' || s[j] == '#' || s[i] == '#'
			|| s[i] == ']' || s[i] == '[')
		{
			if (s[i] == '@' || s[j] == '#')
				i++;
			break ;
		}
		if (s[i] >= '0' && s[i] <= '9' && s[j + 1] >= '0' && s[i] <= '9')
		{
			k = i;
			while (s[i] >= '0' && s[i] <= '9')
				i++;
			if ((s[i] == '\0' && k != j) || (k == j))
			{
				if (k == j)
					i = k + 1;
				break ;
			}
			i = k;
		}
		i++;
	}
	return (i);
}

int	free_set_ret(char *oldvar, char *newvar)
{
	int	retval;

	free(oldvar);
	retval = 0;
	if (newvar)
		retval = ft_len(newvar) - 1;
	return (retval);
}

int	ft_find_dolla(int i, int j, t_mini *mini, t_line *s)
{
	char	*oldvar;
	char	*start;
	char	*end;
	int		retval;
	char	*newvar;

	i = ft_len_replace_dolla(j, i, s->str, 0);
	if (ft_extra_check_dolla(s, i, j) == 0)
		return (0);
	oldvar = ft_substr(s->str, j, i - j);
	start = ft_substr(s->str, 0, j - 1);
	end = ft_substr(s->str, i, ft_strlen(s->str) - i);
	newvar = find_newvar(oldvar, end, mini);
	if (ft_strcmp(oldvar, "") == 0 && (start[ft_strlen(start)] == '"'
			|| s->d % 2 == 1) && end[0] == '"')
	{
		free(newvar);
		newvar = ft_strdup("$");
	}
	retval = free_set_ret(oldvar, newvar);
	free(s->str);
	s->str = ft_strjoin_three(start, newvar, end);
	return (retval);
}
