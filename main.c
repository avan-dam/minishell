/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/17 22:36:40 by salbregh      #+#    #+#                 */
/*   Updated: 2021/01/29 23:02:17 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_set_env(argv, envp, &mini);
		while (lineret)
		{
			ft_putstr_fd("> ", mini.stdout); // the bash prompt
			if ((lineret = get_next_line(mini.stdin, &line)) < 0)
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