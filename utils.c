/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/04 12:06:37 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/01/08 16:49:14 by ambervandam   ########   odam.nl         */
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

int		unvalid_identifier(char *error)
{
    ft_putstr("bash: export: '");
    ft_putstr(error);
    ft_putstr("': not a valid identifier\n");
	return (0);
}

int ft_strchr_numb(char *line, char c, int i)
{
    if (i < 0)
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

int  ft_split_into_tlist(t_mini *mini, char *line)
{
    t_list  *newnode;
    int     i;
    char	*var1;
    char	*var2;

    // only for env and export commands because those are seperated by '='
    // so only looks at tlist env
    if ((i = ft_strchr_numb(line, '=', 0)) == -1)
        return (0);
    if (line[i - 1] == ' ' || line[i + 1] == ' ')
        return (0);
    var1 = ft_substr(line, 0, i);
	var2 = ft_substr(line, i + 1, ft_strlen(line) - i - 1);
	// if already in the list unset it
	ft_unset(mini, var1);
	// printf("about to make a new node with [%s] and [%s]\n", var1, var2);
	newnode = ft_lstnew(var1, var2);
    ft_lstadd_back(&mini->env1, newnode);
	// printf("now added to the list %s and %s node next we printf list\n", var1, var2);
	// ft_lstprint(mini->env1);
    return (1);
}

int     numb_char(char *line, char c)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (line[i] != '\0')
    {
        if (line[i] == c)
            j++;
		i++;
    }
    return (j);
}