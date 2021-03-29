/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils3.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/19 16:27:02 by salbregh      #+#    #+#                 */
/*   Updated: 2021/03/29 15:47:57 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	no_of_commands_more(t_mini *mini, int i, char *line, int numb)
{
	mini->numb_cmds = numb;
	mini->part = ft_substr(line, 0, i);
	if (line[i] == '|')
		mini->type_end = T_PIPE;
	else if (line[i] == ';')
		mini->type_end = T_BREAK;
	return (i);
}

void	ft_free_tmps(char *tmp, char *result)
{
	free(tmp);
	if (result)
		free(result);
}

char	*free_reset_tmp(char *tmp, char *result, char *line, int i)
{
	ft_free_tmps(tmp, result);
	return (ft_substr(line, 0, i));
}

int	unvalid_ident(char *error, t_mini *mini, int exitstatus)
{
	if ((ft_strcmp(error, "|") == 0)
		|| (ft_strcmp(error, ";") == 0)
		|| (ft_strcmp(error, ">") == 0)
		|| (ft_strcmp(error, "<") == 0))
	{
		ft_putstr_fd("bash: syntax error ", mini->stderr);
		ft_putstr_fd("near unexpected token '", mini->stderr);
		ft_putstr_fd(error, mini->stderr);
		ft_putstr_fd("'\n", mini->stderr);
		mini->exit = exitstatus;
		return (-1);
	}
	if (ft_strcmp(error, "\\$?") == 0)
		error = "$?";
	ft_putstr_fd("bash: ", mini->stderr);
	ft_putstr_fd(error, mini->stderr);
	ft_putstr_fd(": command not found\n", mini->stderr);
	mini->exit = exitstatus;
	if (ft_strcmp(error, ft_get_env("HOME", mini)) == 0)
		mini->exit = 126;
	return (-1);
}

int	redir_error(t_mini *mini, int i)
{
	if (i == 1)
	{
		ft_putstr_fd("bash: syntax error near ", mini->stderr);
		ft_putstr_fd("unexpected token `newline'\n", mini->stderr);
		ft_reset_fds(mini);
		mini->exit = 258;
	}
	if (i == 2)
	{
		ft_putstr_fd("bash: : No such file or directory\n", mini->stderr);
		mini->exit = 1;
	}
	return (-1);
}
