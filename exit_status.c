/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_status.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: Amber <Amber@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/24 10:48:47 by Amber         #+#    #+#                 */
/*   Updated: 2021/01/25 12:31:40 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_printf_exit_status(t_mini *mini)
{
	char	*exitstatus;

	exitstatus = ft_itoa(mini->exit);
	ft_putstr_fd(exitstatus, mini->stdout);
	ft_putstr_fd("\n", mini->stdout);
	mini->exit = 127;
}

void	ft_exit(t_mini *mini, char *line)
{
	ft_close_fds(mini);
	ft_lstclear(&mini->env1); // is this freeing the list enough
	ft_memset(&mini, 0, sizeof(t_mini));
	free(line);
	exit(0);
}