/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   t_list.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/07 07:20:21 by salbregh      #+#    #+#                 */
/*   Updated: 2020/12/08 15:52:01 by ambervandam   ########   odam.nl         */
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

// void	ft_lstadd_front(t_list **alst, t_list *new)
// {
// 	if (alst == NULL || new == NULL)
// 		return ;
// 	new->next = *alst;
// 	*alst = new;
// }

// void	ft_lstclear(t_list **lst, void (*del)(void *))
// {
// 	t_list	*store;
// 	t_list	*me;

// 	if (del == NULL || lst == NULL)
// 	{
// 		return ;
// 	}
// 	store = *lst;
// 	*lst = NULL;
// 	while (store != NULL)
// 	{
// 		del(store->var1);
// 		del(store->var2);
// 		me = (store->next);
// 		free(store);
// 		store = me;
// 	}
// }

void	ft_lstprint(t_list *lst)
{
	if (lst == NULL)
		return ;
	while (lst != NULL)
	{
		printf("var1 is[%s] and var2 is[%s]\n", lst->var1, lst->var2);
		lst = lst->next;
	}
}

t_list	*ft_lstnew(void *var1, void *var2)
{
	t_list	*tmp;

	tmp = (t_list *)malloc(sizeof(t_list));
	if (tmp == NULL)
		return (NULL);
	if (tmp)
	{
		tmp->var1 = var1;
		tmp->var2 = var2;
		tmp->next = NULL;
	}
	return (tmp);
}
