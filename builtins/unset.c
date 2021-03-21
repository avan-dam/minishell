/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/07 16:46:57 by salbregh      #+#    #+#                 */
/*   Updated: 2021/03/19 17:15:32 by salbregh      ########   odam.nl         */
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

int	check_valid_unset(t_base *ptr, int i, t_mini *mini)
{
	while (ptr)
	{
		while (i < ptr->size && ptr->av[i])
		{
			if ((ptr->av[i][0] >= '0' && ptr->av[i][0] <= '9')
				|| (ptr->av[i][0] == '+') || (ptr->av[i][0] == '/')
				|| (ptr->av[i][0] == '?') || (ptr->av[i][0] == '$')
				|| (ft_strcmp(ptr->av[i], "=") == 0))
			{
				ft_putstr_fd("bash: unset: ", mini->stderr);
				ft_putstr_fd(ptr->av[i], mini->stderr);
				ft_putstr_fd(" : not a valid identifier\n", mini->stderr);
				mini->exit = 1;
				return (-1);
			}
			i++;
		}
		ptr = ptr->next;
	}
	return (0);
}

int	ft_unset_builtin(t_mini *mini, char *unset, t_base *ptr)
{
	t_list		*tlist;
	int			i;

	i = 0;
	if (unset == NULL)
		return (0);
	if (check_valid_unset(ptr, i, mini) == -1)
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
