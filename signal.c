/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/25 18:35:10 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/01/27 09:38:37 by Amber         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_sigint(int sig)
{
    if (sig == SIGINT) //THIS IS FOR CRTL-C only
	{	
		write(1, "\b\b  \b\b", 6);
		ft_putstr_fd("\n> ", 1);
	}
	if(sig == SIGQUIT) //CTRL slash this overwrites the previous two chars
		write(1, "\b\b  \b\b", 6);
}

void	ft_signals(t_mini *mini, char *line, int i)
{
	if (i == 0)
	{
		if (signal(SIGQUIT, &handle_sigint) == SIG_ERR)
			ft_exit(mini, line, mini->exit);
		if (signal(SIGINT, &handle_sigint) == SIG_ERR)
			ft_exit(mini, line, mini->exit);
	}
	 if (i == 1) //CTRL D detected by EOF so handled differently
		ft_putstr_fd("exit\n", 1);
}
//need to make sure these signals work with execve properly
//maybe use WIFSIGNALED