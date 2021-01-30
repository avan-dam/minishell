/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 16:52:44 by salbregh      #+#    #+#                 */
/*   Updated: 2021/01/30 12:07:47 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *ft_howmany_n(char *string, int i, int j)
{
    while (string[i] != '\0')
    {
        j = i;
        if (string[i] != '-')
            return (ft_substr(string, j, ft_strlen(string) - j));
        i++;
        while (string[i] == 'n')
            i++;
		if (string[i] == '\0')
			return (ft_substr(string, j, ft_strlen(string) - j));
        if (string[i] != ' ')
            return (ft_substr(string, j, ft_strlen(string) - j));
        i++;
    }
    return (string);
}

static int    ft_echo_n(char *string, t_mini *mini)
{
    if (string == NULL)
        return (0);
    string = ft_howmany_n(string, 0, 0);
    string = ft_strtrim(string, " ");
	// ft_putstr_fd(string, STDOUT);
    ft_putstr_fd(string, mini->stdout);
    mini->exit = 0;
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

int    ft_echo(t_base *ptr, t_mini *mini)
{
    char	*string;
	int		i;


	i = 1;

    printf("its actually in here\n");
	string = ft_strdup("");
	while (ptr->argv[i])
	{
		string = ft_strjoin(string, ptr->argv[i]);
		if (ptr->argv[i + 1])
			string = ft_strjoin(string, " ");
		i++;
	}
    if (string == NULL)
        return (ft_putchar_fd('\n', mini->stdout));
    if (ft_check_empty(string) == 1)
		// return (ft_putchar_fd('\n', STDOUT));
        return (ft_putchar_fd('\n', mini->stdout));
    if ((string[0] == '-') && (string[1] == 'n') && ((string[2] == ' ') || (string[2] == '\0') || (string[2] == 'n')))
    {
        if (ft_echo_n(string, mini) != 2)
            return (0);
    }
    string = ft_strtrim(string, " ");
	// ft_putstr_fd(string, STDOUT);
    ft_putstr_fd(string, mini->stdout);
    mini->exit = 0;
    // return (ft_putchar_fd('\n', STDOUT));
    return (ft_putchar_fd('\n', mini->stdout));
}
