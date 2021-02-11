/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/07 22:27:08 by salbregh      #+#    #+#                 */
/*   Updated: 2021/02/11 12:46:45 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Function that adds all environmental variables in a list called mini->env1
*/

void	ft_set_env(char **argv, char **envp, t_mini *mini)
{
	int		i;

	i = 0;
	(void)argv;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "OLDPWD", 6) == 0)
			i++;
		ft_split_into_tlist(mini, envp[i]);
		i++;
	}
	envp[i] = NULL;
	mini->exit = 0;
}
