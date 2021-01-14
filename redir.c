/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/12 13:52:12 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/01/14 19:30:29 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_redir(t_mini *mini, int d)
{
	char *filename;
	int i;
	int fd;

    // Below is only for '>' and '>>' not '<' implement function for that
	// printf("in redir with mini->more %s\n", mini->more);
	while ((i = ft_strchr_numb(mini->more, '>', 0)) != -1)
	{
		filename = ft_substr(mini->more, i + 1, ft_strlen(mini->more) - i - 1);
		mini->more = ft_substr(mini->more, 0, i);
		if (filename == NULL)
		{
			filename = mini->more;
			mini->more = NULL;
		}
		if (filename[0] == '>')
		{
			if (filename[1] == '&')
				return (unvalid_identifier("unexpected token `&'", mini));
			filename = ft_substr(filename, 1, ft_strlen(filename) - 1);
			d = 1;
		}
		if (filename[0] == '&')
		{
			filename = ft_substr(filename, 1, ft_strlen(filename) - 1);
			mini->stdout = ft_atoi(filename);
			if (mini->stdout >= 3)
				return (unvalid_identifier("Bad file descriptor", mini));
		}
		else if (d == 0)
			fd = open(filename, O_RDWR|O_CREAT|O_TRUNC, 0666);
		else if (d == 1)
			fd = open(filename, O_RDWR|O_CREAT|O_APPEND, 0666);
		mini->stdout = fd;
		if (ft_strcmp(mini->more, "") == 0)
			mini->more = NULL;
    	mini->more = ft_strtrim(mini->more, " ");
		// printf("mini->command[%s], mini->more [%s]\n", mini->command, mini->more);
	}
	return (0);
}