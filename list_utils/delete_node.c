/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   delete_node.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/19 17:13:34 by salbregh      #+#    #+#                 */
/*   Updated: 2021/03/19 17:16:36 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	node_free(t_list *lst)
{
	free(lst->var1);
	free(lst->var2);
	free(lst);
}

static void	equal_list(t_list *lst, t_list *tmp, t_mini *mini)
{
	if (!lst->next)
	{
		mini->env1 = tmp;
		node_free(tmp);
		return ;
	}
	tmp = lst->next;
	node_free(lst);
	mini->env1 = tmp;
	return ;
}

static t_list	*loop_through(t_list *prev, t_list *lst, t_list *target)
{
	while (prev->next && prev->next != target)
	{
		prev = prev->next;
		lst = lst->next;
	}
	return (prev);
}

void	delete_node(t_list *lst, t_list *target, t_mini *mini)
{
	t_list		*tmp;
	t_list		*prev;

	tmp = NULL;
	if (lst == NULL)
		return ;
	if (lst == target)
	{
		equal_list(lst, tmp, mini);
		return ;
	}
	prev = lst;
	prev = loop_through(prev, lst, target);
	if (prev->next == NULL)
	{
		ft_lstclear(&lst);
		ft_lstclear(&target);
		return ;
	}
	tmp = prev->next;
	prev->next = prev->next->next;
	lst = tmp;
	node_free(tmp);
	return ;
}
