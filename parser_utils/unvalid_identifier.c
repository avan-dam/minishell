/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unvalid_identifier.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/12 12:40:58 by salbregh      #+#    #+#                 */
/*   Updated: 2021/02/12 12:41:19 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		unvalid_identifier(char *error, t_mini *mini, int exitstatus)
{
	if (ft_strcmp(error, "\\$?") == 0)
		error = "$?";
	ft_putstr_fd("bash: ", mini->stderr);
	ft_putstr_fd(error, mini->stderr);
	ft_putstr_fd(": command not found\n", mini->stderr);
	mini->exit = exitstatus;
	return (-1);
}
