/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstprint.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/18 15:49:11 by salbregh      #+#    #+#                 */
/*   Updated: 2021/02/08 10:50:23 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstprintold(t_list *lst)
{
	if (lst == NULL)
		return ;
	while (lst != NULL)
	{
		ft_putstr_fd(lst->var1, STDOUT);
		ft_putstr_fd("=", STDOUT);
		ft_putstr_fd(lst->var2, STDOUT);
		ft_putstr_fd("\n", STDOUT);
		lst = lst->next;
	}
}

void	ft_lstprint(t_list *lst, t_mini *mini, int i)
{
	t_list *tmp;
	tmp = lst;
	if (tmp == NULL)
		return ;
	while (tmp != NULL)
	{
		if (i == 1)
			ft_putstr_fd("declare -x ", mini->stdout);
		ft_putstr_fd(tmp->var1, mini->stdout);
		ft_putstr_fd("=", mini->stdout);
		ft_putstr_fd(tmp->var2, mini->stdout);
		ft_putstr_fd("\n", mini->stdout);
		tmp = tmp->next;
	}
}