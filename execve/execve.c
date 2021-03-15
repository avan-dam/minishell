/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execve.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 16:41:50 by salbregh      #+#    #+#                 */
/*   Updated: 2021/03/15 17:57:37 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	parent_proces(pid_t pid, t_mini *mini, t_base *ptr, int piped)
{
	int			status;

	waitpid(pid, &status, 0);
	mini->exit = WEXITSTATUS(status);
	if (piped)
	{
		close(ptr->fd[1]);
		if (ptr->type != T_PIPE)
			close(ptr->fd[0]);
	}
	if (ptr->prev && ptr->prev->type == T_PIPE)
		close(ptr->prev->fd[0]);
}

static int	child_process(t_base *ptr, t_mini *mini, char **envp)
{
	if (ft_is_builtin(ptr->av[0]) == 0 && look_for_non_builtin(ptr, 1) == 2)
		unvalid_ident(ptr->av[0], mini, 127);
	if (ptr->type == T_PIPE && dup2(ptr->fd[1], STDOUT) < 0)
		return (1);
	if (ptr->prev && ptr->prev->type == T_PIPE
		&& dup2(ptr->prev->fd[0], STDIN) < 0)
		return (1);
	if (ft_strcmp(ptr->av[0], "exit") != 0
		&& ft_is_builtin(ptr->av[0]) == 1)
		exec_builtin(ptr, mini);
	else if (execve(ptr->av[0], ptr->av, envp) < 0 || !ptr->av[1])
		return (1);
	else
		unvalid_ident(ptr->av[0], mini, 127);
	return (0);
}

static void	execves(t_base *ptr, char **envp, t_mini *mini)
{
	pid_t		pid;
	int			piped;

	piped = 0;
	if (ptr->type == T_PIPE || (ptr->prev && ptr->prev->type == T_PIPE))
	{
		piped = 1;
		if (pipe(ptr->fd))
			exit(0);
	}
	pid = fork();
	if (pid < 0)
		exit(0);
	if (pid == 0)
	{
		dup2(mini->stdin, STDIN);
		dup2(mini->stdout, STDOUT);
		if (child_process(ptr, mini, envp) == 1)
			exit (EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	else
		parent_proces(pid, mini, ptr, piped);
}

static int	execve_more(t_base *ptr, t_mini *mini, char **envp)
{
	if (ft_strcmp(ptr->av[0], "exit") == 0)
	{
		if (ptr->av[1] != NULL)
		{
			if (ft_is_str_int(ptr->av[1]) == 0)
				mini->exit = 255;
			else
			{
				mini->exit = ft_atoi(ptr->av[1]);
				if (ptr->av[2] != NULL)
					mini->exit = 1;
			}
		}
		return (-1);
	}
	else if (look_for_non_builtin(ptr, 0) == 2)
	{
		unvalid_ident(ptr->av[0], mini, 127);
	}
	else
		execves(ptr, envp, mini);
	return (0);
}

static void 	sort_struct_before_redir(t_base *ptr, t_mini *mini)
{
	char	*temp;
	int		i;

	i = 0;
	while (i < ptr->size && ptr->av[i])
	{
		while (i < ptr->size && ptr->av[i] && ((ptr->av[i][0] == '"'
					&& ptr->av[i][1] == '"' && ptr->av[i][2] == '\0')
				|| (ptr->av[i][0] == '\'' && ptr->av[i][1] == '\''
					&& ptr->av[i][2] == '\0')))
			i++;
	 	if (i < ptr->size && ptr->av[i] && ((i == 0)
				 || (ft_strcmp(ptr->av[0], "export") != 0
					&& ft_strcmp(ptr->av[0], "echo") != 0)))
		{
			temp = ptr->av[i];
			ptr->av[i] = ft_strtrim_backslash(temp, ' ');
			free(temp);
			ptr->av[i] = mem_check_tkns(ptr->av[i], mini, 0, 6);
		}
		i++;
	}
}

static void 	sort_struct_after_redir(t_base *ptr)
{
	int	i;

	i = 0;
	while (i < ptr->size && ptr->av[i])
	{
		if ((ptr->av[i][0] == '"' && ptr->av[i][1] == '"'
				&& ptr->av[i][2] == '\0') || (ptr->av[i][0] == '\''
				&& ptr->av[i][1] == '\'' && ptr->av[i][2] == '\0'))
		{
			free(ptr->av[i]);
			ptr->av[i] = ft_strdup("");
		}
		i++;
	}
}

int	exec_cmds(t_base *ptr, char **envp, t_mini *mini)
{
	if ((ptr == NULL) || (ptr->size == 0))
		return (0);
	sort_struct_before_redir(ptr, mini);
	ptr = ft_redir(mini, ptr);
	if (ptr == NULL)
		return (0);
	sort_struct_after_redir(ptr);
	while (ptr->size == 0)
	{
		ptr = ptr->next;
		if (ptr == NULL)
			return (0);
		ptr = ft_redir(mini, ptr);
	}
	if ((ptr->type == T_PIPE || (ptr->prev && ptr->prev->type == T_PIPE))
		&& ft_is_builtin(ptr->av[0]) == 1)
		execves(ptr, envp, mini);
	else if (ft_strcmp("", ptr->av[0]) == 0)
		return (0);
	else if (ft_strcmp(ptr->av[0], "exit") != 0 && ft_is_builtin(ptr->av[0]))
		exec_builtin(ptr, mini);
	else if (execve_more(ptr, mini, envp) == -1)
		return (-1);
	return (0);
}
