/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   replace_dolla.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 20:04:37 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/03/15 14:18:26 by ambervandam   ########   odam.nl         */
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

static char	*find_newvar(char *oldvar, char *start, char *end, t_mini *mini)
{
	char	*newvar;

	(void)start;
	// if (start[ft_len(start) - 1] == 39 && end[0] == 39 && ft_len(end) > 1)
	// {
	// 	if (end[1] == '"')
	// 		ft_memmove(&end[1], &end[2], ft_strlen(end) - 1);
	// }
	newvar = ft_check_envar(mini, oldvar);
	if (ft_strcmp(oldvar, "") == 0 && end[0] != '\'' && end[0] != '"')
	{
		free(newvar);
		newvar = ft_strdup("$");
	}
	return (newvar);
}

static int	dolla_while_checker(char *s, int i)
{
	if (s[i] != '\0' && s[i] != '$' && s[i] != '-' && s[i] != '=' && s[i]
		!= ' ' && s[i] != '\'' && s[i] != '"' && s[i] != '\\' && s[i] != '/'
		&& s[i] != '%' && s[i] != '*')
		return (1);
	return (0);
}

static int	ft_len_replace_dolla(int j, int i, char *s, int k)
{
	while (dolla_while_checker(s, i) == 1)
	{
		if (s[i] == '@' || s[j] == '#' || s[i] == '#')
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

int	ft_find_dolla(int i, int j, t_mini *mini, t_line *s)
{
	char	*oldvar;
	char	*start;
	char	*end;
	int		retval;
	char	*newvar;

	// printf("oin replace dollas->str is[%s]\n", s->str);
	i = ft_len_replace_dolla(j, i, s->str, 0);
	if (s->str[j] == '*')
		i++;
	if (s->str[i - 1] == '"')
		return (0);
	// printf("MID replace dollas->str is[%s]\n", s->str);
	oldvar = ft_substr(s->str, j, i - j);
	start = ft_substr(s->str, 0, j - 1);
	end = ft_substr(s->str, i, ft_strlen(s->str) - i);
	// printf("end is [%s]\n", end);
	newvar = find_newvar(oldvar, start, end, mini);
	// printf("old is [%s] new is [%s] start is [%s] end is [%s]\n", oldvar, newvar, start, end);
	if (ft_strcmp(oldvar, "") == 0
		&& (start[ft_strlen(start)] == '"' || s->d % 2 == 1) && end[0] == '"')
	{
		free(newvar);
		newvar = ft_strdup("$");
	}
	// printf("old is [%s] new is [%s] start is [%s] end is [%s]\n", oldvar, newvar, start, end);
	free(oldvar);
	retval = ft_len(newvar) - 1;
	s->str = ft_strjoin_three(start, newvar, end);
	// printf("OUT replace dollas->str is[%s]\n", s->str);
	return (retval);
}
