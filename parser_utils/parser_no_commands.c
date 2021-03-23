/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_no_commands.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/07 07:59:38 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/03/23 12:46:20 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	no_commands_line(char *line, int i, int numb, t_mini *mini)
{
	char	*result;

	result = mem_check_tkns(ft_substr(line, 0, i), mini, 0, 4);
	if ((line[i] == '>' || line[i] == '<') && line[i + 1] != ' '
		 && line[i + 1] != '>' && line[i + 1] != '\0' && result != NULL)
		numb++;
	else if (result != NULL && (line[i] == '\'' || line[i] == '"'))
		numb++;
	free(result);
	return (numb);
}

static int	set_mini_return(t_mini *mini, int numb, char *line, int i)
{
	mini->numb_cmds = numb;
	mini->part = ft_substr(line, 0, i);
	mini->type_end = T_END;
	return (i);
}

static int	break_check(char *line, int i, char *result, char *tmp)
{
	if ((line[i] == '|' || line[i] == ';'))
	{
		ft_free_tmps(tmp, result);
		return (1);
	}
	return (0);
}

static int	pre_break_check(char *line, int i, char *tmp, t_mini *mini)
{
	char	*result;

	result = check_tokens(tmp, mini, 0, 1);
	if ((line[i] == '|' || line[i] == ';') && result != NULL)
	{
		if (break_check(line, i, result, tmp) == 1)
			return (0);
	}
	if (result)
		free(result);
	return (1);
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
			if (pre_break_check(line, i, tmp, mini) == 0)
				return (no_of_commands_more(mini, i, line, numb));
			numb++;
		}
		if (pre_break_check(line, i, tmp, mini) == 0)
			return (no_of_commands_more(mini, i, line, numb));
		numb = no_commands_line(line, i, numb, mini);
		i++;
		tmp = free_reset_tmp(tmp, result, line, i);
		result = check_tokens(tmp, mini, 0, 1);
	}
	ft_free_tmps(tmp, result);
	return (set_mini_return(mini, numb, line, i));
}
