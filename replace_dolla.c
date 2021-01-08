/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   replace_dolla.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/07 16:29:41 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/01/08 12:08:08 by ambervandam   ########   odam.nl         */
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
    t_list  *tlist;

    // looking through environmental variables to see if needs to be replace
    // so only loop through env1 tlist not run tlist
    tlist = mini->env1;
    while (tlist != NULL)
	{
        if (ft_strcmp(tlist->var1, oldvar) == 0)
			return (tlist->var2);
        tlist = tlist->next;
	}
    return (ft_strdup(""));
}

static t_line *ft_find_dolla(char *line, int i, t_mini *mini, t_line *s)
{
	int		j;
    char    *start;
	char	*oldvar;
    char    *newvar;
    char    *end;

	i++;
    j = i;
	// printf("in ft_finddoll with [%s]\n", line);
    while (line[i] != '\0' && line[i] != '#' && line[i] != '$' && line[i] != '-' && line[i] != '=' && line[i] != ' ' && line[i] != 39 && line[i] != '"')
        i++;
	if (i != 0)
	{
		if (line[i - 1] == '"')
			return (NULL);
	}
    oldvar = ft_substr(line, j, i - j);
    start = ft_substr(line, 0, j - 1);
    end = ft_substr(line, i, ft_strlen(line) - i);
	if(start[ft_len(start) - 1] == 39 && end[0] == 39 && ft_len(end) > 1)
	{
		if (end[1] == '"')
			ft_memmove(&end[1], &end[2], ft_strlen(end) - 1);
	}
    newvar = ft_check_var_tlist(mini, oldvar);
    printf("oldvar[%s] newvar[%s] start[%s] end[%s]\n", oldvar, newvar, start, end);
    s->line = line_replaced(start, newvar, end);
	s->k = ft_len(newvar) - 1;
	return(s);
}

static void		set_tline( t_line *s, char *line)
{
	s->line = ft_strdup(line);
	// free line?
	s->o = 0;
	s->t = 0;
	s->k = 0;
}

static int	ft_double_quotes(t_line *s, int i)
{
	printf("in double\n");
	ft_memmove(&s->line[i], &s->line[i+1], ft_strlen(s->line) - 1);
	i--;
	s->t++;
	return (i);
}

static int	ft_single_quotes(t_line *s, int i)
{
	printf("in single\n");
	// if inside double quotes we keep the single quotes and then covert
	if (s->t % 2 == 1)
		return(i+1);
	// remove single quotes and print exactly what is inside without changing
	ft_memmove(&s->line[i], &s->line[i+1], ft_strlen(s->line) - 1);
	i--;
	s->o++;
	while ((s->line[i] != '\'') && (s->line[i] != '\0'))
		i++;
	if (s->line[i] == '\'')
	{
		ft_memmove(&s->line[i], &s->line[i+1], ft_strlen(s->line) - 1);
		i--;
		s->o++;
	}
	i++;
	return (i);
}

// static int ft_check_quotes_in_order(char *line)
// {
// 	int i;
	
// 	i = 0;
// 	while(line[i] != '\0')
// 	{
// 		if (line[i] =='\'')
// 		{
// 			while(line)
// 		}
// 		//loop forward and backwards see if quotes even and in same order from back to from
// 		i++;
// 	}
// 	return (0);
// }

char		*ft_check_dolla_quotes(char *line, t_mini *mini)
{
	int i;
	t_line s;
	
	i = 0;
    if (line == NULL)
        return (line);
	set_tline(&s, line);
	// if (ft_check_quotes_in_order(line) == -1)
	// error
	while (s.line[i] != '\0')
	{
		printf("char %c t is %d o is %d line is %s\n", s.line[i], s.t, s.o, s.line);
		if (s.line[i] == '\\' && (s.o % 2 == 0) && (s.t %2 == 0)) // ascii 92
		{
			ft_memmove(&s.line[i], &s.line[i+1], ft_strlen(s.line) - 1);
			i--;
		}	
		if (s.line[i] == '\'')
			i = ft_single_quotes(&s, i);
		if (s.line[i] == '"')
			i = ft_double_quotes(&s, i);
		else if(s.line[i] == '$')
		{
			printf("in replace dolla 1\n");
			if ((s.line[i + 1] != '/') && (s.line[i + 1] != '\\') && (s.line[i + 1] != '\0'))
			{
				printf("in replace dolla 2\n");
				ft_find_dolla(s.line, i, mini, &s);
				i = i + s.k;
			}
		}
		i++;
	}
	return (s.line);
}
