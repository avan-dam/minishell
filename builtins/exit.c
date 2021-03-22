/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/07 14:50:10 by salbregh      #+#    #+#                 */
/*   Updated: 2021/03/22 12:21:52 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_reset_fds(t_mini *mini)
{
	if (mini->stdout != 1)
	{
		if (mini->stdout != 2 && mini->stdout != 0)
			close(mini->stdout);
		mini->stdout = 1;
	}
	if (mini->stdin != 0)
	{
		if (mini->stdin != 1 && mini->stdin != 2)
			close(mini->stdin);
		mini->stdin = 0;
	}
	if (mini->stderr != 2)
	{
		if (mini->stderr != 1 && mini->stderr != 0)
			close(mini->stderr);
		mini->stderr = 2;
	}
}

void	ft_print_exit_status(t_mini *mini)
{
	ft_putstr_fd("bash: ", STDERR);
	ft_putnbr_fd(mini->exit, STDERR);
	ft_putstr_fd(": command not found\n", STDERR);
	mini->exit = 127;
}

void	clear_mini(t_mini *mini, int i)
{
	if (mini->part)
		free(mini->part);
	mini->type_end = 0;
	mini->numb_cmds = 0;
	ft_reset_fds(mini);
	if (i == 0)
	{
		mini->exit = 0;
		ft_lstclear(&mini->env1);
	}
}

void	ft_exit(t_mini *mini, int exitstatus)
{
	clear_mini(mini, 0);
	write(STDERR, "exit\n", 5);
	exit(exitstatus);
}
