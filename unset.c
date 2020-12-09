/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/08 11:58:56 by ambervandam   #+#    #+#                 */
/*   Updated: 2020/12/08 17:17:04 by ambervandam   ########   odam.nl         */
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

static void	ft_remove_from_tlist(char *word, t_mini *mini)
{
    t_list  *tlist;
    
    tlist = mini->tlist;
    while (tlist != NULL)
	{
        if (ft_strcmp(tlist->var1, word) == 0)
        {
			printf("Initial tlist is\n");
            ft_lstprint(mini->tlist);
			delete_node(mini->tlist, tlist, mini);
			printf("after deleting [%s] tlist is\n", word);
            ft_lstprint(mini->tlist);
    		printf("found word [%s] now need to remove from list\n", word);
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