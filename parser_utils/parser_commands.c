/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_commands.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/23 17:37:54 by salbregh      #+#    #+#                 */
/*   Updated: 2021/04/04 19:21:28 by ambervandam   ########   odam.nl         */
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

int	pre_break_check(char *line, int i, char *result, char *tmp)
{
	if ((line[i] == '|' || line[i] == ';') && result != NULL)
	{
		free(tmp);
		free(result);
		return (0);
	}
	return (1);
}
