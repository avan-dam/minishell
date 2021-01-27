/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_arrays.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 17:39:41 by salbregh      #+#    #+#                 */
/*   Updated: 2021/01/27 17:39:42 by salbregh      ########   odam.nl         */
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

static void	set_command(t_mini *mini)
{
	mini->notbuiltin[0] = "ls"; //works
	mini->notbuiltin[1] = "/bin/ls"; //works
	mini->notbuiltin[2] = "/bin/chmod";
	mini->notbuiltin[3] = "chmod";
	mini->notbuiltin[4] = "wc";
	mini->notbuiltin[5] = "/bin/wc";
	mini->notbuiltin[6] = "awk";
	mini->notbuiltin[7] = "/bin/awk";
	mini->notbuiltin[8] = "grep";
	mini->notbuiltin[9] = "/bin/grep";
	mini->notbuiltin[10] = "mkdir";
	mini->notbuiltin[11] = "/bin/mkdir"; // works
	mini->notbuiltin[12] = "touch"; //doesnt work
	mini->notbuiltin[13] = "/bin/touch";
	mini->notbuiltin[14] = "rm"; // was rm -rf // doesnt work
	mini->notbuiltin[15] = "/bin/rm"; // works
	mini->notbuiltin[16] = "cat"; // doesnt work
	mini->notbuiltin[17] = "/bin/cat";
	mini->notbuiltin[18] = "cal";
	mini->notbuiltin[19] = "/bin/cal";
	mini->notbuiltin[20] = "date";
	mini->notbuiltin[21] = "/bin/date";
	mini->notbuiltin[22] = NULL;
}

void		ft_set_array(t_mini *mini)
{
	set_builtin(mini);
	set_command(mini);
	mini->stdout = 1;
	mini->stderr = 2;
}