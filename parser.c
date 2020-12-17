/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-dam <avan-dam@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/03 17:24:36 by avan-dam      #+#    #+#                 */
/*   Updated: 2020/12/17 18:26:40 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_find_more(char *line, t_mini *mini, int j, int i)
{
	int k;
	
	k = 0;
	if (line[j])
	{
		j++; // would skip the space after command > trim all spaces between or send to new function!!
		while (line[j] != '\0')
			j++;
	}
	else
		return;
	i++;
	k = 0;
	mini->more = (char *)malloc(sizeof(char) * (j - i + 1)); //free
	while (k < (j - i))
	{
		mini->more[k] = line[i + k];
		k++;
	}
	mini->more[k] = '\0';
	mini->more = ft_strtrim(mini->more, " ");
	return ;
}

static void	ft_find_command(char *line, t_mini *mini)
{
	int i;
	int j;
	t_list *newnode;

	i = 0;
	j = 0;
	while (*line == ' ')
		line++;
	while (line[i] != '\n' && line[i] != '\0' && line[i] != ' ')
		i++;
	mini->command = (char *)malloc(sizeof(char) * i + 1); //free
	while (j < i)
	{
		mini->command[j] = line[j];
		j++;
	}
	mini->command[j] = '\0';
	ft_find_more(line, mini, j, i);
	newnode = ft_lstnew(mini->command, mini->more);
	ft_lstadd_back(&mini->run2, newnode);
	return ;
}

static int		ft_parse_input(char *command, char *more, t_mini *mini)
{
	if (ft_strcmp(command, "echo") == 0)
	{
		// printf("in echo with %s\n", more);
		ft_echo(more);
	}
	else if (ft_strcmp(command, "cd") == 0)
		ft_cd(mini);
	else if ((ft_strcmp(command, "pwd") == 0) || (ft_strcmp(command, "/bin/pwd") == 0))
		ft_pwd(mini);
	else if (ft_strcmp(command, "export") == 0)
	{
		// printf("in export with %s\n", more);
		ft_export(mini, more);
	}
	else if (ft_strcmp(command, "unset") == 0)
		ft_unset(mini, more);
	else if (ft_strcmp(command, "env") == 0)
		ft_lstprint(mini->env1);
	else if ((ft_strcmp(command, "ls") == 0) || (ft_strcmp(command, "/bin/ls") == 0))
		ft_ls(mini, more);
	else if (ft_strcmp(command, "exit") == 0)
	{
		printf("I got an exit baby\n");
		// line = NULL;
		return (-1);
	}
	else
		printf("bash: %s: command not found\n", command);
	return (0);
}

static int		ft_divide_command(char *line, t_mini *mini)
{
	int i;
	char *current;

	while ((ft_strcmp("", line) != 0))
	{
		line = ft_strtrim(line, " ");
		i = ft_strlen(line);
		if (ft_strrch_numb(line, '|') != -1)
			i = ft_strrch_numb(line, '|');
		if ((ft_strrch_numb(line, ';') < i) && (ft_strrch_numb(line, ';') != -1))
			i = ft_strrch_numb(line, ';');
		current = ft_substr(line, 0, i);
		line = ft_substr(line, i + 2, ft_strlen(line) - i);
		current = ft_check_dolla(current, mini);
		ft_find_command(current, mini);
		if (ft_parse_input(mini->command, mini->more, mini) == -1)
			return (-1);
		mini->command = NULL;
		mini->more = NULL;
	}
	return (0);
}

int		main(int argc, char **argv, char **envp)
{
	char	*line;
	int		lineret;
	t_mini	mini;

	if (argc > 1)
		return (-1); // are we implementing an error function?
	ft_memset(&mini, 0, sizeof(t_mini));
	ft_set_env(argv, envp, &mini);
	while (1)
	{
		ft_putstr("> ");
		lineret = get_next_line(1, &line);
		if (lineret < 0)
			ft_putstr("error");
		if (ft_divide_command(line, &mini) == -1)
			return (0);
		// line = NULL;
		free(line);
		// system("leaks minishell");
	}	
	return (0);
}
