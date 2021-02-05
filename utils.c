/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 17:39:30 by salbregh      #+#    #+#                 */
/*   Updated: 2021/02/05 10:38:18 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// why dont we use putstr from libft? this is a double function
// void	ft_putstr(char *s)
// {
// 	int i;
	
// 	if (s == NULL)
// 		return ;
// 	i = 0;
// 	while (i < (int)ft_strlen(s))
// 	{
// 		// so that if you type \ once nothing happens only 
// 		// if twice in a row
// 		// if (s[i] == 92)
// 		// 	i++;
// 		write(1, &s[i], 1);
// 		i++;
// 	}
// }

/* put in file for error handling? */

int		unvalid_identifier(char *error, t_mini *mini, int exitstatus)
{
    // printf("VALUE OR ERROR: %s\n", error);
    // is this STDOUT OR STD ERROR
    ft_putstr_fd("bash: ", mini->stderr);
    ft_putstr_fd(error, mini->stderr);
    ft_putstr_fd(": command not found\n", mini->stderr);
    mini->exit = exitstatus;
    return (-1);
}

int ft_strchr_numb(char *line, char c, int i)
{
    if (line == NULL || i < 0)
        return (-1);
    while (line[i] != '\0')
    {
        if (line[i] == c)
			return (i);
		i++;
    }
    return (-1);
}

int ft_strrchr_numb(char *line, char c, int i)
{
    if (line == NULL || i < 0)
        return (-1);
    if (i > (int)ft_strlen(line))
        return (-1);
    while (i >= 0)
    {
        if (line[i] == c)
			return (i);
		i--;
    }
    return (-1);
}

int     numb_char(char *line, char c)
{
    int i;
    int j;

    i = 0;
    j = 0;
    if (line == NULL)
        return (0);
    while (line[i] != '\0')
    {
		//because do not count a > or < as a redir if backslash ebfore it
		//look at this again
        if (line[i] == c)
			j++;
		i++;
    }
    return (j);
}

char		*ft_strjoin_three(char *start, char *newvar, char *end)
{
	char	*temp;
	char	*newline;

	temp = ft_strjoin(start, newvar);
	newline = ft_strjoin(temp, end);
    free(start);
    free(newvar);
    free(end);
    free(temp);
	return (newline);
}

char        *ft_string_insert(char *string, int i, char *middle)
{
    char	*start;
    char 	*end;

	start = ft_substr(string, 0, i + 1);
	end = ft_substr(string, i + 1, ft_strlen(string) - i - 1);
	return (ft_strjoin_three(start, middle, end));
}
