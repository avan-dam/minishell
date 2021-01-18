/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lst_addback.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/18 15:48:30 by salbregh      #+#    #+#                 */
/*   Updated: 2021/01/18 15:49:46 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
