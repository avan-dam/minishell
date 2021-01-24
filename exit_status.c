/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_status.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: Amber <Amber@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/24 10:48:47 by Amber         #+#    #+#                 */
/*   Updated: 2021/01/24 12:49:07 by Amber         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_printf_exit_status(t_mini *mini)
{
	char *exitstatus;

	exitstatus = ft_itoa(mini->exit);
	ft_putstr_fd(exitstatus, mini->stdout);
	ft_putstr_fd("\n", mini->stdout);
	mini->exit = 127;
}
