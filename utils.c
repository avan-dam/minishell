/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/04 12:06:37 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/01/24 18:53:37 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr(char *s)
{
	int i;
	
	if (s == NULL)
		return ;
	i = 0;
	while (i < (int)ft_strlen(s))
	{
		// so that if you type \ once nothing happens only 
		// if twice in a row
		// if (s[i] == 92)
		// 	i++;
		write(1, &s[i], 1);
		i++;
	}
}

int		unvalid_identifier(char *error, t_mini *mini)
{
    // is this STDOUT OR STD ERROR
    // ft_putstr_fd("bash: export: '", mini->stderr);
    ft_putstr_fd("bash: ", mini->stderr);
    ft_putstr_fd(error, mini->stderr);
    // ft_putstr_fd("': not a valid identifier\n", mini->stderr);
    ft_putstr_fd(": command not found\n", mini->stderr);
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
        if (line[i] == c)
            j++;
		i++;
    }
    return (j);
}