/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-dam <avan-dam@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/03 17:24:36 by avan-dam      #+#    #+#                 */
/*   Updated: 2020/12/04 18:10:44 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libgnl.h"
#include "minishell.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_first_word(char *liney, t_mini *mini)
{
	int i;
	int j;
	int k;
	i = 0;
	j = 0;
	while (liney[i] != '\n' && liney[i] != '\0' && liney[i] != ' ')
		i++;
	mini->command = (char *)malloc(sizeof(char) * (i + 1));
	while (j < i)
	{
		mini->command[j] = liney[j];
		j++;
	}
	mini->command[j] = '\0';
	while (liney[j] != '\0')
		j++;
	i++;
	k = 0;
	mini->more = (char *)malloc(sizeof(char) * (i + 1));
	while (k < j)
	{
		mini->more[k] = liney[i];
		i++;
		k++;
	}
	mini->more[k] = '\0';
	return ;
}

int		check_liney(char **liney, t_mini *mini)
{	
	ft_first_word(*liney, mini);
	if (ft_strcmp(mini->command, "echo") == 0)
		ft_echo(mini);
	else if (ft_strcmp(mini->command, "cd") == 0)
		printf("I got an cd baby\n");
	else if (ft_strcmp(mini->command, "pwd") == 0)
		printf("I got a PWD baby\n");
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
		liney = NULL;
		return (-1);
	}
	else
		printf("I do not recgonise the input entered[%s]\n", *liney);
	liney = NULL;
	return (0);
}

int		main(void)
{
	char	*line;
	int		liney;
	t_mini	mini;

	ft_memset(&mini, 0, sizeof(t_mini));
	while (1)
	{
		liney = get_next_line(1, &line);
		if (liney == -1)
			printf("error");
		if (check_liney(&line, &mini) == -1)
			return (0);
	}
	// printf("command = [%s] more = [%s]\n", mini->command, mini->more);
	return (0);
}


