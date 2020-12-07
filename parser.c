/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-dam <avan-dam@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/03 17:24:36 by avan-dam      #+#    #+#                 */
/*   Updated: 2020/12/07 10:30:50 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	ft_find_command(char *line, t_mini *mini)
// {
// 	int i;
// 	int j;
// 	int k;
// 	// int z;

// 	i = 0;
// 	j = 0;
// 	while (line[i] != '\n' && line[i] != '\0' && line[i] != ' ')
// 		i++;
// 	// z = 0;
// 	// if (line[i])
// 	// {
// 	// 	while (line[i] != ' ')
// 	// 	{
// 	// 		printf("value line[%d]: %c", i, line[i]);
// 	// 		z++;
// 	// 		i++;
// 	// 	}
// 	// }
// 	// printf("value of z: %d\n", z);
// 	mini->command = (char *)malloc(sizeof(char) * (i + 1)); //free
// 	while (j < i)
// 	{
// 		mini->command[j] = line[j];
// 		j++;
// 	}
// 	mini->command[j] = '\0';
// 	while (line[j] != '\0')
// 		j++;
// 	i++;
// 	k = 0;
// 	mini->more = (char *)malloc(sizeof(char) * (i + 1)); //free
// 	while (k < j)
// 	{
// 		mini->more[k] = line[i];
// 		i++;
// 		k++;
// 	}
// 	mini->more[k] = '\0';
// 	return ;
// }

static void	ft_find_command(char *line, t_mini *mini)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	while (*line == ' ') // trims the spaces at the beginning
		line++;
	while (line[i] != '\n' && line[i] != '\0' && line[i] != ' ')
	{
		// printf("value of line[%d]: %c\n", i, line[i]);
		i++;
	}
	// printf("value of i: %d\n", i);
	mini->command = (char *)malloc(sizeof(char) * i + 1); //free
	while (j < i)
	{
		mini->command[j] = line[j];
		// printf("value of minicommand[%d]: %c\n", j, mini->command[j]);
		j++;
	}
	mini->command[j] = '\0';
	// printf("value mini->command: %s\n", mini->command);
	if (line[j])
	{
		j++; // would skip the space after command
		while (line[j] != '\0')
		{
			// printf("value of line[%d]: %c\n", j, line[j]);
			j++;
		}
	}
	else
		return;
	i++;
	// printf("value of i: %d\n", i);
	// printf("value of j: %d\n", j);
	k = 0;
	mini->more = (char *)malloc(sizeof(char) * (j - i + 1)); //free
	while (k < (j - i))
	{
		mini->more[k] = line[i + k];
		// printf("value mini->more[%d]: %c\n", k, mini->more[k]);
		// printf("value of line[%d]: %c\n", i, line[i + k]);
		k++;
	}
	mini->more[k] = '\0';
	// printf("value mini->more: %s\n", mini->more);
	return ;
}

static int		ft_parse_input(char **line, t_mini *mini)
{
	ft_find_command(*line, mini);
	// printf("before env function\n");
	// ft_check_env(mini);
	// printf("after env function\n");
	if (ft_strncmp(mini->command, "echo", ft_strlen(mini->command)) == 0)
		ft_echo(mini);
	else if (ft_strcmp(mini->command, "cd") == 0)
	{
		printf("I got an cd baby\n");
		ft_cd(mini);
	}
	else if (ft_strcmp(mini->command, "pwd") == 0)
		ft_pwd(mini);
	else if (ft_strcmp(mini->command, "export") == 0)
	{
		printf("command = [%s] more = [%s]\n", mini->command, mini->more);
		printf("about to go into export\n");
		ft_export(mini);
	}
	else if (ft_strcmp(mini->command, "unset") == 0)
		printf("I got an UNSNET baby\n");
	else if (ft_strcmp(mini->command, "env") == 0)
		printf("I got an ENV baby\n");
	else if (ft_strcmp(mini->command, "exit") == 0)
	{
		printf("I got an exit baby\n");
		line = NULL;
		return (-1);
	}
	else
		printf("I do not recgonise the input entered[%s]\n", *line);
	// line = NULL;
	return (0);
}

int		main(void)
{
	char	*line;
	int		lineret;
	t_mini	mini;

	ft_memset(&mini, 0, sizeof(t_mini));
	while (1)
	{
		ft_putstr("> ");
		lineret = get_next_line(1, &line);
		if (lineret < 0)
			ft_putstr("error");
		if (ft_parse_input(&line, &mini) == -1)
			return (0);
	}
	// printf("command = [%s] more = [%s]\n", mini->command, mini->more);
	return (0);
}
