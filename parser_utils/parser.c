/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 16:03:26 by salbregh      #+#    #+#                 */
/*   Updated: 2021/02/15 13:59:49 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	no_of_commands(char *line, t_mini *mini, int i, int numb)
{
	line = ft_strtrim(line, " ");
	while (line[i] && ((line[i] != '|' && line[i] != ';') ||
	(check_tokens(ft_substr(line, 0, i), mini, 0, 1) == NULL)))
	{
		if (line[i] == ' ')
		{
			while (line[i] == ' ')
				i++;
			if ((line[i] == '|' || line[i] == ';') &&
			(check_tokens(ft_substr(line, 0, i), mini, 0, 1) != NULL))
			{
				mini->numb_cmds = numb;
				mini->cmd_part = ft_substr(line, 0, i);
				if (line[i] == '|')
					mini->type_end = TYPE_PIPE;
				else if (line[i] == ';')
					mini->type_end = TYPE_BREAK;
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
	mini->numb_cmds = numb;
	mini->cmd_part = ft_substr(line, 0, i);
	mini->type_end = TYPE_END;
	return (i);
}

static void	fill_argv_list(t_base *new, t_mini *mini, int j, int l, int k)
{
	while (l != new->size)
	{
		if (mini->cmd_part[j] == '\0')
			new->argv[l] = ft_strdup("");
		else
		{
			while (mini->cmd_part[j] == ' ')
				j++;
			k = j;
			while (mini->cmd_part[j] != ' ' && mini->cmd_part[j])
			{
				if ((mini->cmd_part[j] == '>' || mini->cmd_part[j] == '<')
				&& mini->cmd_part[j + 1] != '\'' && mini->cmd_part[j + 1] != '>'
				&& mini->cmd_part[j + 1] != '"')
					break ;
				j++;
			}
			if ((mini->cmd_part[j] == '>' || mini->cmd_part[j] == '<')
			&& mini->cmd_part[j + 1] != '>')
			{
				new->argv[l] = ft_substr(mini->cmd_part, k, j - k + 1);
				j++;
			}
			else
				new->argv[l] = ft_substr(mini->cmd_part, k, j - k);
		}
		l++;
	}
}

static int	create_argv_list(t_base **ptr, char *line, t_mini *mini)
{
	int		numb_characters;
	int		size;
	t_base	*new;

	numb_characters = no_of_commands(line, mini, 0, 1);
	size = mini->numb_cmds;
	mini->cmd_part = check_tokens(mini->cmd_part, mini, 0, 0);
	if (mini->cmd_part == NULL)
		return (1);
	new = (t_base *)malloc(sizeof(t_base));
	new->argv = (char **)malloc(sizeof(char *) * (size + 1));
	if (new->argv == NULL)
		return (-1); // should exit program AND DOES NOT
	new->size = size;
	new->prev = NULL;
	new->next = NULL;
	new->argv[size] = NULL;
	fill_argv_list(new, mini, 0, 0, 0);
	new->type = mini->type_end;
	if (mini->cmd_part)
	{
		free(mini->cmd_part);
		mini->cmd_part = NULL;
	}
	ft_lstadd_back_base(ptr, new);
	return (numb_characters);
}

int			parse_input_string(char *line, t_mini *mini, char **envp)
{
	t_base		*ptr;
	int			i;
	int			k;

	ptr = NULL;
	i = 0;
	if (check_tokens(line, mini, 0, 0) == NULL)
		return (-2);
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		k = create_argv_list(&ptr, &line[i], mini);
		i = i + k;
		if (!line[i])
			break ;
		else
			i++;
	}
	if (ptr)
		if (exec_cmds(ptr, envp, mini) == -1)
		{
			ft_baseclear(&ptr);
			free(ptr);
			return (-1);
		}
	ft_baseclear(&ptr);
	free(ptr);
	return (0);
}
