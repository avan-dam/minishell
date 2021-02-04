/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/17 22:36:40 by salbregh      #+#    #+#                 */
/*   Updated: 2021/02/04 14:42:46 by salbregh      ########   odam.nl         */
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
		// system("leaks minishell");
	if (argc == 1)
	{
		ft_memset(&mini, 0, sizeof(t_mini));
		ft_set_env(argv, envp, &mini);
		mini.stdout = 1;
		mini.stderr = 2;
		ft_set_env(argv, envp, &mini);
		while (lineret)
		{
			ft_putstr_fd("> ", mini.stdout); // the bash prompt
			// ft_putstr_fd("> ", STDOUT); // the bash prompt
			ft_signals(&mini, 0);
			if ((lineret = get_next_line(mini.stdin, &line)) < 0)
				return (-1);
			if (parse_input_string(line, &mini, envp) == -1)
			{
				free(line);
				line = NULL;
				ft_exit(&mini, mini.exit);
				// return (-1);
			}
			free(line);
			line = NULL;
		}
		if (lineret == 0)
			ft_signals(&mini, 1);
	}
	free(line);
	line = NULL;
	return (0);
}
