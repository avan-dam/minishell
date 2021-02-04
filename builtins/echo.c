/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 16:52:44 by salbregh      #+#    #+#                 */
/*   Updated: 2021/02/04 12:44:56 by ambervandam   ########   odam.nl         */
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
        if (string[i] != ' ')
            return (ft_substr(string, j, ft_strlen(string) - j));
        i++;
    }
    return (ft_strdup(""));
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

    // printf("in echo\n");
	// t_base *tmp = ptr;
	// while(tmp)
	// {
	// 	printf("AFTEr REDIR Argument HERE in list: tmp->size%d\n", tmp->size);
	// 	for (int k = 0; k < tmp->size; k++)
	// 		printf("the argument: %s\n", tmp->argv[k]);
	// 	printf("TYPE: %d\n", tmp->type);
	// 	printf("SIZE: %d\n", tmp->size);
	// 	printf("end of argument in list\n\n");
	// 	tmp = tmp->next;
	// }
	i = 1;
    mini->exit = 0;
    if (ft_strcmp("", ptr->argv[0]) == 0)
    {
        ft_putstr_fd("", mini->stdout);
        return (0);
    }
	string = ft_strdup("");
	// t_base *tmp = ptr;
	// while(tmp)
	// {
	// 	printf("IN ECHOArgument HERE in list: tmp->size%d\n", tmp->size);
	// 	for (int k = 0; k < tmp->size; k++)
	// 		printf("the argument: %s\n", tmp->argv[k]);
	// 	printf("TYPE: %d\n", tmp->type);
	// 	printf("SIZE: %d\n", tmp->size);
	// 	printf("end of argument in list\n\n");
	// 	tmp = tmp->next;
	// }
    // printf("echo size is ptr->size%d ptr->argv[1][%s] i is %d\n", ptr->size, ptr->argv[1], i);
	// while (ptr->argv[i])
	// {
	// 	string = ft_strjoin(string, ptr->argv[i]);
	// 	if (ptr->argv[i + 1])
	// 		string = ft_strjoin(string, " ");
	// 	i++;
	// }
    while (ptr->argv[i])
	{
		string = ft_strjoin(string, ptr->argv[i]);
		if (i + 1 != ptr->size)
        {
            if (ptr->argv[i + 1] && ptr->argv[i + 1][0] != '>' && ptr->argv[i + 1][0] != '<')
			    string = ft_strjoin(string, " ");
        }
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
    // return (ft_putchar_fd('\n', STDOUT));
    return (ft_putchar_fd('\n', mini->stdout));
}
