/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_no_commands.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/07 07:59:38 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/03/09 15:29:50 by avan-dam      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	no_of_commands_more(t_mini *mini, int i, char *line, int numb)
{
	mini->numb_cmds = numb;
	mini->cmd_part = ft_substr(line, 0, i);
	if (line[i] == '|')
		mini->type_end = T_PIPE;
	else if (line[i] == ';')
		mini->type_end = T_BREAK;
	return (i);
}

static int	no_commands_line(char *line, int i, int numb)
{
	if ((line[i] == '>' || line[i] == '<') && line[i + 1] != ' '
		&& line[i + 1] != '"' && line[i + 1] != '\'' && line[i + 1] != '>'
		&& line[i + 1] != '\0')
		numb++;
	return (numb);
}

static int	set_mini_return(t_mini *mini, int numb, char *line, int i)
{
	mini->numb_cmds = numb;
	mini->cmd_part = ft_substr(line, 0, i);
	mini->type_end = T_END;
	return (i);
}

static int	break_check(char *line, int i, char *result, char *tmp)
{
	if ((line[i] == '|' || line[i] == ';') && (result != NULL))
	{
		ft_free_tmps(tmp, result);
		return (1);
	}
	return (0);
}

int	no_of_commands(char *line, t_mini *mini, int i, int numb)
{
	char	*tmp;
	char	*result;

	tmp = ft_substr(line, 0, i);
	result = check_tokens(tmp, mini, 0, 1);
	while (line[i] && ((line[i] != '|' && line[i] != ';')
			|| (i == 0) || (line[i - 1] == '\\') || (result == NULL)))
	{
		if (line[i] == ' ')
		{
			while (line[i] == ' ')
				i++;
			tmp = free_reset_tmp(tmp, result, line, i);
			result = check_tokens(tmp, mini, 0, 1);
			if (break_check(line, i, result, tmp) == 1)
				return (no_of_commands_more(mini, i, line, numb));
			numb++;
		}
		numb = no_commands_line(line, i, numb);
		i++;
		tmp = free_reset_tmp(tmp, result, line, i);
		result = check_tokens(tmp, mini, 0, 1);
	}
	ft_free_tmps(tmp, result);
	return (set_mini_return(mini, numb, line, i));
}
