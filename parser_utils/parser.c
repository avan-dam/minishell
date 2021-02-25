/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 16:03:26 by salbregh      #+#    #+#                 */
/*   Updated: 2021/02/25 15:07:42 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	no_of_commands(char *line, t_mini *mini, int i, int numb)
{
	char	*temp;
	// char	*temp3;

	while (line[i] && ((line[i] != '|' && line[i] != ';')
			|| (mem_check_tkns(ft_substr(line, 0, i), mini, 0, 1) == NULL)))
	{
		if (line[i] == ' ')
		{
			while (line[i] == ' ')
				i++;
			if ((line[i] == '|' || line[i] == ';')
				&& (mem_check_tkns(ft_substr(line, 0, i), mini, 0, 1) != NULL))
			{
				mini->numb_cmds = numb;
				temp = ft_substr(line, 0, i);
				mini->cmd_part = temp;
				free(temp);
				if (line[i] == '|')
					mini->type_end = T_PIPE;
				else if (line[i] == ';')
					mini->type_end = T_BREAK;
				return (i);
			}
			numb++;
		}
		if ((line[i] == '>' || line[i] == '<') && line[i + 1] != ' '
			&& line[i + 1] != '"' && line[i + 1] != '\'' && line[i + 1] != '>'
			&& line[i + 1] != '\0')
			numb++;
		i++;
	}
	// mini->numb_cmds = numb;
	// temp3 = line;
	// line = ft_substr(temp3, 0, i);
	// mini->cmd_part = line;
	// free(temp3);
	mini->cmd_part = mem_substr(line, 0, i);
	mini->type_end = T_END;
	return (i);
}

static void	fill_av_list(t_base *new, t_mini *mini, int j, int l, int k)
{
	while (l != new->size)
	{
		if (mini->cmd_part[j] == '\0')
			new->av[l] = NULL;
		else
		{
			while (mini->cmd_part[j] == ' ')
				j++;
			k = j;
			while (mini->cmd_part[j] != ' ' && mini->cmd_part[j])
			{
				if ((mini->cmd_part[j] == '>' || mini->cmd_part[j] == '<')
					&& mini->cmd_part[j + 1] != '\''
					&& mini->cmd_part[j + 1] != '>'
					&& mini->cmd_part[j + 1] != '"')
					break ;
				j++;
			}
			if ((mini->cmd_part[j] == '>' || mini->cmd_part[j] == '<')
				&& mini->cmd_part[j + 1] != '>')
			{
				new->av[l] = ft_substr(mini->cmd_part, k, j - k + 1);
				j++;
			}
			else
				new->av[l] = ft_substr(mini->cmd_part, k, j - k);
		}
		l++;
	}
}

static void 	create_av_list_more(t_base *new, t_mini *mini, t_base **ptr)
{
	new->size = mini->numb_cmds;
	new->prev = NULL;
	new->next = NULL;
	new->av[mini->numb_cmds] = NULL;
	fill_av_list(new, mini, 0, 0, 0);
	new->type = mini->type_end;
	if (mini->cmd_part)
	{
		free(mini->cmd_part);
		mini->cmd_part = NULL;
	}
	new->av[0] = ft_strtolower(new->av[0]);
	ft_lstadd_back_base(ptr, new);
}

static int	create_av_list(t_base **ptr, char *line, t_mini *mini)
{
	int		numb_characters;
	t_base	*new;

	line = ft_trim_paths(line, " ");
	numb_characters = no_of_commands(line, mini, 0, 1);
	// mini->cmd_part = mem_check_tkns(mini->cmd_part, mini, 0, 0);
	mini->cmd_part = check_tokens(mini->cmd_part, mini, 0, 0);
	if (mini->cmd_part == NULL)
		return (-1);
	new = (t_base *)malloc(sizeof(t_base));
	new->av = (char **)malloc(sizeof(char *) * (mini->numb_cmds + 1));
	if (new->av == NULL)
		return (-1);
	create_av_list_more(new, mini, ptr);
	return (numb_characters);
}

static int	ft_loop_to_cmds(t_base *ptr, char **envp, t_mini *mini, char *line)
{
	free(line);
	if (ptr)
	{
		if (exec_cmds(ptr, envp, mini) == -1)
		{
			ft_baseclear(&ptr);
			free(ptr);
			return (-1);
		}
	}
	ft_baseclear(&ptr);
	free(ptr);
	return (0);
}

int	parse_input_string(char *line, t_mini *mini, char **envp, int i)
{
	t_base		*ptr;
	int			k;

	ptr = NULL;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		k = create_av_list(&ptr, &line[i], mini);
		if (k == -1)
		{
			mini->exit = 1;
			return (0);
		}
		i = i + k;
		if (!line[i])
			break ;
		else
			i++;
	}
	return (ft_loop_to_cmds(ptr, envp, mini, line));
}
