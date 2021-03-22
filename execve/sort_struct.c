/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort_struct.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/19 17:04:06 by salbregh      #+#    #+#                 */
/*   Updated: 2021/03/22 12:13:51 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sort_struct_before_redir(t_base *ptr, t_mini *mini)
{
	char	*temp;
	int		i;

	i = 0;
	while (i < ptr->size && ptr->av[i])
	{
		while (i < ptr->size && ptr->av[i] && ((ptr->av[i][0] == '"'
					&& ptr->av[i][1] == '"' && ptr->av[i][2] == '\0')
				|| (ptr->av[i][0] == '\'' && ptr->av[i][1] == '\''
					&& ptr->av[i][2] == '\0')))
			i++;
	 	if (i < ptr->size && ptr->av[i] && ((i == 0)
				|| (ft_strcmp(ptr->av[0], "export") != 0
					&& ft_strcmp(ptr->av[0], "echo") != 0)))
		{
			temp = ptr->av[i];
			ptr->av[i] = ft_strtrim_backslash(temp, ' ');
			free(temp);
			ptr->av[i] = mem_check_tkns(ptr->av[i], mini, 0, 6);
		}
		i++;
	}
}

void	sort_struct_after_redir(t_base *ptr)
{
	int	i;

	i = 0;
	while (i < ptr->size && ptr->av[i])
	{
		if ((ptr->av[i][0] == '"' && ptr->av[i][1] == '"'
				&& ptr->av[i][2] == '\0') || (ptr->av[i][0] == '\''
				&& ptr->av[i][1] == '\'' && ptr->av[i][2] == '\0'))
		{
			free(ptr->av[i]);
			ptr->av[i] = ft_strdup("");
		}
		i++;
	}
}
