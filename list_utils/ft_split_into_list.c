/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_into_list.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/10 20:43:12 by salbregh      #+#    #+#                 */
/*   Updated: 2021/03/24 18:45:10 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_and_add(t_mini *mini, char *var1, char *var2)
{
	t_list	*newnode;

	newnode = ft_lstnew(var1, var2);
	ft_unset(mini, var1);
	free(var1);
	free(var2);
	ft_lstadd_back(&mini->env1, newnode);
}

static int	ft_only_export(char *line, t_mini *mini, char *var1, char *var2)
{
	int		i;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	var1 = ft_substr(line, 0, i);
	var2 = NULL;
	free_and_add(mini, var1, var2);
	return (0);
}

int	ft_split_into_tlist(t_mini *mini, char *line)
{
	int			i;
	char		*var1;
	char		*var2;

	var1 = NULL;
	var2 = NULL;
	i = ft_strchr_numb(line, '=', 0);
	if (i == -1)
		return (ft_only_export(line, mini, var1, var2));
	if (line[i - 1] == ' ' || line[i + 1] == ' ')
		return (0);
	var1 = ft_substr(line, 0, i);
	if (numb_char(var1, '\\') != 0)
	{
		unvalid_ident(line, mini, 1);
		free(var1);
		return (-1);
	}
	var2 = ft_substr(line, i + 1, ft_strlen(line) - i - 1);
	free_and_add(mini, var1, var2);
	return (1);
}
