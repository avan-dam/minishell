/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_utils2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/15 10:50:58 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/04/15 12:04:01 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_file_more(t_base *ptr, int i, t_mini *mini, int k)
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

int	error_opening(char *error, t_mini *mini)
{	
	ft_putstr_fd("bash: ", mini->stderr);
	ft_putstr_fd(error, mini->stderr);
	if (error[0] == '/')
		ft_putstr_fd(": Is a directory\n", mini->stderr);
	else
		ft_putstr_fd(": No such file or directory\n", mini->stderr);
	ft_reset_fds(mini);
	mini->exit = 1;
	return (-1);
}
