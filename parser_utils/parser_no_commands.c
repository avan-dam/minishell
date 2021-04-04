/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_no_commands.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/07 07:59:38 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/04/04 19:20:09 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	set_mini_return(t_mini *mini, int numb, char *line, int i)
{
	mini->numb_cmds = numb;
	mini->part = ft_substr(line, 0, i);
	mini->type_end = T_END;
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

int	no_of_commands(char *line, t_mini *mini, int i, int numb)
{
	char	*tmp;
	char	*result;

	tmp = ft_substr(line, 0, i);
	result = check_tokens(tmp, mini, 0, 1);
	while (line_valid(line, i, result) == 1)
	{
		if (space_start(line, i) != -1)
		{
			i = space_start(line, i);
			tmp = free_reset_tmp(tmp, result, line, i);
			result = check_tokens(tmp, mini, 0, 1);
			if (pre_break_check(line, i, result, tmp) != 1)
				return (no_of_commands_more(mini, i, line, numb));
			numb++;
		}
		if (pre_break_check(line, i, result, tmp) == 0)
			return (no_of_commands_more(mini, i, line, numb));
		numb = no_commands_line(line, i, numb, mini);
		i++;
		tmp = free_reset_tmp(tmp, result, line, i);
		result = check_tokens(tmp, mini, 0, 1);
	}
	ft_free_tmps(tmp, result);
	return (set_mini_return(mini, numb, line, i));
}
