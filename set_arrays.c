/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_arrays.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/19 11:12:11 by salbregh      #+#    #+#                 */
/*   Updated: 2020/12/19 16:32:18 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_builtin(t_mini *mini)
{
	mini->builtin[0] = "echo";
	mini->builtin[1] = "cd";
	mini->builtin[2] = "pwd";
	mini->builtin[3] = "export";
	mini->builtin[4] = "unset";
	mini->builtin[5] = "env";
	mini->builtin[6] = "exit";
	mini->builtin[7] = NULL;
}

// static void	set_command(t_mini *mini)
// {
// 	mini->command[0] = "ls";
// 	mini->command[1] = "/bin/ls";
// 	mini->command[2] = "/bin/chmod";
// 	mini->command[3] = "chmod";
// 	mini->command[4] = "wc";
// 	mini->command[5] = "cat";
// 	mini->command[6] = "awk";
// 	mini->command[7] = "grep";
// 	mini->command[8] = "mkdir";
// 	mini->command[9] = "touch";
// 	mini->command[10] = "rm -rf";
// }

void		ft_set_array(t_mini *mini)
{
	set_builtin(mini);
	// set_command(mini);
}