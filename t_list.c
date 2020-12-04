/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   t_list.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/04 17:53:55 by ambervandam   #+#    #+#                 */
/*   Updated: 2020/12/04 17:55:11 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*first;

	if (alst == NULL || new == NULL)
		return ;
	if (*alst == NULL)
		*alst = new;
	first = *alst;
	while (first->next != NULL)
		first = first->next;
	first->next = new;
	new->next = NULL;
}

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	if (alst == NULL || new == NULL)
		return ;
	new->next = *alst;
	*alst = new;
}

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

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (del == NULL || lst == NULL)
		return ;
	if (lst)
	{
		del(lst->content);
		free(lst);
	}
}

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (f == NULL || lst == NULL)
		return ;
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
}
