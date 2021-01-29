/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/07 14:50:10 by salbregh      #+#    #+#                 */
/*   Updated: 2021/01/29 21:46:18 by ambervandam   ########   odam.nl         */
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
	// printf("going out of close fds\n");
}

void		ft_printf_exit_status(t_mini *mini)
{
	char	*exitstatus;

	printf("in exit status command\n");
	exitstatus = ft_itoa(mini->exit);
	ft_putstr_fd(exitstatus, mini->stdout);
	ft_putstr_fd("\n", mini->stdout);
	mini->exit = 127;
}

// MAKE SURE ALL CLEARED
void	ft_exit(t_mini *mini, int exitstatus)
{
	ft_reset_fds(mini);
	ft_memset(&mini, 0, sizeof(t_mini)); // but not mini->exit
	// printf("exit status is %d\n", mini->exit);
	exit(exitstatus);
}