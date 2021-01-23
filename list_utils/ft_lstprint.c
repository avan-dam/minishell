/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstprint.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/18 15:49:11 by salbregh      #+#    #+#                 */
/*   Updated: 2021/01/18 15:49:43 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstprintold(t_list *lst)
{
	if (lst == NULL)
		return ;
	while (lst != NULL)
	{
		ft_putstr(lst->var1);
		ft_putstr("=");
		ft_putstr(lst->var2);
		ft_putstr("\n");
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