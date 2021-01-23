/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/07 16:31:42 by salbregh      #+#    #+#                 */
/*   Updated: 2021/01/23 16:58:27 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_export(t_base *ptr, t_mini *mini)
{
	if (ptr->argv[1] == NULL)
		return (0);
	if ((ptr->argv[1][0] >= '0' && ptr->argv[1][0] <= '9') || (ptr->argv[1][0] == '/'))
		return (unvalid_identifier(ptr->argv[1], mini));
	ft_split_into_tlist(mini, ptr->argv[1]);
	return (0);
}
