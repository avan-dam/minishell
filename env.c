/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/07 22:27:08 by salbregh      #+#    #+#                 */
/*   Updated: 2020/12/14 11:46:11 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_env(char **argv, char **envp, t_mini *mini)
{
	int		i;
	t_list	*env;

	i = 0;
	env = NULL;
	(void)argv; // check for correct name executable?
	while (envp[i] != NULL)
	{
		ft_split_into_tlist(mini, envp[i]);
		i++;
	}
}
