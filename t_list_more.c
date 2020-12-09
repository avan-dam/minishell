/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   t_list_more.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/07 07:20:47 by salbregh      #+#    #+#                 */
/*   Updated: 2020/12/08 13:27:35 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_list	*ft_lstlast(t_list *lst)
// {
// 	if (lst)
// 	{
// 		while (lst->next != NULL)
// 			lst = lst->next;
// 	}
// 	return (lst);
// }

// int		ft_lstsize(t_list *lst)
// {
// 	int	i;

// 	i = 0;
// 	while (lst)
// 	{
// 		i++;
// 		lst = lst->next;
// 	}
// 	return (i);
// }

// void	ft_lstdelone(t_list *lst, void (*del)(void *))
// {
// 	if (del == NULL || lst == NULL)
// 		return ;
// 	if (lst)
// 	{
// 		del(lst->var1);
// 		del(lst->var2);
// 		free(lst);
// 	}
// }