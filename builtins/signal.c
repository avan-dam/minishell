/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/07 16:29:41 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/04/19 20:58:28 by ambervandam   ########   odam.nl         */
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
		write(STDOUT, "\b\b  \b\b", 6);
		ft_putstr_fd("\n> ", STDOUT);
	}
	if (sig == SIGQUIT)
		write(STDOUT, "\b\b  \b\b", 6);
}

void	handle_sigint1(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT);
	}
	if (sig == SIGQUIT)
	{	
		ft_putstr_fd("Quit: 3\n", STDOUT);
	}
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
	ft_signals_more(mini, i);
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
