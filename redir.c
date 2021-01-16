/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/12 13:52:12 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/01/16 21:06:17 by Amber         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_set_start(t_redir *r, t_mini *mini)
{
	if ((r->j < r->i && r->j != -1) || (r->i == -1 && r->j != -1))
	{
		// printf("mini->more is [%s]in swap with r.j%d as and r.i%d as \n", mini->more, r.j, r.i);
		r->i = r->j;
		r->k = 1;
	}
	r->filename = ft_substr(mini->more, r->i + 1, ft_strlen(mini->more) - r->i - 1);
	mini->more = ft_substr(mini->more, 0, r->i);
	r->m_files = ft_strdup(r->filename);
}

static void	ft_check_values(t_redir *r, t_mini *mini)
{
	if (r->filename == NULL)
	{
		r->filename = mini->more;
		mini->more = NULL;
	}
	if (r->filename[0] == '>')
	{
		if (r->filename[1] == '&')
		{
			r->error = ft_strdup("unexpected token `&'");
			return ;
		}
		r->filename = ft_substr(r->filename, 1, ft_strlen(r->filename) - 1);
		r->d = 1;
	}
	if ((r->i = ft_strchr_numb(r->m_files, '>', 0)) != -1)
	{
		r->filename = ft_substr(r->m_files, 0 ,r->i);
		r->m_files = ft_substr(r->m_files,r->i + 1, ft_strlen(r->m_files) -r->i - 1);
	}
	else
		r->m_files = ft_strdup("");
			// printf("r.ir.is %d r.m_files %s r.filename %s\n",r.i, r.m_files, r.filename);
}

static void	ft_check_alpha(t_redir *r, t_mini *mini)
{
	r->filename = ft_substr(r->filename, 1, ft_strlen(r->filename) - 1);
	if (r->k == 0)
	{
		mini->stdout = ft_atoi(r->filename);
		if (mini->stdout >= 3)
		{
			r->error = ft_strdup("Bad file descriptor");
			return ;
		}
	}
	if (r->k == 1)
	{
		mini->stdin = ft_atoi(r->filename);
		if (mini->stdin >= 3)
		{
			r->error = ft_strdup("Bad file descriptor");
			return ;
		}
	}
}

static void	open_function(t_redir *r, t_mini *mini)
{
	if (r->error == NULL)
	{
		if (r->d == 0 && r->k == 0)
			mini->stdout = open(r->filename, O_RDWR | O_CREAT|O_TRUNC, 0666);
		if (r->d == 1 && r->k == 0)
			mini->stdout = open(r->filename, O_RDWR | O_CREAT|O_APPEND, 0666);
		if (r->k == 1)
		{
			printf("filename is [%s]\n", r->filename);
			if ((r->fd = open(r->filename, O_RDWR, 0666)) == -1)
			{
				r->error = ft_strdup("No such file or directory");
				return ;
			}
			mini->stdin = r->fd;
		}
	}
}

static void	ft_reset_values(t_redir *r, t_mini *mini)
{
	if (ft_strcmp("", mini->more) == 0)
		mini->more = NULL;
	r->filename = ft_strdup(r->m_files);
	r->j = ft_strchr_numb(mini->more, '<', 0);
	r->i = ft_strchr_numb(mini->more, '>', 0);
}

int			ft_redir(t_mini *mini)
{
	t_redir r;

	ft_memset(&r, 0, sizeof(r));
	r.j = ft_strchr_numb(mini->more, '<', 0);
	r.i = ft_strchr_numb(mini->more, '>', 0);
	while (r.j != -1 || r.i != -1)
	{
		ft_set_start(&r, mini);
		while (ft_strcmp(r.m_files, "") != 0)
		{
			ft_check_values(&r, mini);
			if (r.filename[0] == '&' && r.error == NULL)
				ft_check_alpha(&r, mini);
			else
				open_function(&r, mini);
			if (r.error != NULL)
				return (unvalid_identifier(r.error, mini));
			ft_reset_values(&r, mini);
			// printf("d is %d k is %d stdin is now %d std out is now %d\n", d, k, mini->stdin, mini->stdout);
		}
		free(r.filename);
		free(r.m_files);
	}
	ft_memset(&r, 0, sizeof(r));
	return (0);
}

// int		ft_redir(t_mini *mini)
// {
// 	char *filename;
// 	char *m_files;
// 	int i;
// 	int d;
// 	int k;
// 	int j;
// 	int fd;

