/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/07 16:46:57 by salbregh      #+#    #+#                 */
/*   Updated: 2021/01/23 22:02:02 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		delete_node(t_list *lst, t_list *target, t_mini *mini)
{
	t_list		*temp;
	t_list		*prev;

	temp = NULL;
	if (lst == NULL)
		return ;
	if (lst == target)
	{
		if (lst->next == NULL)
		{
			free(lst);
			mini->env1 = temp;
			return ;
		}
		lst->var1 = lst->next->var1;
		lst->var2 = lst->next->var2;
		lst->next = lst->next->next;
		return ;
	}
	// if not first node, find previous node
	prev = lst;
	while ((prev->next != NULL) && (prev->next != target))
	{
		prev = prev->next;
		lst = lst->next;
	}
	// double check target in list
	if (prev->next == NULL)
		return ;
	// Remove node from Linked List
	prev->next = prev->next->next;
	free(target);
	lst = prev;
	return ;
}

int			ft_unset(t_mini *mini, char *unset)
{
	t_list		*tlist;

	if (unset == NULL)
		return (0);
	// looping through environmental variables only not run tlist
	// to see if can delete any from list
	tlist = mini->env1;
	while (tlist != NULL)
	{
		if (ft_strcmp(tlist->var1, unset) == 0)
		{
			delete_node(mini->env1, tlist, mini);
			return (0);
		}
		tlist = tlist->next;
	}
	return (0);
}
