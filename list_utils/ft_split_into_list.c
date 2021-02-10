/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_into_list.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/18 17:32:41 by salbregh      #+#    #+#                 */
/*   Updated: 2021/02/10 19:03:03 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	used for export and env to create the environmental variable list
**	and add values to the list by using export
**	var1 contains the environmental variable
**	var2 contains what comes after the '=' sign
**	if variable already excist unset it first
**	add new node to the end of the list of environmental variables
*/

int  ft_split_into_tlist(t_mini *mini, char *line, int j)
{
	t_list 		*newnode;
	int			i;
	char		*var1;
	char		*var2;

	if ((i = ft_strchr_numb(line, '=', 0)) == -1)
		return (0);
	if (line[i - 1] == ' ' || line[i + 1] == ' ')
		return (0);
	var1 = ft_substr(line, 0, i);
	var2 = ft_substr(line, i + 1, ft_strlen(line) - i - 1);
	if (j != 1)
		ft_unset(mini, var1); // leak comes from here
	newnode = ft_lstnew(var1, var2);
	free(var1);
	free(var2);
	ft_lstadd_back(&mini->env1, newnode);
	return (1);
}
