/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/07 16:31:42 by salbregh      #+#    #+#                 */
/*   Updated: 2021/01/07 16:31:43 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_export(t_mini *mini, char *more)
{
	if (more == NULL)
		return (0);
	if ((more[0] >= '0' && more[0] <= '9') || (more[0] == '/'))
		return (unvalid_identifier(more));
	ft_split_into_tlist(mini, more);
	return (0);
}
