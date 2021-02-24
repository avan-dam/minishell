/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 16:03:26 by salbregh      #+#    #+#                 */
/*   Updated: 2021/02/24 17:15:28 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	no_of_commands(char *line, t_mini *mini, int i, int numb)
{
	char	*temp;
	char	*temp3;

	line = ft_trim_paths(line, " ");
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
	mini->numb_cmds = numb;
	temp3 = line;
	line = ft_substr(temp3, 0, i);
	mini->cmd_part = line;
	free(temp3);
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
					&& mini->cmd_part[j + 1] != '\'' && mini->cmd_part[j + 1] != '>'
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

static int	create_av_list(t_base **ptr, char *line, t_mini *mini)
{
	int		numb_characters;
	int		size;
	t_base	*new;

	numb_characters = no_of_commands(line, mini, 0, 1);
	size = mini->numb_cmds;
	// SEGFAULT IN THIS
	mini->cmd_part = check_tokens(mini->cmd_part, mini, 0, 0);
	if (mini->cmd_part == NULL)
		return (1);
		// PART
	// char *tmp = check_tokens(mini->cmd_part, mini, 0, 0);
	// if (tmp == NULL)
	// {	
	// 	free(tmp);
	// 	// printf("exit statement is : %d\n", mini->exit);
	// 	return (1);
	// }
	// // printf("exit statement is : %d\n", mini->exit);
	// free(mini->cmd_part);
	// mini->cmd_part = tmp;
	// free(tmp);
	new = (t_base *)malloc(sizeof(t_base));
	new->av = (char **)malloc(sizeof(char *) * (size + 1));
	if (new->av == NULL)
		return (-1); // should exit program AND DOES NOT
	new->size = size;
	new->prev = NULL;
	new->next = NULL;
	new->av[size] = NULL;
	fill_av_list(new, mini, 0, 0, 0);
	new->type = mini->type_end;
	if (mini->cmd_part)
	{
		free(mini->cmd_part);
		mini->cmd_part = NULL;
	}
	new->av[0] = ft_strtolower(new->av[0]);
	ft_lstadd_back_base(ptr, new);
	return (numb_characters);
}

int	parse_input_string(char *line, t_mini *mini, char **envp)
{
	t_base		*ptr;
	char		*tmp;
	int			i;
	int			k;

	i = 0;
	ptr = NULL;
	tmp = check_tokens(line, mini, 0, 0);
	if (tmp == NULL)
	{
		free(tmp);
		return (0);
	}
	free(tmp);
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
