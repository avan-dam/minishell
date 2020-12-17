/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/04 11:40:20 by ambervandam   #+#    #+#                 */
/*   Updated: 2020/12/17 18:26:32 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_check_n(char *string)
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
			// printf("j = %i so mini->more[j] is %c and length is %lu\n", j, string[j], ft_strlen(string) - j);
            string = ft_substr(string, j, ft_strlen(string) - j);
            return (2);
        }
        i++;
    }
    return (0);
}

static int    ft_echo_n(char *string)
{
    int     i;
    int     j;

    if(string == NULL)
        return (0);
	j = ft_check_n(string);
    if (j == 1)
        return (j);
	if (j != 2)
	{
	    i = ft_len(string);
    	i = i - 3;
    	string = ft_substrr(string, 3, i);
	}
	j = 0;
    string = ft_strtrim(string, " ");
    ft_putstr(string);
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

int    ft_echo(char *string)
{
    if (string == NULL)
    {
        ft_putchar('\n');
        return (0);
    }
    if (ft_check_empty(string) == 1)
        ft_putchar('\n');
    else if ((string[0] == '-') && (string[1] == 'n') && ((string[2] == ' ') || (string[2] == '\0') || (string[2] == 'n')))
    {
        if (ft_echo_n(string) == 2)
        {
            string = ft_strtrim(string, " ");
            ft_putstr(string) ;
            ft_putchar('\n');
        }
    }
    else
    {
            string = ft_strtrim(string, " ");
            ft_putstr(string);
            ft_putchar('\n');
    }
    return (0);
}
