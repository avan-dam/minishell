/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   replace_dolla.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 20:04:37 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/02/16 20:16:48 by ambervandam   ########   odam.nl         */
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
			return (ft_strdup(tlist->var2));
		tlist = tlist->next;
	}
	return (ft_strdup(""));
}

static int	change_var(char *start, char *end, char *oldvar, t_line *s, t_mini *mini)
{
	char	*newvar;
	int		retval;

	if (start[ft_len(start) - 1] == 39 && end[0] == 39 && ft_len(end) > 1)
	{
		if (end[1] == '"')
			ft_memmove(&end[1], &end[2], ft_strlen(end) - 1);
	}
	newvar = ft_check_envar(mini, oldvar);
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

static int	find_start_end_old(int j, int i, char *str, t_line *s, t_mini *mini)
{
	char	*start;
	char	*oldvar;
	char	*end;

	oldvar = ft_substr(str, j, i - j);
	start = ft_substr(str, 0, j - 1);
	end = ft_substr(str, i, ft_strlen(str) - i);
	return (change_var(start, end, oldvar, s, mini));
}

int			ft_find_dolla(char *str, int i, t_mini *mini, t_line *s)
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
	return (find_start_end_old(j, i, str, s, mini));
}
