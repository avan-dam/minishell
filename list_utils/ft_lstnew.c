/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/18 15:50:24 by salbregh      #+#    #+#                 */
/*   Updated: 2021/02/04 12:25:26 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_lstnew(void *var1, void *var2)
{
	t_list	*tmp;

	tmp = (t_list *)malloc(sizeof(t_list));
	if (tmp == NULL)
		return (NULL);
	if (tmp)
	{
		tmp->var1 = ft_strdup(var1);
		tmp->var2 = ft_strdup(var2);
		tmp->next = NULL;
	}
	return (tmp);
}
