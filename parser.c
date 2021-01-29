/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 16:03:26 by salbregh      #+#    #+#                 */
/*   Updated: 2021/01/29 23:28:09 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	number_of_commands(char *line, t_mini *mini)
{
	int		i;
	int		numb;
	char	*tmp;

	i = 0;
	tmp = line;
	mini->numb_cmds = 0;
	numb = 1;
	while (tmp[i] && ((tmp[i] != '|' && tmp[i] != ';') || (ft_check_dolla_quotes(ft_substr(line, 0, i), mini, 0, 1) == NULL)))
	{
		if (tmp[i] == ' ')
		{
			while (tmp[i] == ' ')
				i++;
			if ((tmp[i] == '|' || tmp[i] == ';') && (ft_check_dolla_quotes(ft_substr(line, 0, i), mini, 0, 1) != NULL))
			{
				mini->numb_cmds = numb;
				mini->cmd_part = ft_substr(line, 0, i);
				if (tmp[i] == '|')
					mini->type_end = TYPE_PIPE;
				else if (tmp[i] == ';')
					mini->type_end = TYPE_BREAK;
				return (i);
			}
			numb++;
		}
		i++;
	}
	mini->numb_cmds = numb;
	mini->cmd_part = ft_substr(line, 0, i);
	mini->type_end = TYPE_END;
	return (i);
}

static int	put_commands_in_list(t_base **ptr, char *line, t_mini *mini)
{
	int		numb_characters;
	int		j;
	int		size;
	t_base	*new;

	numb_characters = number_of_commands(line, mini); // i is the number of characters
	size = mini->numb_cmds;
	mini->cmd_part = ft_check_dolla_quotes(mini->cmd_part, mini, 0, 0); //FIXXXXXX!!!
	new = (t_base *)malloc(sizeof(t_base));
	new->argv = (char **)malloc(sizeof(char *) * (size + 1));
	if (new->argv == NULL)
		return (-1); // should exit program
	new->size = size;
	new->prev = NULL;
	new->next = NULL;
	new->argv[size] = NULL;
	j = 0;
	int l = 0;
	while (l < size && mini->cmd_part[j])
	{
		while (mini->cmd_part[j] == ' ')
			j++;
		int	k = j;
		while (mini->cmd_part[j] != ' ' && mini->cmd_part[j])
			j++;
		new->argv[l] = ft_substr(mini->cmd_part, k, j - k);
		l++;
	}
	new->type = mini->type_end;
	ft_lstadd_back_new(ptr, new);
	return (numb_characters);
}

int			parse_input_string(char *line, t_mini *mini, char **envp)
{
	t_base		*ptr;
	int			i;

	ptr = NULL;
	i = 0;
	line = ft_strtrim(line, " ");
	if (ft_check_dolla_quotes(line, mini, 0, 0) == NULL)// if u remove this need to add in if line ==NULL return
			return (-2); // -1 is to exit whole thing this just goes to next promt and tells u you entered a multiline
	while (line[i])
	{
		while (line[i] == ' ') // deleted ;
			i++;
		i = i + put_commands_in_list(&ptr, &line[i], mini);
		if (!line[i])
			break ;
		else
			i++;
	}
	// t_base *tmp = ptr;
	// while(tmp)
	// {
	// 	printf("Argument in list: \n");
	// 	for (i = 0; i < tmp->size; i++)
	// 		printf("the argument: %s\n", tmp->argv[i]);
	// 	printf("TYPE: %d\n", tmp->type);
	// 	printf("SIZE: %d\n", tmp->size);
	// 	printf("end of argument in list\n\n");
	// 	tmp = tmp->next;
	// }
	if (ptr)
		if (exec_cmds(ptr, envp, mini) == -1)
			return (-1);
	return (0);
	// fix leaks
}

