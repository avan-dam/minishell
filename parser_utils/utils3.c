/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils3.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/19 16:27:02 by salbregh      #+#    #+#                 */
/*   Updated: 2021/04/14 16:19:02 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	mini_vals(t_mini *mini, int i, char *line, int check)
{
	if (check == 1)
	{
		mini->part = ft_substr(line, 0, i);
		if (line[i] == '|' || (i != 0 && line[i - 1] == '|'))
			mini->type_end = T_PIPE;
		else if (line[i] == ';' || (i != 0 && line[i - 1] == ';'))
			mini->type_end = T_BREAK;
		return (i);
	}
	if (check == 2)
	{
		mini->part = ft_substr(line, 0, i + 1);
		if (line[i + 1] == '|')
			mini->type_end = T_PIPE;
		else if (line[i + 1] == ';')
			mini->type_end = T_BREAK;
		return (i + 1);
	}
	return (i);
}

void	ft_free_tmps(char *tmp, char *result)
{
	if (tmp)
		free(tmp);
	if (result)
		free(result);
}

char	*free_reset_tmp(char *tmp, char *result, char *line, int i)
{
	ft_free_tmps(tmp, result);
	return (ft_substr(line, 0, i));
}

int	unvalid_ident(char *error, t_mini *mini, int exitstatus)
{
	if ((ft_strcmp(error, "|") == 0)
		|| (ft_strcmp(error, ";") == 0)
		|| (ft_strcmp(error, ">") == 0)
		|| (ft_strcmp(error, "<") == 0))
	{
		printf("in here\n");
		ft_putstr_fd("bash: syntax error ", mini->stderr);
		ft_putstr_fd("near unexpected token '", mini->stderr);
		ft_putstr_fd(error, mini->stderr);
		ft_putstr_fd("'\n", mini->stderr);
		mini->exit = exitstatus;
		return (-1);
	}
	if (ft_strcmp(error, "\\$?") == 0)
		error = "$?";
	ft_putstr_fd("bash: ", mini->stderr);
	ft_putstr_fd(error, mini->stderr);
	ft_putstr_fd(": command not found\n", mini->stderr);
	mini->exit = exitstatus;
	if (ft_strcmp(error, mini->home) == 0)
		mini->exit = 126;
	if (ft_strcmp(error, "~") == 0)
		mini->exit = 126;
	return (-1);
}

char	*create_tmp2(t_base *ptr, int i, char *tmp2, t_mini *mini)
{
	if (!(ptr->av[i + 1]) && (numb_char(ptr->av[i], '\\') > 0) && i == 1)
		tmp2 = trim_string(ptr, tmp2, i);
	if (numb_char(ptr->av[i], '>') == 0 && numb_char(ptr->av[i], '<') == 0 )
		tmp2 = check_tokens(ptr->av[i], mini, 0, 9);
	if (tmp2 == NULL && ptr->av[i] != NULL)
		tmp2 = ft_strdup(ptr->av[i]);
	return (tmp2);
}
