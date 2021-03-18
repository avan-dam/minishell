/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/07 22:27:08 by salbregh      #+#    #+#                 */
/*   Updated: 2021/03/18 11:09:53 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Function that adds all environmental variables in a list called mini->env1
*/

void	ft_set_env(char **av, char **envp, t_mini *mini)
{
	int		i;

	i = 0;
	(void)av;
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

void	ft_lstprint_env(t_list *lst, t_mini *mini, t_base *ptr)
{
	t_list	*tmp;

	tmp = lst;
	if (tmp == NULL)
		return ;
	if (ptr->av[1])
	{
		ft_putstr_fd("env: ", STDOUT);
		ft_putstr_fd(ptr->av[1], STDOUT);
		ft_putstr_fd(": No such file or directory\n", STDOUT);
		mini->exit = 127;
		return ;
	}
	while (tmp != NULL)
	{
		if (tmp->var2 == NULL)
		{
			tmp = tmp->next;
			continue ;
		}
		ft_putstr_fd(tmp->var1, mini->stdout);
		ft_putstr_fd("=", mini->stdout);
		ft_putstr_fd(tmp->var2, mini->stdout);
		ft_putstr_fd("\n", mini->stdout);
		tmp = tmp->next;
	}
}
