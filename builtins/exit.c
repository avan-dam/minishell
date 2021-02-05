/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/07 14:50:10 by salbregh      #+#    #+#                 */
/*   Updated: 2021/02/05 16:07:40 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void 		ft_reset_fds(t_mini *mini)
{
	// printf("in close fds mini->stdout is %d mini->stdin is %d mini->stderr is %d\n", mini->stdout, mini->stdin, mini->stderr);
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

void		ft_printf_exit_status(t_mini *mini)
{
	char	*exitstatus;

	exitstatus = ft_itoa(mini->exit);
	ft_putstr_fd(exitstatus, mini->stdout);
	ft_putstr_fd("\n", mini->stdout);
	mini->exit = 127;
}

void	clear_mini(t_mini *mini, int i)
{
	if (mini->cmd_part)
	{
		free(mini->cmd_part);
		mini->cmd_part = NULL;
	}
	ft_t_lstclear(&mini->env1);
	mini->type_end = 0;
	mini->numb_cmds = 0;
	ft_reset_fds(mini);
	// mini->stdin = 0;
	// mini->stderr = 0;
	// mini->stdout = 0;
	if (i == 0)
		mini->exit = 0;	
}

void	ft_exit(t_mini *mini, int exitstatus) // exit with 0 or exit statment??
{
	clear_mini(mini, 0);
	exit(exitstatus);
}
