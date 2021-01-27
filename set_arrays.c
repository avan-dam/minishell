/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_arrays.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/19 11:12:11 by salbregh      #+#    #+#                 */
/*   Updated: 2021/01/27 16:40:26 by ambervandam   ########   odam.nl         */
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
	mini->notbuiltin[5] = "cat";
	mini->notbuiltin[6] = "awk";
	mini->notbuiltin[7] = "grep";
	mini->notbuiltin[8] = "mkdir";
	mini->notbuiltin[9] = "touch"; //doesnt work
	mini->notbuiltin[10] = "rm -rf"; // doesnt work BECAUSE SPACE IN COMMAND SO SET EDGE CASE FOR THIS
	mini->notbuiltin[11] = "cat"; 
	mini->notbuiltin[12] = NULL;
}

void		ft_set_array(t_mini *mini)
{
	set_builtin(mini);
	set_command(mini);
	mini->stdout = 1;
	mini->stderr = 2;
}