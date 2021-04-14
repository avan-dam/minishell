/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/02 14:34:29 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/04/14 17:19:45 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	open_file_more(t_base *ptr, int i, t_mini *mini, int k)
{
	if (ft_check_empty(ptr->av[i + 1]) == 1 && k == 1)
	{
		mini->exit = 0;
		return (-1);
	}
	ft_close_correct(ptr->av[i], mini, ptr);
	if (ft_strcmp(">", ptr->av[i]) == 0)
	{
		mini->stdout = open(ptr->av[i + 1], R | C | T, 0666);
		if (mini->stdout == -1)
			return (error_opening(ptr->av[i + 1], mini));
	}
	if (ft_strcmp(">>", ptr->av[i]) == 0)
	{
		mini->stdout = open(ptr->av[i + 1], R | C | A, 0666);
		if (mini->stdout == -1)
			return (error_opening(ptr->av[i + 1], mini));
	}
	if (ft_strcmp("<", ptr->av[i]) == 0)
	{
		if (ft_special_open_stdin(mini, ptr, i) == -1)
			return (-1);
	}
	return (0);
}

static int	ft_open_file(t_base *ptr, int i, t_mini *mini, int k)
{
	int		ret;

	direction_list(ptr, i, i, 0);
	if (check_file_toredir(ptr, i, mini) == -1)
		return (-1);
	if (ptr->redir == 0)
		return (i);
	if (ft_tokens_open_argv(ptr, mini, i) == -1)
		return (-1);
	ret = open_file_more(ptr, i, mini, k);
	if (ret == -1)
		return (-1);
	if (ret == 0)
		ptr->av = ft_remove_redir_av(ptr, i, 0, find_k(ptr));
	if (ret == 1)
		ptr->av = ft_remove_redir_av(ptr, i + 1, 0, find_k(ptr));
	if (ptr->av == NULL)
		return (-1);
	return (i);
}

static int	check_no_redirs(char *s, t_mini *mini, int k, int j)
{
	while (s[k])
	{
		j = 0;
		while (s[k] == '>')
		{
			j++;
			k++;
		}
		if (send_to_unvalid_one(j, s, k, mini) == -1)
			return (-1);
		j = 0;
		while (s[k] == '<')
		{
			j++;
			k++;
		}
		if ((j == 1 && s[k] == '>' && (s[k + 1] == '>'
					|| s[k + 1] == '<')) || ((j == 2 || j == 3) && s[k] == '>'))
			return (unvalid_ident(">", mini, 258));
		if (send_to_unvalid(mini, j, s) == -1)
			return (-1);
		k++;
	}
	return (0);
}

static int	ft_backslash_redir(t_base *ptr, int i, t_mini *mini, int j)
{
	int	k;

	k = 0;
	if (ptr->av[i + 1] && ((ptr->av[i + 1][0] == ' ')
		|| (ptr->av[i + 1][0] == '\\')))
		k = 1;
	if ((numb_char(ptr->av[i], '"') != 0) || (numb_char(ptr->av[i], '\'') != 0))
	{
		ptr->av[i] = mem_check_tkns(ptr->av[i], mini, 0, 9);
		ptr->redir = 5;
		return (1);
	}
	if (ft_check_redir_in_quotes(ptr, mini, i) == 0)
		return (0);
	while (ptr->av[i][j] != '>' && ptr->av[i][j] != '<')
		j++;
	if (j <= 0 && ptr->redir == 1)
	{
		if (ft_open_file(ptr, i, mini, k) == -1)
			return (-1);
		return (0);
	}
	if (add_new_into_list(j, ptr, i) == -1)
		return (-1);
	return (0);
}

t_base	*ft_redir(t_mini *mini, t_base *ptr)
{
	int		i;

	i = 0;
	while (ptr->av[i] && i < ptr->size)
	{
		if ((ft_strchr_numb(ptr->av[i], '>', 0) != -1)
			|| (ft_strchr_numb(ptr->av[i], '<', 0) != -1))
		{
			redir_change_backslash(ptr, i);
			if (check_no_redirs(ptr->av[i], mini, 0, 0) == -1)
				return (NULL);
			if (ft_backslash_redir(ptr, i, mini, 0) < 0)
				return (NULL);
			if (ptr->redir == 1 && i != 0)
				i--;
			if (ptr->redir == 0 || ptr->redir == 5)
				i++;
		}
		else
			fix_redir_space_echo(ptr, i);
		ptr->redir = 0;
		i++;
	}
	return (ptr);
}
