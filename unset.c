/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/08 11:58:56 by ambervandam   #+#    #+#                 */
/*   Updated: 2020/12/08 13:16:10 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_node(t_list *lst, t_list *target)
{
	//if target is first node
	if(lst == target) 
    { 
		// if only one node lst cant be empty
    	if (lst->next == NULL) 
            return; 
        // send data of target to head
        lst->var1 = lst->next->var1; 
        lst->var2 = lst->next->var2; 
        // address of next node 
        target = lst->next; 
        // Remove the link of next node 
        lst->next = lst->next->next;
        // free memory 
        free(target); 
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

static void	ft_remove_from_tlist(char *word, t_mini *mini)
{
    t_list  *tlist;
    
    tlist = mini->tlist;
    while (tlist != NULL)
	{
        if (ft_strcmp(tlist->var1, word) == 0)
        {
			// printf("Initial tlist is\n");
		    ft_lstprint(mini->tlist);
			delete_node(mini->tlist, tlist);
			// printf("after deleting [%s] tlist is\n", word);
		    ft_lstprint(mini->tlist);
			// printf("found word%s now need to remove from list\n", word);
    	    return ;    
        }
        tlist = tlist->next;
	}
}

int ft_unset(t_mini *mini)
{
    int     i;
    int     j;
    char    *word;

    i = 0;
    // printf("in unset fucntion mini->more%s\n", mini->more);
    if (mini->more == NULL)
		return (0);
	while(mini->more[i] != '\0')
    {
        j = i;
        while(mini->more[i] != ' ' && mini->more[i] != '\0')
			i++;
		if (mini->more[i] != '\0')
		i++;
		if (i == (int)ft_strlen(mini->more))
	        word = ft_substr(mini->more, j, i - j);
		else
	        word = ft_substr(mini->more, j, i - j - 1);
        // printf("word:%s\n", word);
		ft_remove_from_tlist(word, mini);
    }
    return (0);
}