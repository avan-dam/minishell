/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   replace_dolla.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/07 16:29:41 by ambervandam   #+#    #+#                 */
/*   Updated: 2020/12/21 11:19:41 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static char *line_replaced(char *start, char *newvar, char *end)
{
    char *temp;
    char *newline;
    
    temp = ft_strjoin(start, newvar);
    newline = ft_strjoin(temp, end);
    return (newline);
}

static char *ft_check_var_tlist(t_mini *mini, char *oldvar)
{
    char    *newvar;
    t_list  *tlist;

    // looking through environmental variables to see if needs to be replace
    // so only loop through env1 tlist not run tlist
    tlist = mini->env1;
    while (tlist != NULL)
	{
        if (ft_strcmp(tlist->var1, oldvar) == 0)
        {
            newvar = ft_strjoin(" ", tlist->var2);
    	    return (newvar);   
        }
        tlist = tlist->next;
	}
    return (ft_strdup(""));
}

static char	*ft_find_dolla(char *line, int i, t_mini *mini)
{
	int		j;
    char    *start;
	char	*oldvar;
    char    *newvar;
    char    *end;

	i++;
    j = i;
    while (line[i] != '\0' && line[i] != '#' && line[i] != '$' && line[i] != '-' && line[i] != '=' && line[i] != ' ')
        i++;
    oldvar = ft_substr(line, j, i - j);
    start = ft_substr(line, 0, j - 2);
    end = ft_substr(line, i, ft_strlen(line) - i);
    newvar = ft_check_var_tlist(mini, oldvar);
    // printf("oldvar[%s] newvar[%s] start[%s] end[%s]\n", oldvar, newvar, start, end);
    return (line_replaced(start, newvar, end));
}

// static int 	ft_quotes(char *line, int i)
// {
// 	printf("i to start with %i\n", i);
// 	if (line[i - 1] == 39)
// 	{
// 		if (line[i] != '\0')
// 			i++;
// 		printf("printf line %s and char %c  i to start with %i\n", line, line[i], i);
// 		while ((line[i] != 39) && (line[i] != '\0'))
// 			i++;
// 		printf("i to start with %i\n", i);
// 		return (i);
// 	}
// 	printf("printf line %s and char %c  i to start with %i\n", line, line[i], i);
// 	// if (line[i - 1] == '"')
// 	// 	i--;
// 	printf("printf line %s and char %c  i to start with %i\n", line, line[i], i);
// 	return (i);
	
// }

char		*ft_check_dolla(char *line, t_mini *mini)
{
	int     i;

    i = 0;
    if (line == NULL)
        return (line);
    // printf("line coming into ft_check_dola func [%s]\n", line);
	while (line[i + 1] != '\0')
	{
        // if (line[i] == 39 || line[i] == '"')
		// 	i = ft_quotes(line, i + 1);
        if (line[i] == '$')
        {
            if ((line[i + 1] != '/') && (line[i + 1] != 92) && (line[i + 1] != '\0'))
                line = ft_find_dolla(line, i, mini);
            else
                i = i + 2;
        }
        if (line[i] != '\0' && line[i] != '$')
            i++;
	}
    // printf("line coming OUT ft_check_dola func [%s]\n", line);
    return (line);
}
