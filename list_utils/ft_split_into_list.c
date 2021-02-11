/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_into_list.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/10 20:43:12 by salbregh      #+#    #+#                 */
/*   Updated: 2021/02/11 10:37:21 by salbregh      ########   odam.nl         */
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

int  ft_split_into_tlist(t_mini *mini, char *line)
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
	if (numb_char(var1, '\\') != 0)
	{
		unvalid_identifier(line, mini, 1);
		free(var1);
		return (-1);
	}
	var2 = ft_substr(line, i + 1, ft_strlen(line) - i - 1);
	ft_unset(mini, var1);
	newnode = ft_lstnew(var1, var2);
	free(var1);
	free(var2);
	ft_lstadd_back(&mini->env1, newnode);
	return (1);
}
