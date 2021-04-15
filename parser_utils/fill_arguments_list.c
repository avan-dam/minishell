/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fill_arguments_list.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/22 13:14:31 by salbregh      #+#    #+#                 */
/*   Updated: 2021/04/15 16:08:05 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_redir(t_mini *m, int j, char *result)
{
	if ((m->part[j] == '>' || m->part[j] == '<') && m->part[j + 1] != '>'
		&& m->part[j + 1] != '<' && result != NULL)
	{
		if ((m->part[j + 1] == '"') || (m->part[j + 1] == '\''))
			j++;
		return (1);
	}
	if (result != NULL && (m->part[j] == '\'' || m->part[j] == '"')
		&& ((m->part[j + 1] == ' ') || (m->part[j + 1] == '\0')))
	{
		j++;
		return (1);
	}
	return (0);
}

static int	extra_j_check(t_mini *mini, int j)
{
	while (mini->part[j] == ' ' && mini->part[j + 1] != '>'
		&& mini->part[j + 1] != '<')
		j++;
	if (j > 0 && (mini->part[j - 1] == '>' || mini->part[j - 1] == '<'))
	{
		while (mini->part[j] == '\\' || mini->part[j] == '\''
			|| mini->part[j] == '"' || mini->part[j] == '|' )
			j++;
	}
	if (mini->part[j - 1] == '<' || mini->part[j - 1] == '>')
	{
		if (j > 1 && (mini->part[j - 2] == '\'' || mini->part[j - 2] == '"'))
		{
			while ((mini->part[j] == '\'' || mini->part[j] == '"'))
				j++;
			j++;
		}
	}
	if (mini->part[j - 1] == ';' && j == (int)ft_strlen(mini->part)
		&& (j < 2 || mini->part[j - 2] != '\\'))
		j--;
	return (j);
}

static int 	fill_av_more(t_mini *m, int j, int k)
{
	char	*result;

	result = mem_check_tkns(ft_substr(m->part, k, j - k + 1), m, 0, 4);
	while (m->part[j] && ((m->part[j] != ' ' || (m->part[j] != ' '
					&& m->part[j + 1] != '\\')) || result == NULL))
	{
		free(result);
		result = mem_check_tkns(ft_substr(m->part, k, j - k + 1), m, 0, 4);
		if (check_redir(m, j, result) == 1)
		{
			j++;
			break ;
		}
		free(result);
		result = mem_check_tkns(ft_substr(m->part, k, j - k + 1), m, 0, 4);
		j++;
	}
	if (result)
		free(result);
	j = extra_j_check(m, j);
	return (j);
}

static int	substr_av(t_mini *mini, int j, int l, t_base *new)
{
	int	k;

	k = 0;
	while (mini->part[j] == ' ')
		j++;
	k = j;
	j = fill_av_more(mini, j, k);
	if ((mini->part[j] == '>') || (mini->part[j] == '<'))
	{
		if (mini->part[j + 1] == '>')
		{
			new->av[l] = ft_substr(mini->part, k, j - k + 2);
			j++;
		}
		else
			new->av[l] = ft_substr(mini->part, k, j - k + 1);
		j++;
	}
	else
		new->av[l] = ft_substr(mini->part, k, j - k);
	return (j);
}

int	fill_av_list(t_base *new, t_mini *mini, int j, int l)
{
	while (l != new->size)
	{
		if (mini->part[j] == '\0')
			new->av[l] = NULL;
		else
			j = substr_av(mini, j, l, new);
		l++;
	}
	return (0);
}