// 	fd = 0;
// 	d = 0;
// 	k = 0;
// 	j = 0;
//     // Below is only for '>' and '>>' not '<' implement function for that
// 	// printf("in redir with mini->more %s\n", mini->more);
// 	while (((i = ft_strchr_numb(mini->more, '>', 0)) != -1) || ((j = ft_strchr_numb(mini->more, '<', 0)) != -1))
// 	{
// 		if ((j < i && j != -1) || (i == -1 && j != -1))
// 		{
// 			i = j;
// 			k = 1;
// 		}
// 		filename = ft_substr(mini->more, i + 1, ft_strlen(mini->more) - i - 1);
// 		mini->more = ft_substr(mini->more, 0, i);
// 		m_files = ft_strdup(filename);
// 		while (ft_strcmp(m_files, "") != 0)
// 		{
// 			if (filename == NULL)
// 			{
// 				filename = mini->more;
// 				mini->more = NULL;
// 			}
// 			if (filename[0] == '>')
// 			{
// 				if (filename[1] == '&')
// 					return (unvalid_identifier("unexpected token `&'", mini));
// 				filename = ft_substr(filename, 1, ft_strlen(filename) - 1);
// 				d = 1;
// 			}
// 			if ((i = ft_strchr_numb(m_files, '>', 0)) != -1)
// 			{
// 				filename = ft_substr(m_files, 0, i);
// 				m_files = ft_substr(m_files, i + 1, ft_strlen(m_files) - i - 1);
// 			}
// 			else
// 				m_files = ft_strdup("");
// 			// printf(" i is %d m_files %s filename %s\n", i, m_files, filename);
// 			if (filename[0] == '&')
// 			{
// 				filename = ft_substr(filename, 1, ft_strlen(filename) - 1);
// 				if (k == 0)
// 				{
// 					mini->stdout = ft_atoi(filename);
// 					if (mini->stdout >= 3)
// 						return (unvalid_identifier("Bad file descriptor", mini));
// 				}
// 				if (k == 1)
// 				{
// 					mini->stdin = ft_atoi(filename);
// 					if (mini->stdin >= 3)
// 						return (unvalid_identifier("Bad file descriptor", mini));
// 				}
// 			}
// 			else if (d == 0 && k == 0)
// 				mini->stdout = open(filename, O_RDWR|O_CREAT|O_TRUNC, 0666);
// 			else if (d == 1 && k == 0)
// 				mini->stdout = open(filename, O_RDWR|O_CREAT|O_APPEND, 0666);
// 			else if (k == 1)
// 			{
// 				if ((fd = open(filename, O_RDWR, 0666)) == -1)
// 					return (unvalid_identifier("No such file or directory", mini));
// 				mini->stdin = fd;
// 				// printf("in d= 0 k is 1 and filename is %s and mini->stdin%d\n", filename, mini->stdin);
// 			}
// 			if (ft_strcmp("", mini->more) == 0)
// 				mini->more = NULL;
// 			filename = ft_strdup(m_files);
// 			// printf("d is %d k is %d stdin is now %d std out is now %d\n", d, k, mini->stdin, mini->stdout);
// 		}
// 		free(filename);
// 		free(m_files);
// 	}
// 	return (0);
// }


// int		ft_redir(t_mini *mini)
// {
// 	char *filename;
// 	char *m_files;
// 	int i;
// 	int d;

// 	d = 0;
//     // Below is only for '>' and '>>' not '<' implement function for that
// 	printf("in redir with mini->more %s\n", mini->more);
// 	while ((i = ft_strchr_numb(mini->more, '>', 0)) != -1)
// 	{
// 		filename = ft_substr(mini->more, i + 1, ft_strlen(mini->more) - i - 1);
// 		mini->more = ft_substr(mini->more, 0, i);
// 		m_files = ft_strdup(filename);
// 		while (ft_strcmp(m_files, "") != 0)
// 		{
// 			if (filename == NULL)
// 			{
// 				filename = mini->more;
// 				mini->more = NULL;
// 			}
// 			if (filename[0] == '>')
// 			{
// 				if (filename[1] == '&')
// 					return (unvalid_identifier("unexpected token `&'", mini));
// 				filename = ft_substr(filename, 1, ft_strlen(filename) - 1);
// 				d = 1;
// 			}
// 			if ((i = ft_strchr_numb(m_files, '>', 0)) != -1)
// 			{
// 				filename = ft_substr(m_files, 0, i);
// 				m_files = ft_substr(m_files, i + 1, ft_strlen(m_files) - i - 1);
// 			}
// 			else
// 				m_files = ft_strdup("");
// 			printf(" i is %d m_files %s filename %s\n", i, m_files, filename);
// 			if (filename[0] == '&')
// 			{
// 				filename = ft_substr(filename, 1, ft_strlen(filename) - 1);
// 				mini->stdout = ft_atoi(filename);
// 				if (mini->stdout >= 3)
// 					return (unvalid_identifier("Bad file descriptor", mini));
// 			}
// 			else if (d == 0)
// 				mini->stdout = open(filename, O_RDWR|O_CREAT|O_TRUNC, 0666);
// 			else if (d == 1)
// 				mini->stdout = open(filename, O_RDWR|O_CREAT|O_APPEND, 0666);
// 			if (ft_strcmp("", mini->more) == 0)
// 				mini->more = NULL;
// 			filename = ft_strdup(m_files);
// 		}
// 		free(filename);
// 		free(m_files);
// 	}
// 	return (0);
// }
