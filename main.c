/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/17 22:36:40 by salbregh      #+#    #+#                 */
/*   Updated: 2021/01/18 19:24:57 by salbregh      ########   odam.nl         */
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
	if (argc > 1)
		return (-1);
	ft_memset(&mini, 0, sizeof(t_mini));
	ft_set_array(&mini); // check use of
	ft_set_env(argv, envp, &mini);
	while (lineret)
	{
		ft_putstr("> ");
		lineret = get_next_line(1, &line);
		if (lineret < 0)
			return (-1);
		if (ft_start_parsing(line, &mini, envp) < 0)
			return (-1);
		ft_lstprintold(mini.run2);
		free(mini.run2); // free the list of line
		mini.run2 = NULL;
		free(line);
		line = NULL;
	}	
	free(line);
	line = NULL;
	return (0);
}