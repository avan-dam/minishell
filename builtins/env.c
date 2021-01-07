/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/07 22:27:08 by salbregh      #+#    #+#                 */
/*   Updated: 2021/01/07 20:59:52 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_set_env(char **argv, char **envp, t_mini *mini)
{
	int		i;
	t_list	*env;

	i = 0;
	env = NULL;
	(void)argv;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "OLDPWD", 5) == 0)
			i++; // delete OLDPWD
		ft_split_into_tlist(mini, envp[i]);
		i++;
	}
	envp[i] = NULL;
	// delete old pwd out of the environmental variables.
}
