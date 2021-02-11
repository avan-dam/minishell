/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/25 18:35:10 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/02/11 10:56:25 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void handle_sigint(int sig)
{
    if (sig == SIGINT) //THIS IS FOR CRTL-C only
	{	
		write(1, "\b\b  \b\b", 6);
		ft_putstr_fd("\n> ", 1); // comment out for tester
	}
	if (sig == SIGQUIT) //CTRL slash this overwrites the previous two chars
		write(1, "\b\b  \b\b", 6);
}

void	ft_signals(t_mini *mini, int i)
{
	if (i == 0)
	{
		if (signal(SIGQUIT, &handle_sigint) == SIG_ERR)
			ft_exit(mini, mini->exit);
		if (signal(SIGINT, &handle_sigint) == SIG_ERR)
			ft_exit(mini, mini->exit);
	}
	if (i == 1) //CTRL D detected by EOF so handled differently when lineret ==0
		ft_putstr_fd("exit\n", 1); // ALSO FREE ALL IF GET THERE
}
//need to make sure these signals work with execve properly
//maybe use WIFSIGNALED