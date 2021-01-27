/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
<<<<<<< HEAD:export.c
/*   Created: 2020/12/04 18:02:26 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/01/25 16:37:55 by ambervandam   ########   odam.nl         */
=======
/*   Created: 2021/01/07 16:31:42 by salbregh      #+#    #+#                 */
/*   Updated: 2021/01/17 22:15:51 by salbregh      ########   odam.nl         */
>>>>>>> master:builtins/export.c
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_export(t_mini *mini, char *more)
{
<<<<<<< HEAD:export.c
  char *error;
    if (more == NULL)
=======
	if (more == NULL)
>>>>>>> master:builtins/export.c
		return (0);
    if ((more[0] >= '0' && more[0] <= '9') || (more[0] == '/'))
    {    
      error = ft_strjoin_three("bash: export: ", more, " : not a valid identifier\n");
      ft_putstr_fd(error, mini->stderr);
      mini->exit = 1;
      return(-1);
    }
    ft_split_into_tlist(mini, more);
    return (0);
}
