/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   newparser.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 16:03:26 by salbregh      #+#    #+#                 */
/*   Updated: 2021/01/27 16:29:25 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

static int	number_of_commands(char *line, t_mini *mini)
{
	int		i;
	int		numb;
	char	*tmp;

	i = 0;
	tmp = line;
	mini->numb_cmds = 0;
	numb = 1;
	// in here quotes should be checked, so echo "hello this is one command" will not be split on spaces
	while (tmp[i] && tmp[i] != '|' && tmp[i] != ';')
	{
		if (tmp[i] == ' ')
		{
			while (tmp[i] == ' ')
				i++;
			if (tmp[i] == '|' || tmp[i] == ';')
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
	return (i);
}

void			parse_input_string(char *line, t_mini *mini, char **envp)
{
	t_base		*ptr;
	int			i;

	ptr = NULL;
	i = 0;
	line = ft_strtrim(line, " ");
	ft_set_array(mini);
	while (line[i])
	{
		while (line[i] == ';' || line[i] == ' ')
			i++;
		i = i + put_commands_in_list(&ptr, &line[i], mini);
		if (!line[i])
			break ;
		else
			i++;
	}
	// while(ptr)
	// {
	// printf("Argument in list: \n")
	// 	for (i = 0; i < ptr->size; i++)
	// 		printf("the argument: %s\n", ptr->argv[i]);
	// 	printf("TYPE: %d\n", ptr->type);
	// 	printf("SIZE: %d\n", ptr->size);
	//	printf("end of argument in list\n\n");
	// 	ptr = ptr->next;
	// }
	if (ptr)
		exec_cmds(ptr, envp, mini);
	// fix leaks
}

