/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_status.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: Amber <Amber@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/24 10:48:47 by Amber         #+#    #+#                 */
/*   Updated: 2021/01/27 17:42:34 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 		ft_close_fds(t_mini *mini)
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

	exitstatus = ft_itoa(mini->exit);
	ft_putstr_fd(exitstatus, mini->stdout);
	ft_putstr_fd("\n", mini->stdout);
	mini->exit = 127;
}

// MAKE SURE ALL CLEARED
void	ft_exit(t_mini *mini, char *line, int exitstatus)
{
	ft_close_fds(mini);
	ft_lstclear(&mini->env1); // is this freeing the list enough
	ft_memset(&mini, 0, sizeof(t_mini)); // but not mini->exit
	free(line);
	// printf("exit status is %d\n", mini->exit);
	exit(exitstatus);
}