/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   t_list.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/07 07:20:21 by salbregh      #+#    #+#                 */
/*   Updated: 2021/01/11 18:15:41 by ambervandam   ########   odam.nl         */
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

void	ft_lstclear(t_list **lst)
{
	t_list	*store;
	t_list	*me;

	if (lst == NULL)
	{
		return ;
	}
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