/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/04 18:02:26 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/01/25 16:03:52 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    ft_export(t_mini *mini, char *more)
{
  char *error;
    if (more == NULL)
		return (0);
    if ((more[0] >= '0' && more[0] <= '9') || (more[0] == '/'))
    {    
      error = ft_strjoin("bash: export: ", more);
      error = ft_strjoin(error, " : not a valid identifier\n");
      ft_putstr_fd(error, mini->stderr);
      mini->exit = 1;
      return(-1);
    }
    ft_split_into_tlist(mini, more);
    return (0);
}
