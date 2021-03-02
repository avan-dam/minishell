/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/26 10:25:51 by salbregh      #+#    #+#                 */
/*   Updated: 2021/03/02 09:05:55 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static int   no_of_commands(char *line, t_mini *mini, int i, int numb)
// {
//  while (line[i] && ((line[i] != '|' && line[i] != ';')
//          || (mem_check_tkns(ft_substr(line, 0, i), mini, 0, 1) == NULL)))
//  {
//      if (line[i] == ' ')
//      {
//          while (line[i] == ' ')
//              i++;
//          if ((line[i] == '|' || line[i] == ';')
//              && (mem_check_tkns(ft_substr(line, 0, i), mini, 0, 1) != NULL))
//          {
//              //leak
//              mini->numb_cmds = numb;
//              mini->cmd_part = ft_substr(line, 0, i);
//              if (line[i] == '|')
//                  mini->type_end = T_PIPE;
//              else if (line[i] == ';')
//                  mini->type_end = T_BREAK;
//              return (i);
//          }
//          numb++;
//      }
//      if ((line[i] == '>' || line[i] == '<') && line[i + 1] != ' '
//          && line[i + 1] != '"' && line[i + 1] != '\'' && line[i + 1] != '>'
//          && line[i + 1] != '\0')
//          numb++;
//      i++;
//  }
//  mini->numb_cmds = numb;
//  mini->cmd_part = ft_substr(line, 0, i);;
//  mini->type_end = T_END;
//  return (i);
// }

static int  no_of_commands(char *line, t_mini *mini, int i, int numb)
{
    char    *tmp;

    tmp = ft_substr(line, 0, i);
    while (line[i] && ((line[i] != '|' && line[i] != ';')
            || (mem_check_tkns(tmp, mini, 0, 1) == NULL)))
    {
        free(tmp);
        if (line[i] == ' ')
        {
            while (line[i] == ' ')
                i++;
            if ((line[i] == '|' || line[i] == ';')
                && (mem_check_tkns(tmp, mini, 0, 1) != NULL))
            {
                //leak
                mini->numb_cmds = numb;
                mini->cmd_part = ft_substr(line, 0, i);
                if (line[i] == '|')
                    mini->type_end = T_PIPE;
                else if (line[i] == ';')
                    mini->type_end = T_BREAK;
                return (i);
            }
            numb++;
        }
        if ((line[i] == '>' || line[i] == '<') && line[i + 1] != ' '
            && line[i + 1] != '"' && line[i + 1] != '\'' && line[i + 1] != '>'
            && line[i + 1] != '\0')
            numb++;
        i++;
        tmp = ft_substr(line, 0, i);
    }
    free(tmp);
    mini->numb_cmds = numb;
    mini->cmd_part = ft_substr(line, 0, i);;
    mini->type_end = T_END;
    return (i);
}

static void fill_av_list(t_base *new, t_mini *mini, int j, int l, int k)
{
    while (l != new->size)
    {
        if (mini->cmd_part[j] == '\0')
            new->av[l] = NULL;
        else
        {
            while (mini->cmd_part[j] == ' ')
                j++;
            k = j;
            while (mini->cmd_part[j] != ' ' && mini->cmd_part[j])
            {
                if ((mini->cmd_part[j] == '>' || mini->cmd_part[j] == '<')
                    && mini->cmd_part[j + 1] != '\''
                    && mini->cmd_part[j + 1] != '>'
                    && mini->cmd_part[j + 1] != '"')
                    break ;
                j++;
            }
            if ((mini->cmd_part[j] == '>' || mini->cmd_part[j] == '<')
                && mini->cmd_part[j + 1] != '>')
            {
                new->av[l] = ft_substr(mini->cmd_part, k, j - k + 1);
                j++;
            }
            else
                new->av[l] = ft_substr(mini->cmd_part, k, j - k);
        }
        l++;
    }
}

static int  create_av_list(t_base **ptr, char *line, t_mini *mini)
{
    int     numb_characters;
    int     size;
    t_base  *new;

    if (mini->cmd_part)
     free(mini->cmd_part);
    // printf("LINE: %s\n", line);
    numb_characters = no_of_commands(line, mini, 0, 1);
    size = mini->numb_cmds;
    char *temp = mini->cmd_part;
    // free(mini->cmd_part);
    // ft_leaks();
    mini->cmd_part = mem_check_tkns(temp, mini, 0, 0);
    if (mini->cmd_part == NULL)
		return (1);
    // ft_leaks();
    new = (t_base *)malloc(sizeof(t_base));
    new->av = (char **)malloc(sizeof(char *) * (size + 1));
    if (new->av == NULL)
        return (-1); // should exit program AND DOES NOT
    new->size = size;
    new->prev = NULL;
    new->next = NULL;
    new->av[mini->numb_cmds] = NULL;
    fill_av_list(new, mini, 0, 0, 0);
    new->type = mini->type_end;
    new->av[0] = ft_strtolower(new->av[0]);
    // ft_leaks(); // delete
    ft_lstadd_back_base(ptr, new);
    // free(mini->cmd_part);
    free(line);
    return (numb_characters);
}

int parse_input_string(char *line, t_mini *mini, char **envp, int i)
{
    t_base      *ptr;
    char        *tmp;
    int         k;

    ptr = NULL;
    while (line[i])
    {
        while (line[i] == ' ')
            i++;
        tmp = ft_strdup(&line[i]);
        k = create_av_list(&ptr, tmp, mini);
        // printf("value line: %s\n", &line[i]);
        if (k == -1)
        {
            mini->exit = 1;
            return (0);
        }
        i = i + k;
        if (!line[i])
            break ;
        else
            i++;
    }
    // printf("line: %s\n", line);
    free(line);
    if (ptr)
        if (exec_cmds(ptr, envp, mini) == -1)
            return (-1);
    return (0);
}

