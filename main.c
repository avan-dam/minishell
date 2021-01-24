/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/17 22:36:40 by salbregh      #+#    #+#                 */
/*   Updated: 2021/01/24 21:10:09 by salbregh      ########   odam.nl         */
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

static void		try_execve(t_base *ptr, char **envp)
{
	pid_t		pid;
	int			status;
	int			piped;

	piped = 0;
	if (ptr->type == TYPE_PIPE || (ptr->prev && ptr->prev->type == TYPE_PIPE))
	{
		piped = 1;
		if (pipe(ptr->fd))
			exit (0); // change
	}
	if ((pid = fork()) < 0)
		exit (0); // change
	if (pid == 0) // child process
	{
		printf("GOES IN CHILD PROCES\n");
		if (ptr->type == TYPE_PIPE && dup2(ptr->fd[1], STDOUT) < 0)
			printf("CASE 1\n");
			// exit (0); // change
		if (ptr->prev && ptr->prev->type == TYPE_PIPE && dup2(ptr->prev->fd[0], STDIN) < 0)
			printf("CASE 2\n");
			// exit (0); // change
		if ((execve(ptr->argv[0], ptr->argv, envp)) < 0)
			printf("CASE 3\n");
			// exit (0); // change
		exit (EXIT_SUCCESS); // closes process with succes // change
	}
	else // parent process
	{
		waitpid(pid, &status, 0);
		if (piped)
		{
			close(ptr->fd[1]);
			if (!ptr->next || ptr->next->type == TYPE_BREAK) // end proces if no next or type is break
				close(ptr->fd[1]);
		}
		if (ptr->prev && ptr->prev->type == TYPE_PIPE)
			close(ptr->prev->fd[0]);
	}
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

static void	exec_cmds(t_base *ptr, char **envp, t_mini *mini)
{
	t_base	*tmp;

	tmp = ptr;
	while (tmp)
	{
		// printf("the argument going in: %s\n", tmp->argv[0]);
		if ((ft_strcmp(tmp->argv[0], "echo")) == 0 || (ft_strcmp(tmp->argv[0], "/bin/echo") == 0))
			ft_echo(tmp);
		else if (ft_strcmp(tmp->argv[0], "cd") == 0)
			ft_cd(tmp, mini);
		else if ((ft_strcmp(tmp->argv[0], "pwd") == 0) || (ft_strcmp(tmp->argv[0], "/bin/pwd") == 0))
			ft_pwd(mini);
		else if (ft_strcmp(tmp->argv[0], "export") == 0)
			ft_export(tmp, mini);
		else if (ft_strcmp(tmp->argv[0],"unset") == 0)
			ft_unset(mini, tmp->argv[1]);
		else if (ft_strcmp(tmp->argv[0], "env") == 0)
			ft_lstprint(mini->env1, mini);
		else if (ft_check_notbultin(tmp->argv[0], mini) == 1)
			try_execve(tmp, envp);
		else
			unvalid_identifier(tmp->argv[0], mini);
		tmp = tmp->next;
	}
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
	ft_set_array(mini);
	while (line[i])
	{
		while (line[i] == ';' || line[i] == ' ')
			i++;
		i = i + parse_this_shit(&ptr, &line[i], mini);
		if (!line[i])
			break ;
		else
			i++;
	}
	// while(ptr)
	// {			
	// 	printf("=================\n");
	// 	for (i = 0; i < ptr->size; i++)
	// 		printf("the argument: %s\n", ptr->argv[i]);
	// 	printf("TYPE: %d\n", ptr->type);
	// 	printf("SIZE: %d\n", ptr->size);
	// 	printf("=================\n");
	// 	ptr = ptr->next;
	// }
	if (ptr)
		exec_cmds(ptr, envp, mini);
	// fix leaks
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
	ft_set_array(&mini); // check use of
	ft_set_env(argv, envp, &mini);
	while (lineret)
	{
		ft_putstr("> "); // the bash prompt
		if ((lineret = get_next_line(1, &line)) < 0)
			return (-1);
		split_this_shit(line, &mini, envp);
		free(line);
		line = NULL;
	}	
	free(line);
	line = NULL;
	return (0);
}