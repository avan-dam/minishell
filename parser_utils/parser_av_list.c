/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_av_list.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-dam <avan-dam@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/04 11:10:44 by avan-dam      #+#    #+#                 */
/*   Updated: 2021/03/08 18:56:46 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int 	fill_av_more(t_mini *mini, int j, int k)
{
	while (mini->cmd_part[j] && (mini->cmd_part[j] != ' ' 
		|| check_tokens(ft_substr(mini->cmd_part, k, j - k), mini, 0, 1) == NULL)) // && check tokens current part is not null
	{
		// printf("jo\n");
		if ((mini->cmd_part[j] == '>' || mini->cmd_part[j] == '<')
			&& mini->cmd_part[j + 1] != '\''
			&& mini->cmd_part[j + 1] != '>'
			&& mini->cmd_part[j + 1] != '"' && check_tokens(ft_substr(mini->cmd_part, k, j - k + 1), mini, 0, 1) != NULL)
{
				// printf("in ft_substr(mini->cmd_part, k, j - k + 1)[%s] check_tokens(ft_substr(mini->cmd_part, k, j - k + 1), mini, 0, 0)[%s]\n", ft_substr(mini->cmd_part, k, j - k + 1), check_tokens(ft_substr(mini->cmd_part, k, j - k + 1), mini, 0, 1));
				break ;
}
		j++;
		// printf("end\n");
	}
	return (j);
}

void	fill_av_list(t_base *new, t_mini *mini, int j, int l)
{
	int		k;
	char	*temp;

	k = 0;
	// printf("mini->cmd_part[%s]\n", mini->cmd_part);
	while (l != new->size)
	{
		if (mini->cmd_part[j] == '\0')
			new->av[l] = NULL;
		else
		{
			while (mini->cmd_part[j] == ' ')
				j++;
			k = j;
			j = fill_av_more(mini, j, k);
			// printf("j return then check\n");
			if ((mini->cmd_part[j] == '>' || mini->cmd_part[j] == '<')
				&& mini->cmd_part[j + 1] != '>' && check_tokens(ft_substr(mini->cmd_part, k, j - k + 1), mini, 0, 0) != NULL)
			{
				// printf("inin\n");
				new->av[l] = ft_substr(mini->cmd_part, k, j - k + 1);
				j++;
			}
			else
				new->av[l] = ft_substr(mini->cmd_part, k, j - k);
			// printf("new->av[l][%s]\n", new->av[l]);
			temp = new->av[l];
			new->av[l] = mem_check_tkns(temp, mini, 0, 0);
			// printf("2new->av[l][%s]\n", new->av[l]);
			if (new->av[l] == NULL)
				return ; // do something return -1
			// printf("loop go\n");
		}
		l++;
	}
}

static void	more_av_list(t_base *new, t_mini *mini, t_base **ptr, char *line)
{
	new->size = mini->numb_cmds;
	new->prev = NULL;
	new->next = NULL;
	new->av[mini->numb_cmds] = NULL;
	fill_av_list(new, mini, 0, 0);
	new->type = mini->type_end;
	new->av[0] = ft_strtolower(new->av[0]);
	ft_lstadd_back_base(ptr, new);
	free(line);
}

int	create_av_list(t_base **ptr, char *line, t_mini *mini)
{
	int		numb_characters;
	t_base	*new;
	// char	*temp;

	if (mini->cmd_part)
		free(mini->cmd_part);
	numb_characters = no_of_commands(line, mini, 0, 1);
	// temp = mini->cmd_part;
	// mini->cmd_part = mem_check_tkns(temp, mini, 0, 0);
	// if (mini->cmd_part == NULL)
	// 	return (-1);
	new = (t_base *)malloc(sizeof(t_base));
	if (new == NULL)
		return (-1);
	new->av = (char **)malloc(sizeof(char *) * (mini->numb_cmds + 1));
	if (new->av == NULL)
		return (-1);
	more_av_list(new, mini, ptr, line);
	return (numb_characters);
}
