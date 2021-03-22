/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils3.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/19 16:27:02 by salbregh      #+#    #+#                 */
/*   Updated: 2021/03/22 13:05:25 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		|| (ft_strcmp(error, ";") == 0))
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
	return (-1);
}
