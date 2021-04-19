/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort_struct.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/19 17:04:06 by salbregh      #+#    #+#                 */
/*   Updated: 2021/04/19 15:42:51 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check_unvalid(t_base *ptr)
{
	if (((ptr->av[0][0] == '"' && ptr->av[0][1] == '"')
			|| (ptr->av[0][0] == '\'' && ptr->av[0][1] == '\''))
		&& (ptr->av[0][2] == '\0' || ptr->av[0][2] == ' '))
		return (-1);
	return (0);
}

int	sort_struct_before_redir(t_base *ptr, t_mini *mini)
{
	char	*temp;
	int		i;

	i = 0;
	if (ft_check_unvalid(ptr) == -1)
		return (unvalid_ident("", mini, 127));
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
	return (0);
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

int	ptr_size_null(t_base *ptr, t_mini *mini)
{
	while (ptr->size == 0)
	{
		ptr = ptr->next;
		if (ptr == NULL)
			return (0);
		ptr = ft_redir(mini, ptr);
	}
	return (1);
}

int	ft_check_empty_av(t_base *ptr, t_mini *mini)
{
	int	i;
	int	len;

	i = 0;
	while (ptr->av[i])
	{
		if (ft_strcmp("", ptr->av[i]) == 0)
		{
			if (i > 0)
				len = ft_strlen(ptr->av[i - 1]) - 1;
			else
				len = -2;
			if (mini->check == 0 && (i == 0 || (len == -2)
					|| (len >= 0 && (ptr->av[i - 1][len]) != '\\')))
			{
				mini->check = 1;
				ft_putstr_fd("bash: syntax error near", mini->stderr);
				ft_putstr_fd(" unexpected token `;;'\n", mini->stderr);
				mini->exit = 258;
			}
			return (-2);
		}
		i++;
	}
	return (0);
}
