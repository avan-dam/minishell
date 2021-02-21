/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/18 15:50:58 by salbregh      #+#    #+#                 */
/*   Updated: 2021/02/21 20:23:41 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*current;
	t_list	*next;

	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		free(current->var1);
		free(current->var2);
		free(current);
		current = next;
	}
	*lst = NULL;
}

static void	zero_store(t_base *store)
{
	store->redir = 0;
	store->type = 0;
	store->fd[0] = 0;
	store->fd[1] = 0;
}

void	ft_baseclear(t_base **lst)
{
	t_base	*store;
	t_base	*storenext;
	int		i;

	i = 0;
	if (lst == NULL)
		return ;
	store = *lst;
	*lst = NULL;
	while (store != NULL)
	{
		zero_store(store);
		while (i < store->size)
		{
			if (store->argv[i])
				free(store->argv[i]);
			i++;
		}
		i = 0;
		store->size = 0;
		free(store->argv);
		storenext = (store->next);
		free(store);
		store = storenext;
	}
}
