/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/18 15:50:58 by salbregh      #+#    #+#                 */
/*   Updated: 2021/02/09 17:44:48 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstclear(t_list **lst)
{
	t_list *current;
	t_list *next;

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
		store->redir = 0;
		store->type = 0;
		store->fd[0] = 0;
		store->fd[1] = 0;
		while (i < store->size)
		{
			// printf("i is %d and store->size is %d\n", i, store->size);
			// printf("and store->argv[i] is [%s]\n", store->argv[i]);
			if (store->argv[i])
			{
				free(store->argv[i]);
				store->argv[i] = NULL;
			}
			i++;
		}
		store->size = 0;
		free(store->argv);
		storenext = (store->next);
		free(store);
		store = storenext;
	}
}
