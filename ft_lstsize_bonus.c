/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsize_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-dam <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/11 10:25:01 by avan-dam      #+#    #+#                 */
/*   Updated: 2020/12/04 17:31:11 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minshell.h"

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
