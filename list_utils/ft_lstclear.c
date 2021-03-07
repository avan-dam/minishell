/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/18 15:50:58 by salbregh      #+#    #+#                 */
/*   Updated: 2021/03/06 15:18:01 by salbregh      ########   odam.nl         */
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
			if (store->av[i])
				free(store->av[i]);
			i++;
		}
		store->size = 0;
		free(store->av);
		storenext = (store->next);
		free(store);
		store = storenext;
	}
}

void 	clear_leaks(t_base *ptr)
{
	t_base	*temp;
	int		i;

	while (ptr)
	{
		temp = ptr->next;
		i = 1;
		while (i <= ptr->size)
		{
			free(ptr->av[i]);
			i++;
		}
		free(ptr->av);
		free(ptr);
		ptr = temp;
	}
	free(ptr);
	ptr = NULL;
}

void	one_baseclear(t_base *store)
{
	int		i;

	i = 0;
	if (store == NULL)
		return ;
	while (i < store->size)
	{
		if (store->av[i])
			free(store->av[i]);
		i++;
	}
	store->size = 0;
	free(store->av);
}
