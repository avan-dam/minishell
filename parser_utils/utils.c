/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 17:39:30 by salbregh      #+#    #+#                 */
/*   Updated: 2021/02/15 18:42:10 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_strchr_numb(char *line, char c, int i)
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

int		ft_strrchr_numb(char *line, char c, int i)
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

int		numb_char(char *line, char c)
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

char		*ft_strjoin_three(char *start, char *newvar, char *end)
{
	char	*temp;
	char	*newline;

	temp = ft_strjoin(start, newvar);
	newline = ft_strjoin(temp, end);
	free(start);
	free(newvar);
	free(end);
	free(temp);
	return (newline);
}

char		*ft_string_insert(char *string, int i, char *middle)
{
	char	*start;
	char 	*end;

	start = ft_substr(string, 0, i + 1);
	end = ft_substr(string, i + 1, ft_strlen(string) - i - 1);
	return (ft_strjoin_three(start, middle, end));
}

int			ft_is_str_int(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
		i++;
	}
	return (1);
}

char		*ft_strtolower(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 65 && str[i] <= 90)
			str[i] = str[i] + 32;
		i++;
	}
	return (str);
}

char     *ft_trim_paths(char *line, char *set)
{
    char    *tmp1;
    int     i;
    char    *tmp2;
    tmp2 = NULL;
    i = 0;
    tmp1 = ft_strtrim(line, set);
    if (tmp1[0] == ' ' || tmp1[ft_strlen(tmp1)] == ' ')
    {
        tmp2 = ft_strtrim(tmp1, " ");
        free(tmp1);
        return (tmp2);
    }
    return (tmp1);
}