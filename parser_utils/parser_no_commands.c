/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_no_commands.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/07 07:59:38 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/04/14 12:05:02 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	set_mini_return(t_mini *mini, char *line, int i)
{
	mini->part = ft_substr(line, 0, i);
	mini->type_end = T_END;
	if (line[i] == ';')
	{
		ft_putstr_fd("bash: syntax error near unexpected token `;;'\n", mini->stderr);
		mini->exit = 258;
		return (-1);
	}
	return (i);
}

static int	space_start(char *line, int i)
{
	if (line[i] && line[i] == ' ')
	{
		while (line[i] && line[i] == ' ')
			i++;
		return (i);
	}
	return (-1);
}

static int	line_valid(char *line, int i, char *result)
{
	if (line[i] && ((line[i] != '|' && line[i] != ';')
			|| (i == 0) || (line[i - 1] == '\\') || (result == NULL)))
		return (1);
	return (0);
}

int	no_of_commands(char *str, t_mini *mini, int i)
{
	char	*tmp;
	char	*result;

	tmp = ft_substr(str, 0, i);
	result = check_tokens(tmp, mini, 0, 1);
	while (line_valid(str, i, result) == 1)
	{
		if (space_start(str, i) != -1)
		{
			i = space_start(str, i);
			tmp = free_reset_tmp(tmp, result, str, i);
			result = check_tokens(tmp, mini, 0, 1);
			if (div_str(str, (i * -1), result, tmp) > 0)
				return (mini_vals(mini, i, str, div_str(str, i, result, tmp)));
			mini->numb_cmds++;
		}
		if (div_str(str, (i * -1), result, tmp) > 0)
			return (mini_vals(mini, i, str, div_str(str, i, result, tmp)));
		i = no_commands_line(str, i, mini);
		tmp = free_reset_tmp(tmp, result, str, i);
		result = check_tokens(tmp, mini, 0, 1);
	}
	ft_free_tmps(tmp, result);
	return (set_mini_return(mini, str, i));
}
