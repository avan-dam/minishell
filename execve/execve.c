/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execve.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 16:41:50 by salbregh      #+#    #+#                 */
/*   Updated: 2021/04/13 11:05:39 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	prep_child_proces(t_base *ptr, t_mini *mini, char **envp)
{
	if (child_process(ptr, mini, envp, 0) == 1)
	{	
		if (ft_strcmp(ptr->av[0], "~") == 0)
			exit (mini->exit);
		exit (EXIT_FAILURE);
	}
	if (ft_strcmp(ptr->av[0], "exit") == 0 || ft_strcmp(ptr->av[0], "~") == 0)
		exit (mini->exit);
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
		prep_child_proces(ptr, mini, envp);
		exit(EXIT_SUCCESS);
	}
	else
		parent_proces(pid, mini, ptr, piped);
}

static int	tilda_check(char *home, char *ptrstr)
{
	char	*sub;

	sub = ft_substr(ptrstr, 1, ft_strlen(ptrstr) - 1);
	if (ft_strcmp(home, sub) == 0)
	{	
		free(sub);
		return (-1);
	}
	free(sub);
	return (1);
}

static int	execve_more(t_base *ptr, t_mini *mini, char **envp)
{
	char	*home;
	char	*tmp;

	tmp = mini->home;
	home = ft_substr(tmp, 1, ft_strlen(tmp) - 1);
	if (ft_strcmp(ptr->av[0], "exit") == 0)
	{
		free(home);
		return (sort_exit_statement(ptr, mini, 1));
	}
	else if ((((ptr->av[0][0] == '.' && ptr->av[0][1] == '/')
		|| ptr->av[0][0] == '.' || ptr->av[0][0] == '/')
			|| ft_strncmp(ptr->av[0], home, ft_strlen(home)) == 0)
		&& tilda_check(home, ptr->av[0]) != -1)
		execves(ptr, envp, mini);
	else if (look_for_non_builtin(ptr, 0, mini, envp) == 2)
		unvalid_ident(ptr->av[0], mini, 127);
	else
		execves(ptr, envp, mini);
	free(home);
	return (0);
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
		exec_builtin(ptr, mini, envp);
	else if (execve_more(ptr, mini, envp) == -1)
		return (-1);
	return (0);
}
