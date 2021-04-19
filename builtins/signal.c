/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/07 16:29:41 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/04/19 19:00:54 by ambervandam   ########   odam.nl         */
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
		ft_putstr_fd("\n> ", 0);
	}
	if (sig == SIGQUIT)
		write(1, "\b\b  \b\b", 6);
}

void	handle_sigint1(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\b\b  \b\b", 6);
	}
	if (sig == SIGQUIT)
		write(1, "\b\b  \b\b", 6);
}

static void	ft_signals_more(t_mini *mini, int i)
{
	if (i == 3)
	{
		if (signal(SIGQUIT, &handle_sigint1) == SIG_ERR)
		{
			mini->exit = 0;
			ft_exit(mini, mini->exit);
		}
		else if (signal(SIGINT, &handle_sigint1) == SIG_ERR)
		{
			mini->exit = 0;
			ft_exit(mini, mini->exit);
		}
	}
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
		else if (signal(SIGINT, &handle_sigint) == SIG_ERR)
		{
			mini->exit = 0;
			ft_exit(mini, mini->exit);
		}
	}
	if (i == 1)
	{
		ft_putstr_fd("exit\n", mini->stderr);
		mini->exit = 0;
		ft_exit(mini, mini->exit);
	}
}
