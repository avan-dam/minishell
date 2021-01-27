/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/17 22:36:40 by salbregh      #+#    #+#                 */
/*   Updated: 2021/01/27 18:08:22 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void		execve_commands(t_base *ptr, char **envp)
// {
// 	pid_t		pid;
// 	int			status;
// 	int			piped;

// 	piped = 0;
// 	if (ptr->type == TYPE_PIPE || (ptr->prev && ptr->prev->type == TYPE_PIPE))
// 	{
// 		piped = 1;
// 		if (pipe(ptr->fd))
// 		{
// 			printf("Error in piping\n");
// 			exit (0); // change
// 		}
// 	}
// 	if ((pid = fork()) < 0)
// 	{
// 		printf("Error in forking\n");
// 		exit (0); // change
// 	}
// 	if (pid == 0) // child process
// 	{
// 		printf("GOES IN CHILD PROCES\n");
// 		if (ptr->type == TYPE_PIPE && dup2(ptr->fd[1], STDOUT) < 0)
// 			printf("CASE 1\n");
// 		if (ptr->prev && ptr->prev->type == TYPE_PIPE && dup2(ptr->prev->fd[0], STDIN) < 0)
// 			printf("CASE 2\n");
// 		if ((execve(ptr->argv[0], ptr->argv, envp)) < 0)
// 			printf("CASE 3\n");
// 		exit (EXIT_SUCCESS); // closes process with succes // change
// 	}
// 	else // parent process
// 	{
// 		waitpid(pid, &status, 0);
// 		if (piped)
// 		{
// 			close(ptr->fd[1]);
// 			if (!ptr->next || ptr->next->type == TYPE_BREAK) // end proces if no next or type is break
// 				close(ptr->fd[1]);
// 		}
// 		if (ptr->prev && ptr->prev->type == TYPE_PIPE)
// 			close(ptr->prev->fd[0]);
// 	}
// }

// static int		ft_check_notbultin(char *command, t_mini *mini)
// {
// 	int i;
	
// 	i = 0;
// 	while (mini->notbuiltin[i] != NULL)
// 	{
// 		if (ft_strcmp(command, mini->notbuiltin[i]) == 0)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// static void	exec_cmds(t_base *ptr, char **envp, t_mini *mini)
// {
// 	t_base	*tmp;

// 	tmp = ptr;
// 	while (tmp)
// 	{
// 		if ((ft_strcmp(tmp->argv[0], "echo")) == 0 || (ft_strcmp(tmp->argv[0], "/bin/echo") == 0))
// 			ft_echo(tmp);
// 		else if (ft_strcmp(tmp->argv[0], "cd") == 0)
// 			ft_cd(tmp, mini);
// 		else if ((ft_strcmp(tmp->argv[0], "pwd") == 0) || (ft_strcmp(tmp->argv[0], "/bin/pwd") == 0))
// 			ft_pwd(mini);
// 		else if (ft_strcmp(tmp->argv[0], "export") == 0)
// 			ft_export(tmp, mini);
// 		else if (ft_strcmp(tmp->argv[0],"unset") == 0)
// 			ft_unset(mini, tmp->argv[1]);
// 		else if (ft_strcmp(tmp->argv[0], "env") == 0)
// 			ft_lstprint(mini->env1, mini);
// 		else if (ft_check_notbultin(tmp->argv[0], mini) == 1) // also builtins should go into execve
// 			execve_commands(tmp, envp);
// 		else
// 			unvalid_identifier(tmp->argv[0], mini);
// 		tmp = tmp->next;
// 	}
// }

int		main(int argc, char **argv, char **envp)
{
	char	*line;
	int		lineret;
	t_mini	mini;

	line = NULL;
	lineret = 1;
	if (argc == 1)
	{
		ft_memset(&mini, 0, sizeof(t_mini));
		ft_set_array(&mini); // check use of
		ft_set_env(argv, envp, &mini);
		while (lineret)
		{
			ft_putstr_fd("> ", mini.stdout); // the bash prompt
			if ((lineret = get_next_line(1, &line)) < 0)
				return (-1);
			parse_input_string(line, &mini, envp);
			free(line);
			line = NULL;
		}
	}
	free(line);
	line = NULL;
	return (0);
}