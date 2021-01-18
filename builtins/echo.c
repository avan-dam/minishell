/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/04 11:40:20 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/01/18 10:07:29 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int ft_howmany_n(char *string)
{
    int i;
    int j;
    int l;

    i = 0;
    j = 0;
    l = 0;
    while (string[i] != '\0')
    {
        l++;
        j = i;
        if (string[i] != '-')
            return (-1);
        i++;
        while (string[i] == 'n')
            i++;
		if (string[i] == '\0')
			return (1);
        if (string[i] != ' ')
        {
            string = ft_substr(string, j, ft_strlen(string) - j);
            return (2);
        }
        i++;
    }
    return (0);
}

static int    ft_echo_n(char *string, t_mini *mini)
{
    int     i;
    int     j;

    if(string == NULL)
        return (0);
    if ((j = ft_howmany_n(string)) == 2)
        return (2);
	if (j != 2)
	{
    	i = ft_len(string) - 3;
    	string = ft_substrr(string, 3, i);
	}
    string = ft_strtrim(string, " ");
    ft_putstr_fd(string, mini->stdout);
    return(0);
}

static int  ft_check_empty(char *string)
{
    int i;
    int j;

    i = 0;
    j = 0;
    if (ft_strcmp(string, "") == 0)
        return (1);
    while (string[i] != '\0')
    {
        if (string[i] == ' ')
            j++;
        i++;
    }
    if (i == j)
        return (1);
    return (0);
}

int    ft_echo(char *string, t_mini *mini)
{
    if (string == NULL)
        return(ft_putchar('\n'));
    if (ft_check_empty(string) == 1)
        return(ft_putchar_fd('\n', mini->stdout));
    else if ((string[0] == '-') && (string[1] == 'n') && ((string[2] == ' ') || (string[2] == '\0') || (string[2] == 'n')))
    {
        if (ft_echo_n(string, mini) != 2)
            return(0);
    }
    string = ft_strtrim(string, " ");
    ft_putstr_fd(string, mini->stdout);
    return (ft_putchar_fd('\n', mini->stdout));
}
