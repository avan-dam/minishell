/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/18 15:50:58 by salbregh      #+#    #+#                 */
/*   Updated: 2021/02/07 10:06:35 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_t_lstclear(t_list **lst)
{
	t_list	*store;
	t_list	*storenext;

	if (lst == NULL)
		return ;
	store = *lst;
	*lst = NULL;
	while (store != NULL)
	{
		free(store->var1);
		free(store->var2);
		storenext = (store->next);
		free(store);
		store = storenext;
	}
}

void	ft_t_baseclear(t_base **lst)
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
