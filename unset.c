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

void	delete_node(t_list *lst, t_list *target, t_mini *mini)
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
            mini->env1 = temp;
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

int ft_unset(t_mini *mini, char *unset)
{
    t_list  *tlist;

    if (unset == NULL)
		return (0);
    // looping through environmental variables only not run tlist
    // to see if can delete any from list
    tlist = mini->env1;
    while (tlist != NULL)
	{
        if (ft_strcmp(tlist->var1, unset) == 0)
        {
            // ft_lstprint(mini->env1);
			delete_node(mini->env1, tlist, mini);
            // ft_lstprint(mini->env1);
    	    return (0);    
        }
        tlist = tlist->next;
	}
    return (0);
}