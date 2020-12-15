/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/08 11:58:56 by ambervandam   #+#    #+#                 */
/*   Updated: 2020/12/09 19:52:38 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_node(t_list *lst, t_list *target, t_mini *mini)
{
    t_list *temp;
    temp = NULL;
	if (lst == NULL)
		return ;
	if (lst == target) 
    { 
	    if (lst->next == NULL)
        {
            free(lst);
            mini->tlist = temp;
            return ;
        }
        lst->var1 = lst->next->var1; 
        lst->var2 = lst->next->var2; 
        lst->next = lst->next->next;
        return;
	}
    // if not first node, find previous node 
    t_list *prev = lst; 
    while(prev->next != NULL && prev->next != target) 
        prev = prev->next; 
    // double check target in list
    if(prev->next == NULL) 
        return; 
    // Remove node from Linked List 
    prev->next = prev->next->next; 
    free(target); 
    return;  
}

int ft_unset(t_mini *mini)
{
    t_list  *tlist;

    if (mini->more == NULL)
		return (0);
    tlist = mini->tlist;
    while (tlist != NULL)
	{
        if (ft_strcmp(tlist->var1, mini->more) == 0)
        {
            ft_lstprint(mini->tlist);
			delete_node(mini->tlist, tlist, mini);
            ft_lstprint(mini->tlist);
    	    return (0);    
        }
        tlist = tlist->next;
	}
    return (0);
}