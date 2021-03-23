/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_commands.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/23 17:37:54 by salbregh      #+#    #+#                 */
/*   Updated: 2021/03/23 17:40:09 by salbregh      ########   odam.nl         */
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

static int	break_check(char *line, int i, char *result, char *tmp)
{
	if ((line[i] == '|' || line[i] == ';'))
	{
		ft_free_tmps(tmp, result);
		return (1);
	}
	return (0);
}

int	pre_break_check(char *line, int i, char *tmp, t_mini *mini)
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
