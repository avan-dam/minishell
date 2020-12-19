/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execve.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/17 14:10:52 by ambervandam   #+#    #+#                 */
/*   Updated: 2020/12/19 17:55:05 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_exceptions(t_mini *mini)
{
	if (ft_strcmp(mini->command, "ls") == 0)
		mini->command = "/bin/ls";	
}

int				ft_execve(t_mini *mini)
{
    char *argv[] = {mini->command, NULL};
    char *envp[] = {NULL};
    pid_t	pid;

	pid = fork();
	printf("Value of pid: %d\n", pid);
	ft_exceptions(mini);
	if (pid == -1)
	{
		ft_putstr("error in forking\n");
		return (-1);
	}
	else if (pid == 0)
	{
		if (execve(mini->command, argv, envp) < 0)
        	return (-1); 
		exit(0);
	}
	else
	{
		wait(NULL);
		return (0);
	}
    return 0;
}

// int				ft_ls(t_mini *mini, char *more)
// {
//     pid_t	pid;

// 	pid = fork();
// 	printf("Value of pid: %d\n", pid);
// 	if (pid == -1)
// 		ft_putstr("error in forking\n");
// 	else if (pid == 0)
//     (void)mini;
//     (void)more;
//     int y;
//     char *argv[] = { "/bin/ls", NULL };
//     char *envp[] = { NULL };
//     // if (ft_strcmp(more, "la") == 0)
//     //     argv = { "/bin/ls", "-la", NULL };
//     // else if (ft_strcmp(more, "") == 0)
//     //     argv = { "/bin/ls", NULL };
//     // else
//     //     return (0);
//     y = execve("/bin/ls", argv, envp);
//     if (y == -1)
//         return (-1); 
//         // fprintf(stderr, "Error: %s\n", strerror(errno));
//     return 0;
// }