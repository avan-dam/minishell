/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 16:52:44 by salbregh      #+#    #+#                 */
/*   Updated: 2021/02/07 10:41:00 by ambervandam   ########   odam.nl         */
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
	char	*tmp;
    if (string == NULL)
        return (0);
    string = ft_howmany_n(string, 0, 0);
	tmp = ft_strdup(string);
	free(string);
    string = ft_strtrim(tmp, " ");
	free(tmp);
	// ft_putstr_fd(string, STDOUT);
    ft_putstr_fd(string, mini->stdout);
	free(string);
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
    {   
		free(string); 
		return (1);
	}
    return (0);
}

static char *ft_argvs_into_string(t_base *ptr)
{
	char	*tmp;
	char	*string;
	int		i;

	i = 1;
	tmp = ft_strdup("");
	string = NULL;
    while (ptr->argv[i])
	{
		if (string)
			free(string);
		string = ft_strjoin(tmp, ptr->argv[i]);
		free(tmp);
		if (i + 1 != ptr->size)
        {
            if (ptr->argv[i + 1] && ptr->argv[i + 1][0] != '>' && ptr->argv[i + 1][0] != '<')
			{    
				tmp = ft_strdup(string);
				free(string);
				string = ft_strjoin(tmp, " ");
				free(tmp);
			}
        }
		tmp = ft_strdup(string);
		i++;
	}
	return (string);
}

int    ft_echo(t_base *ptr, t_mini *mini)
{
    char	*string;
	char	*tmp;

    mini->exit = 0;
    if (ft_strcmp("", ptr->argv[0]) == 0)
    {
        ft_putstr_fd("", mini->stdout);
        return (0);
    }
	string = ft_argvs_into_string(ptr);
    if (string == NULL)
        return (ft_putchar_fd('\n', mini->stdout));
    if (ft_check_empty(string) == 1)
        return (ft_putchar_fd('\n', mini->stdout));
    if ((string[0] == '-') && (string[1] == 'n') && ((string[2] == ' ') || (string[2] == '\0') || (string[2] == 'n')))
    {
        if (ft_echo_n(string, mini) != 2)
            return (0);
    }
	tmp = ft_strdup(string);
	free(string);
    string = ft_strtrim(tmp, " ");
	free(tmp);
    ft_putstr_fd(string, mini->stdout);
	// printf("ending echo with string [%s]\n", string);
	free(string);
    return (ft_putchar_fd('\n', mini->stdout));
}

    // printf("Goes in echo funct\n");
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