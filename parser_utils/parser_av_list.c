/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_av_list.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-dam <avan-dam@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/04 11:10:44 by avan-dam      #+#    #+#                 */
/*   Updated: 2021/04/06 14:30:35 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	more_av_list(t_base *new, t_mini *mini, t_base **ptr, char *line)
{
	new->size = mini->numb_cmds;
	new->prev = NULL;
	new->next = NULL;
	new->av[mini->numb_cmds] = NULL;
	if (fill_av_list(new, mini, 0, 0) == -1)
	{
		free(line);
		return (-1);
	}
	new->type = mini->type_end;
	if (numb_char(new->av[0], '$') == 0)
		new->av[0] = ft_strtolower(new->av[0]);
	ft_lstadd_back_base(ptr, new);
	free(line);
	return (0);
}

int	create_av_list(t_base **ptr, char *line, t_mini *mini)
{
	int		numb_characters;
	t_base	*new;

	if (ft_strcmp(line, "") == 0)
		return (0);
	if (mini->part != NULL)
	{
		free(mini->part);
		mini->part = NULL;
	}
	mini->numb_cmds = 1;
	numb_characters = no_of_commands(line, mini, 0);
	new = (t_base *)malloc(sizeof(t_base));
	if (new == NULL)
		return (-1);
	new->av = (char **)malloc(sizeof(char *) * (mini->numb_cmds + 1));
	if (new->av == NULL)
		return (-1);
	if (more_av_list(new, mini, ptr, line) == -1)
		return (-1);
	return (numb_characters);
}
