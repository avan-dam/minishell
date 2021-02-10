/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 17:04:41 by salbregh      #+#    #+#                 */
/*   Updated: 2021/02/10 14:22:42 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_export(t_base *ptr, t_mini *mini)
{
	int i;

	i = 1;
	if (ptr->argv[1] == NULL)
	{
		ft_lstprint(mini->env1, mini, 1); //but then with delares and slighlty different
		return (0); // in this one things can have no var2
	}
	while (i < ptr->size && ptr->argv[i])
	{
		if ((ptr->argv[i][0] >= '0' && ptr->argv[i][0] <= '9') || (ptr->argv[i][0] == '+')|| (ptr->argv[i][0] == '/') || (ft_strcmp(ptr->argv[i], "=") == 0))
		{
			ft_putstr_fd("bash: export: ", mini->stderr);
			ft_putstr_fd(ptr->argv[i], mini->stderr);
			ft_putstr_fd(" : not a valid identifier\n", mini->stderr);
    		mini->exit = 1;
      		return (-1); // change
		} //check this
		if (ft_split_into_tlist(mini, ptr->argv[i]) != -1)
			mini->exit = 0;
		i++;
	}
	return (0); //change
}


	// if (ptr->argv[2] != NULL)
	// {
	// 	if (numb_char(ptr->argv[1], '=') == 0)
	// 		return (unvalid_identifier(ptr->argv[1], mini, 1));	
	// 	return (0);
	// }
	// if ((ptr->argv[1][0] >= '0' && ptr->argv[1][0] <= '9') || (ptr->argv[1][0] == '/'))
	// {
    // 	error = ft_strjoin_three("bash: export: ", ptr->argv[1], " : not a valid identifier\n");
    // 	ft_putstr_fd(error, mini->stderr);
    // 	mini->exit = 1;
    //   	return (-1); // change
	// } //check this
	// ft_split_into_tlist(mini, ptr->argv[1]);
	// mini->exit = 0;