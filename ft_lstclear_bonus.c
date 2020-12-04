/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear_bonus.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-dam <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/11 14:51:32 by avan-dam      #+#    #+#                 */
/*   Updated: 2020/12/04 17:30:58 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minshell.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*store;
	t_list	*me;

	if (del == NULL || lst == NULL)
	{
		return ;
	}
	store = *lst;
	*lst = NULL;
	while (store != NULL)
	{
		del(store->content);
		me = (store->next);
		free(store);
		store = me;
	}
}
