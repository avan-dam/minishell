/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   t_list.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/07 07:20:21 by salbregh      #+#    #+#                 */
/*   Updated: 2020/12/07 07:20:23 by salbregh      ########   odam.nl         */
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
		del(store->var1);
		del(store->var2);
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
		del(lst->var1);
		del(lst->var2);
		free(lst);
	}
}

void	ft_lstprint(t_list *lst)
{
	if (lst == NULL)
		return ;
	while (lst != NULL)
	{
		ft_putstr("vars1 is: ");
		ft_putstr(lst->var1);
		ft_putstr(" and vars2 is: ");
		ft_putstr(lst->var2);
		ft_putchar('\n');
		lst = lst->next;
	}
}
