/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/07 16:29:41 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/03/23 17:32:19 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	(sig == SIGINT) handles CTRL-C
**	(sig == SIGQUIT) handles CTRL-\
**	CTRL slash this overwrites the previous two chars
**	CTRL D detected by EOF so handled differently when lineret == 0
*/

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\b\b  \b\b", 6);
		ft_putstr_fd("\n> ", 1);
	}
	if (sig == SIGQUIT)
		write(1, "\b\b  \b\b", 6);
}

void	ft_signals(t_mini *mini, int i)
{
	if (i == 0)
	{
		if (signal(SIGQUIT, &handle_sigint) == SIG_ERR)
		{
			mini->exit = 0;
			ft_exit(mini, mini->exit);
		}
		if (signal(SIGINT, &handle_sigint) == SIG_ERR)
		{
			mini->exit = 0;
			ft_exit(mini, mini->exit);
		}
	}
	else if (i == 1)
	{
		mini->exit = 0;
		ft_exit(mini, mini->exit);
	}
}
