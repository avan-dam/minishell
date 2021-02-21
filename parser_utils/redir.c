/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/02 14:34:29 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/02/21 20:15:13 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	error_opening(char *error, t_mini *mini)
{
	ft_putstr_fd("bash: ", mini->stderr);
	ft_putstr_fd(error, mini->stderr);
	ft_putstr_fd(": No such file or directory\n", mini->stderr);
	ft_reset_fds(mini);
	mini->exit = 1;
	return (-1);
}

static void	direction_list(t_base *ptr, int i)
{
	int	j;

	if ((ft_strchr_numb(ptr->argv[i + 1], '>', 0) != -1)
		|| (ft_strchr_numb(ptr->argv[i + 1], '<', 0) != -1))
	{
		if (ft_strchr_numb(ptr->argv[i + 1], '>', 0) != -1)
			j = ft_strchr_numb(ptr->argv[i + 1], '>', 0);
		if ((ft_strchr_numb(ptr->argv[i + 1], '<', 0) != -1)
			&& ft_strchr_numb(ptr->argv[i + 1], '<', 0) < j)
			j = ft_strchr_numb(ptr->argv[i + 1], '<', 0);
		if (add_new_into_list(j, ptr, i + 1) == -1)
			i++;
	}
}

static int	ft_open_file(t_base *ptr, int i, t_mini *mini)
{
	if (check_file_toredir(ptr, i, mini) == -1)
		return (-1);
	if (ptr->redir == 0)
		return (i);
	if (ft_strcmp(">", ptr->argv[i]) == 0)
	{
		if ((mini->stdout = open(ptr->argv[i + 1], R | C | T, 0666)) == -1)
			return (error_opening(ptr->argv[i + 1], mini));
	}
	if (ft_strcmp(">>", ptr->argv[i]) == 0)
	{
		if ((mini->stdout = open(ptr->argv[i + 1], R | C | A, 0666)) == -1)
			return (error_opening(ptr->argv[i + 1], mini));
	}
	if (ft_strcmp("<", ptr->argv[i]) == 0)
	{
		if ((mini->stdin = open(ptr->argv[i + 1], R, 0666)) == -1)
			return (error_opening(ptr->argv[i + 1], mini));
	}
	if ((ptr->argv = ft_remove_redir_argv(ptr, i, 0)) == NULL)
		return (-1);
	return (i);
}

static int	ft_backslash_redir(t_base *ptr, int i, t_mini *mini, int j)
{
	if (ft_check_redir_in_quotes(ptr, mini, i) == 0)
		return (0);
	while (ptr->argv[i][j] != '>' && ptr->argv[i][j] != '<')
		j++;
	if (j <= 0)
	{
		if (ptr->redir == 1)
		{
			direction_list(ptr, i);
			if (ft_open_file(ptr, i, mini) == -1)
				return (-1);
			return (0);
		}
	}
	if (add_new_into_list(j, ptr, i) == -1)
		return (-1);
	return (0);
}

t_base		*ft_redir(t_mini *mini, t_base *ptr)
{
	int		i;

	i = 0;
	while (i < ptr->size && ptr->argv[i])
	{
		if ((ft_strchr_numb(ptr->argv[i], '>', 0) != -1) ||
		(ft_strchr_numb(ptr->argv[i], '<', 0) != -1))
		{
			redir_change_backslash(ptr, i);
			if (ft_backslash_redir(ptr, i, mini, 0) == -1)
				return (NULL);
			if (ptr->redir == 1 && i != 0)
				i--;
			if (ptr->redir == 0)
				i++;
		}
		ptr->redir = 0;
		i++;
	}
	return (ptr);
}
