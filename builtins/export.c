/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/10 20:43:43 by salbregh      #+#    #+#                 */
/*   Updated: 2021/03/22 12:09:20 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	export_error_msg(t_mini *mini, char *string)
{
	ft_putstr_fd("bash: export: ", mini->stderr);
	ft_putstr_fd(string, mini->stderr);
	ft_putstr_fd(": not a valid identifier\n", mini->stderr);
	mini->exit = 1;
	return (-1);
}

static int	check_valid_export(t_base *ptr, t_mini *mini, int i)
{
	int	j;

	j = 0;
	while (ptr->av[i][j])
		j++;
	j = 0;
	while (ptr->av[i][j])
	{
		if ((ptr->av[i][0] == '=') || (((numb_char(ptr->av[i], '=') == 0))
				&& ((ptr->av[0][j] >= '0' && ptr->av[0][j] <= '9')
					|| ptr->av[i][j] == '-')))
			return (export_error_msg(mini, ptr->av[i]));
		if (ptr->av[i][j] == '=')
			break ;
		j++;
	}
	if ((ptr->av[i][0] >= '0' && ptr->av[i][0] <= '9')
		|| (ptr->av[i][0] == '+') || (ptr->av[i][0] == '/')
		|| (ptr->av[i][0] == '?') || (ptr->av[i][0] == '$')
		|| (ft_strcmp(ptr->av[i], "=") == 0))
		return (export_error_msg(mini, ptr->av[i]));
	return (0);
}

int	ft_export(t_base *ptr, t_mini *mini)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	mini->exit = 0;
	while (j < ptr->size && ptr->av[i])
	{
		ptr->av[j] = mem_check_tkns(ptr->av[j], mini, 0, 6);
		j++;
	}
	if (ptr->av[1] == NULL || ft_strcmp(ptr->av[1], "") == 0)
	{
		ft_lstprint(mini->env1, mini, 1);
		return (0);
	}
	while (i < ptr->size && ptr->av[i])
	{
		if (check_valid_export(ptr, mini, i) == -1)
			return (-1);
		ft_split_into_tlist(mini, ptr->av[i]);
		mini->exit = 0;
		i++;
	}
	return (0);
}
