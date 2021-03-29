/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/07 14:50:10 by salbregh      #+#    #+#                 */
/*   Updated: 2021/03/29 15:05:31 by ambervandam   ########   odam.nl         */
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
	exit(exitstatus);
}

int	sort_exit_statement(t_base *ptr, t_mini *mini, int i)
{
	if (i == 1)
		ft_putstr_fd("exit\n", mini->stderr);
	if (ptr->av[1] != NULL)
	{
		ptr->av[1] = mem_check_tkns(ptr->av[1], mini, 0, 6);
		if (ft_is_str_int(ptr->av[1]) == 0)
		{
			ft_putstr_fd("bash: exit: ", mini->stderr);
			ft_putstr_fd(ptr->av[1], mini->stderr);
			ft_putstr_fd(": numeric argument required\n", mini->stderr);
			mini->exit = 255;
		}
		else
		{
			mini->exit = ft_atoi(ptr->av[1]);
			if (ptr->av[2] != NULL)
			{
				ft_putstr_fd("bash: exit: too many arguments\n", mini->stderr);
				mini->exit = 1;
				return (0);
			}
		}
	}
	return (-1);
}
