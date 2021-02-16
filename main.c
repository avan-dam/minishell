/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/17 22:36:40 by salbregh      #+#    #+#                 */
/*   Updated: 2021/02/16 14:49:51 by ambervandam   ########   odam.nl         */
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
		// memset for argument struct
		mini.stdout = 1;
		mini.stderr = 2;
		while (lineret)
		{
			// ft_putstr_fd("> ", mini.stdout);
			ft_signals(&mini, 0);
			if ((lineret = get_next_line(mini.stdin, &line)) < 0)
			{
				free(line);
				line = NULL;
				ft_lstclear(&mini.env1);
				exit(1);
			}
			if (parse_input_string(line, &mini, envp) == -1)
			{
				free(line);
				line = NULL;
				ft_exit(&mini, mini.exit);
			}
			clear_mini(&mini, 1);
			free(line);
			line = NULL;
			// printf("afetr\n");
			// ft_leaks();
		}
		if (lineret == 0)
			ft_signals(&mini, 1);
		free(line);
		line = NULL;
		ft_lstclear(&mini.env1);
	}
	else
		ft_putstr_fd("No argument needed.\nUsage: ./minishell\n", STDERR);
	return (0);
}
