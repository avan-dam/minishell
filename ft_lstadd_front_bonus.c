/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_front_bonus.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-dam <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/11 10:14:01 by avan-dam      #+#    #+#                 */
/*   Updated: 2020/12/04 17:30:55 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minshell.h"

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	if (alst == NULL || new == NULL)
		return ;
	new->next = *alst;
	*alst = new;
}
