/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/07 16:46:57 by salbregh      #+#    #+#                 */
/*   Updated: 2021/02/10 20:42:56 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		delete_node(t_list *lst, t_list *target, t_mini *mini)
{
	t_list		*tmp;
	t_list		*prev;

	tmp = NULL;
	if (lst == NULL)
		return ;
	if (lst == target)
	{
		if (!lst->next)
		{
			mini->env1 = tmp; // list is NULL
			return ;
		}
		lst = lst->next;
		mini->env1 = lst;
		return ;
	}
	// if not first node, find previous node
	prev = lst;
	while (prev->next && prev->next != target)
	{
		prev = prev->next;
		lst = lst->next;
	}
	if (prev->next == NULL)
	{
		ft_lstclear(&lst);
		ft_lstclear(&target);
		return ;
	}
	// Remove node from Linked List
	prev->next = prev->next->next;
	lst = prev;
	// ft_lstclear(&target);
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
	mini->exit = 0;
	return (0);
}
