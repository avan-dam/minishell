/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/18 15:50:58 by salbregh      #+#    #+#                 */
/*   Updated: 2021/01/18 15:51:14 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*store;
	t_list	*me;

	if (lst == NULL)
		return ;
	store = *lst;
	*lst = NULL;
	while (store != NULL)
	{
		free(store->var1);
		free(store->var2);
		me = (store->next);
		free(store);
		store = me;
	}
}
