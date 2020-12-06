/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   t_list_more.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/04 17:55:31 by ambervandam   #+#    #+#                 */
/*   Updated: 2020/12/04 19:09:17 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst)
	{
		while (lst->next != NULL)
			lst = lst->next;
	}
	return (lst);
}

t_list	*ft_lstnew(void *var1, void *var2)
{
	t_list	*tmp;

	tmp = (t_list *)malloc(sizeof(t_list));
	if (tmp == NULL)
		return (NULL);
	if (tmp)
	{
		tmp->var1 = var1;
		tmp->var2 = var2;
		tmp->next = NULL;
	}
	return (tmp);
}

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}