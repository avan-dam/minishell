/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lst_addback.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/18 15:48:30 by salbregh      #+#    #+#                 */
/*   Updated: 2021/02/10 19:05:40 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*first;

	if (alst == NULL || new == NULL)
		return ;
	if (!*alst)
		*alst = new;
	else
	{
		first = *alst;
		while (first->next)
			first = first->next;
		first->next = new;
		new->next = NULL;
	}
}

/*
**	list functions used in new parser
**	lets see if we can make this to one
*/

void		ft_lstadd_back_new(t_base **ptr, t_base *new)
{
	t_base	*tmp;

	if (!(*ptr))
		*ptr = new;
	else
	{
		tmp = *ptr;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}
