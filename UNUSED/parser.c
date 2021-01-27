/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-dam <avan-dam@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/03 17:24:36 by avan-dam      #+#    #+#                 */
/*   Updated: 2021/01/20 12:41:50 by salbregh      ########   odam.nl         */
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
	while (line[i] != '\n' && line[i] != '\0' && line[i] != ' '&& line[i] != '<' && line[i] != '>')
		i++;
	mini->command = (char *)malloc(sizeof(char) * i + 1); //free
	while (j < i)
	{
		mini->command[j] = line[j];
		j++;
	}
	mini->command[j] = '\0';
	while(line[i] == '>' || line[i] == '<')
		i--;
	ft_find_more(line, mini, j, i);
	newnode = ft_lstnew(mini->command, mini->more);
	ft_lstadd_back(&mini->run2, newnode);
	// printf("mini->command[%s], mini->more [%s]\n", mini->command, mini->more);
	return ;
}

static int		ft_check_notbultin(char *command, t_mini *mini)
{
	int i;
	
	i = 0;
	while (mini->notbuiltin[i] != NULL)
	{
		if (ft_strcmp(command, mini->notbuiltin[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

static int		ft_parse_input(char *command, char *more, t_mini *mini, char **envp, t_piper *piper)
{
	if (piper->check == 1)
	{
		printf("PIPE HERE\n");
		if (pipe(piper->fd) == -1)
			return (-1); // ERROR WITH PIPE
	}
	if (ft_strcmp(command, "echo") == 0 || (ft_strcmp(command, "/bin/echo") == 0))
		ft_echo(more, mini, piper);
	else if (ft_strcmp(command, "cd") == 0)
		ft_cd(mini);
	else if ((ft_strcmp(command, "pwd") == 0) || (ft_strcmp(command, "/bin/pwd") == 0))
		ft_pwd(mini);
	else if (ft_strcmp(command, "export") == 0)
		ft_export(mini, more);
	else if (ft_strcmp(command, "unset") == 0)
		ft_unset(mini, more);
	else if (ft_strcmp(command, "env") == 0)
		ft_lstprint(mini->env1, mini);
	else if (ft_check_notbultin(command, mini) == 1)
		ft_execve(mini, envp, piper);
	else if (ft_strcmp(command, "exit") == 0)
		return (-1);
	else
		unvalid_identifier(command, mini);
	return (0);
}

static int		ft_divide_command(char *line, t_mini *mini, char **envp)
{
	int		i;
	char	*current;
	t_piper	piper;

	ft_memset(&piper, 0, sizeof(piper));
	while ((ft_strcmp("", line) != 0))
	{
		line = ft_strtrim(line, " ");
		// printf("line: %s\n", line);
		i = ft_strlen(line);
		if (ft_strchr_numb(line, '|', 0) != -1)
		{
			piper.check = 1;
			i = ft_strchr_numb(line, '|', 0);
		}
		if ((ft_strchr_numb(line, ';', 0) < i) && (ft_strchr_numb(line, ';', 0) != -1))
			i = ft_strchr_numb(line, ';', 0);
		current = ft_substr(line, 0, i);
		line = ft_substr(line, i + 1, ft_strlen(line) - i);
		current = ft_check_dolla_quotes(current, mini, 0);
		if (current == NULL)
			return (-2);
		ft_find_command(current, mini);
		// if (ft_parse_input(mini->command, mini->more, mini, envp) == -1)
		// 	return (-1);
		(void)envp;
		if (numb_char(mini->more, '>') != 0 || numb_char(mini->more, '<') != 0)
            ft_redir(mini, 0);
		if (ft_parse_input(mini->command, mini->more, mini, envp, &piper) == -1)
			return (-1);
		mini->command = NULL;
		mini->more = NULL;
		if (mini->stdout != 1)
			close(mini->stdout);
	}
	return (0);
}

int		ft_start_parsing(char *line, t_mini *mini, char **envp)
{
	if (ft_divide_command(line, mini, envp) == -1)
	{
		ft_lstclear(&mini->env1);
		ft_memset(&mini, 0, sizeof(mini));
		return (-1);
	}
	// put ft_parse input here?
	return (0);
}