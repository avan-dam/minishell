/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   t_list.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/07 07:20:21 by salbregh      #+#    #+#                 */
/*   Updated: 2020/12/09 20:59:27 by salbregh      ########   odam.nl         */
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

void	ft_lstprint(t_list *lst)
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
