/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-dam <avan-dam@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/13 17:58:43 by avan-dam      #+#    #+#                 */
/*   Updated: 2020/06/08 10:29:51 by Amber         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libgnl.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1000

#endif

static int		ft_free_storage(char **storage, int result)
{
	if (result == -1)
	{
		if (*storage)
		{
			free(*storage);
			*storage = 0;
		}
		return (-1);
	}
	if (result == 0)
	{
		if (*storage)
		{
			free(*storage);
			*storage = 0;
		}
		return (0);
	}
	return (1);
}

static int		ft_find_new_line(char **sto, char **line)
{
	int		len;
	char	*temp;

	if ((ft_no_new_line(*sto)) == -1)
	{
		*line = ft_strdupp("");
		if (*line == NULL)
			return (-1);
		len = 0;
	}
	else
	{
		len = ft_len(*sto);
		if (ft_no_new_line(*sto) != 0)
			len = ft_no_new_line(*sto);
		*line = ft_substrr(*sto, 0, len);
		if (*line == NULL)
			return (-1);
	}
	temp = ft_substrr(*sto, len + 1, ft_len(*sto) - len + 1);
	if (temp == NULL)
		return (-1);
	free(*sto);
	*sto = temp;
	return (1);
}

static int		ft_eof(char **line, int rd, char **sto)
{
	if (rd < 0)
		return (ft_free_storage(sto, -1));
	*line = ft_strdupp("");
	if (*line == NULL)
		return (-1);
	return (0);
}

static int		ft_join_me(char **sto, char *buf, int rd)
{
	char	*temp;

	buf[rd] = '\0';
	temp = ft_strjoinn(*sto, buf);
	if (temp == NULL)
		return (-1);
	if (*sto)
	{
		free(*sto);
		*sto = 0;
	}
	*sto = temp;
	return (1);
}

int				get_next_line(int fd, char **line)
{
	static char *storage;
	char		buf[BUFFER_SIZE + 1];
	int			rd;
	int			result;

	result = 1;
	if (fd < 0 || line == NULL)
		return (-1);
	while (ft_no_new_line(storage) == 0)
	{
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd <= 0)
		{
			if (!storage || rd < 0 || (!storage && rd < 0))
				return (ft_eof(line, rd, &storage));
			result = 0;
			break ;
		}
		if ((ft_join_me(&storage, buf, rd)) == -1)
			return (ft_free_storage(&storage, -1));
	}
	if (ft_find_new_line(&storage, line) == -1)
		return (ft_free_storage(&storage, -1));
	return (ft_free_storage(&storage, result));
}
