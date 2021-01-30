/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 17:04:41 by salbregh      #+#    #+#                 */
/*   Updated: 2021/01/30 12:31:13 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_export(t_base *ptr, t_mini *mini)
{
	char	*error;
	printf("in export with ptr->argv[0][%s] and ptr->1 is [%s]\n", ptr->argv[0], ptr->argv[1]);
	if (ptr->argv[1] == NULL)
		return (0);
	if ((ptr->argv[1][0] >= '0' && ptr->argv[1][0] <= '9') || (ptr->argv[1][0] == '/'))
	{
    	error = ft_strjoin_three("bash: export: ", ptr->argv[1], " : not a valid identifier\n");
    	ft_putstr_fd(error, mini->stderr);
    	mini->exit = 1;
      	return (-1); // change
	}
	ft_split_into_tlist(mini, ptr->argv[1]);
	return (0); //change
}
