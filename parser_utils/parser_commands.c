/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_commands.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/23 17:37:54 by salbregh      #+#    #+#                 */
/*   Updated: 2021/04/05 11:47:56 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	no_commands_line(char *line, int i, t_mini *mini)
{
	char	*result;

	result = mem_check_tkns(ft_substr(line, 0, i), mini, 0, 4);
	if ((line[i] == '>' || line[i] == '<') && line[i + 1] != ' '
		 && line[i + 1] != '>' && line[i + 1] != '\0' && result != NULL)
		mini->numb_cmds++;
	else if (result != NULL && (line[i] == '\'' || line[i] == '"'))
		mini->numb_cmds++;
	free(result);
	return (i + 1);
}

int	div_str(char *line, int i, char *result, char *tmp)
{
	int	y;

	y = i;
	if (i < 0)
		y = i * -1;
	if ((line[y] == '|' || line[y] == ';') && result != NULL)
	{
		if (i >= 0)
			ft_free_tmps(tmp, result);
		return (1);
	}
	if ((line[y + 1] == '|' || line[y + 1] == ';')
		&& line[y + 2] == ' ' && result != NULL)
	{	
		if (i >= 0)
			ft_free_tmps(tmp, result);
		return (2);
	}
	return (0);
}
