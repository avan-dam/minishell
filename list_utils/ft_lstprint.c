/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstprint.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/18 15:49:11 by salbregh      #+#    #+#                 */
/*   Updated: 2021/01/27 13:45:09 by salbregh      ########   odam.nl         */
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

void	ft_lstprint(t_list *lst, t_mini *mini)
{
	if (lst == NULL)
		return ;
	while (lst != NULL)
	{
		ft_putstr_fd(lst->var1, mini->stdout);
		ft_putstr_fd("=", mini->stdout);
		ft_putstr_fd(lst->var2, mini->stdout);
		ft_putstr_fd("\n", mini->stdout);
		lst = lst->next;
	}
}