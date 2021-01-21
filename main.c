/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/17 22:36:40 by salbregh      #+#    #+#                 */
/*   Updated: 2021/01/21 14:13:07 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_lstadd_back_new(t_base **ptr, t_base *new)
{
	t_base	*tmp;

	if (!(*ptr))
		*ptr = new;
	else
	{
		tmp = *ptr;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

static int	number_of_commands(char *line, t_mini *mini)
{
	int		i;
	int		numb;
	char	*tmp;

	i = 0;
	tmp = line;
	mini->numb_cmds = 0;
	numb = 1;
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

static int	parse_this_shit(t_base **ptr, char *line, t_mini *mini)
{
	int		i;
	int		j;
	int		size;
	t_base	*new;

	i = number_of_commands(line, mini); // returns number of characters
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
	printf("value of mini->cmd_part befor while loop: %s\n", mini->cmd_part);
	while (l < size && mini->cmd_part[j])
	{
		while (mini->cmd_part[j] == ' ')
			j++;
		int	k = j;
		while (mini->cmd_part[j] != ' ')
			j++;
		new->argv[l] = ft_substr(mini->cmd_part, k, j - k);
		l++;
	}
	new->type = mini->type_end;
	ft_lstadd_back_new(ptr, new);
	return (i);
}

static void	split_this_shit(char *line, t_mini *mini, char **envp)
{
	t_base	*ptr;
	int		i;

	(void)mini;
	(void)envp;

	ptr = NULL;
	i = 0;
	line = ft_strtrim(line, " ");
	while (line[i])
	{
		while (line[i] == ';' || line[i] == ' ') // go to next command if line begins with ;
			i++;
		i = i + parse_this_shit(&ptr, &line[i], mini); // ga naar locatie van eerste argument deel
		if (!line[i]) // if end of line
			break;
		else
			i++;
	}
	while(ptr)
	{			
		printf("=================\n");
		for (i = 0; i < ptr->size; i++)
			printf("the argument: %s\n", ptr->argv[i]);
		printf("TYPE: %d\n", ptr->type);
		printf("SIZE: %d\n", ptr->size);
		printf("=================\n");
		ptr = ptr->next;
	}
}

int		main(int argc, char **argv, char **envp)
{
	char	*line;
	int		lineret;
	t_mini	mini;

	line = NULL;
	lineret = 1;
	if (argc > 1) // no argument should be added to the excutable
		return (-1);
	ft_memset(&mini, 0, sizeof(t_mini));
	// ft_set_array(&mini); // check use of
	ft_set_env(argv, envp, &mini);
	while (lineret)
	{
		ft_putstr("> "); // the bash prompt
		if ((lineret = get_next_line(1, &line)) < 0)
			return (-1);
		split_this_shit(line, &mini, envp);
		// if (ft_start_parsing(line, &mini, envp) < 0)
		// 	return (-1);
		ft_lstprintold(mini.run2);
		free(mini.run2); // free the list of line
		mini.run2 = NULL;
		free(line);
		line = NULL;
	}	
	free(line);
	line = NULL;
	return (0);
}