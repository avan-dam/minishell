/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/07 16:46:57 by salbregh      #+#    #+#                 */
/*   Updated: 2021/03/31 14:06:39 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(t_mini *mini, char *unset)
{
	t_list		*tlist;

	if (unset == NULL)
		return (0);
	tlist = mini->env1;
	while (tlist != NULL)
	{
		if (ft_strcmp(tlist->var1, unset) == 0)
		{
			delete_node(mini->env1, tlist, mini);
			return (0);
		}
		tlist = tlist->next;
	}
	return (0);
}

int	check_valid_unset(char *unset, t_mini *mini)
{
	if ((unset[0] >= '0' && unset[0] <= '9')
		|| (unset[0] == '+') || (unset[0] == '/')
		|| (unset[0] == '?') || (unset[0] == '$')
		|| (ft_strcmp(unset, "=") == 0))
	{
		ft_putstr_fd("bash: unset: ", mini->stderr);
		ft_putstr_fd(unset, mini->stderr);
		ft_putstr_fd(" : not a valid identifier\n", mini->stderr);
		mini->exit = 1;
		return (-1);
	}
	return (0);
}

static int	ft_unset_builtin_go(t_mini *mini, char *unset)
{
	t_list		*tlist;
	int			i;

	i = 0;
	if (unset == NULL)
		return (0);
	if (check_valid_unset(unset, mini) == -1)
		return (-1);
	mini->exit = 0;
	tlist = mini->env1;
	while (tlist != NULL)
	{
		if (ft_strcmp(tlist->var1, unset) == 0)
		{
			delete_node(mini->env1, tlist, mini);
			return (0);
		}
		tlist = tlist->next;
	}
	return (0);
}

int	ft_unset_builtin(t_mini *mini, t_base *ptr)
{
	int	i;
	int	ret;

	i = 1;
	while (ptr->av[i])
	{	
		ret = ft_unset_builtin_go(mini, ptr->av[i]);
		i++;
	}
	return (ret);
}
