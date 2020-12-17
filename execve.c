/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execve.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/17 14:10:52 by ambervandam   #+#    #+#                 */
/*   Updated: 2020/12/17 14:40:44 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				ft_ls(t_mini *mini, char *more)
{
    (void)mini;
    (void)more;
    int y;
    char *argv[] = { "/bin/ls", NULL };
    char *envp[] = { NULL };
    // if (ft_strcmp(more, "la") == 0)
    //     argv = { "/bin/ls", "-la", NULL };
    // else if (ft_strcmp(more, "") == 0)
    //     argv = { "/bin/ls", NULL };
    // else
    //     return (0);
    y = execve("/bin/ls", argv, envp);
    if (y == -1)
        return (-1); 
        // fprintf(stderr, "Error: %s\n", strerror(errno));
    return 0;
}