/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 17:04:41 by salbregh      #+#    #+#                 */
/*   Updated: 2021/02/07 12:39:07 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_export(t_base *ptr, t_mini *mini)
{
	char	*error;
	if (ptr->argv[1] == NULL)
	{
		ft_lstprint(mini->env1, mini); //but then with delares and slighlty different
		return (0); // in this one things can have no var2
	}
	if (ptr->argv[2] != NULL)
	{
		if ((ft_strcmp("=", ptr->argv[2]) != 0) && numb_char(ptr->argv[1], '=') == 0)
		{	
			return (unvalid_identifier(ptr->argv[1], mini, 1));	
		}
		return (0);
	}
	if ((ptr->argv[1][0] >= '0' && ptr->argv[1][0] <= '9') || (ptr->argv[1][0] == '/'))
	{
    	error = ft_strjoin_three("bash: export: ", ptr->argv[1], " : not a valid identifier\n");
    	ft_putstr_fd(error, mini->stderr);
    	mini->exit = 1;
      	return (-1); // change
	} //check this
	ft_split_into_tlist(mini, ptr->argv[1]);
	mini->exit = 0;
	return (0); //change
}
