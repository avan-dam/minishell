/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/10 20:43:43 by salbregh      #+#    #+#                 */
/*   Updated: 2021/03/09 12:01:49 by avan-dam      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_valid_export(t_base *ptr, t_mini *mini, int i)
{
	if ((ptr->av[i][0] >= '0' && ptr->av[i][0] <= '9')
		|| (ptr->av[i][0] == '+') || (ptr->av[i][0] == '/')
		|| (ptr->av[i][0] == '?') || (ptr->av[i][0] == '$')
		|| (ft_strcmp(ptr->av[i], "=") == 0)
		|| (ft_lst_cmp(mini, ptr->av[i])))
		// OR CHECK IN LAST BIT OF LIST
	{
		ft_putstr_fd("bash: export: ", mini->stderr);
		ft_putstr_fd(ptr->av[i], mini->stderr);
		ft_putstr_fd(" : not a valid identifier\n", mini->stderr);
		mini->exit = 1;
		return (-1);
	}
	return (0);
}

int	ft_export(t_base *ptr, t_mini *mini)
{
	int	i;

	i = 1;
	if (ptr->av[1] == NULL || ft_strcmp(ptr->av[1], "") == 0)
	{
		ft_lstprint(mini->env1, mini, 1);
		return (0);
	}
	while (i < ptr->size && ptr->av[i])
	{
		if (check_valid_export(ptr, mini, i) == -1)
			return (-1);
		ft_split_into_tlist(mini, ptr->av[i]);
		mini->exit = 0;
		i++;
	}
	return (0);
}
