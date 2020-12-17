/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/04 18:02:26 by ambervandam   #+#    #+#                 */
/*   Updated: 2020/12/09 21:15:06 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    ft_export(t_mini *mini, char *more)
{
    if (more == NULL)
		return (0);
    if ((more[0] >= '0' && more[0] <= '9') || (more[0] == '/'))
        return(unvalid_identifier(more));
    ft_split_into_tlist(mini, more);
    return (0);
}
