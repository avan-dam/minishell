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

int    ft_export(t_mini *mini)
{
    if (mini->more == NULL)
		return (0);
    if ((mini->more[0] >= '0' && mini->more[0] <= '9') || (mini->more[0] == '/'))
        return(unvalid_identifier(mini->more));
    ft_split_into_tlist(mini, mini->more, 1);
    return (0);
}
