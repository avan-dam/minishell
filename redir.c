/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/12 13:52:12 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/01/15 18:07:25 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_redir(t_mini *mini)
{
	t_redir r;

	ft_memset(&r, 0, sizeof(r));
	r.j = ft_strchr_numb(mini->more, '<', 0);
	r.i = ft_strchr_numb(mini->more, '>', 0);
	while (r.j != -1 || r.i != -1)
	{
		if ((r.j < r.i && r.j != -1) || (r.i == -1 && r.j != -1))
		{
			// printf("mini->more is [%s]in swap with r.j%d as and r.i%d as \n", mini->more, r.j, r.i);
			r.i = r.j;
			r.k = 1;
		}
		r.filename = ft_substr(mini->more, r.i + 1, ft_strlen(mini->more) - r.i - 1);
		mini->more = ft_substr(mini->more, 0, r.i);
		r.morefiles = ft_strdup(r.filename);
		while (ft_strcmp(r.morefiles, "") != 0)
		{
			if (r.filename == NULL)
			{
				r.filename = mini->more;
				mini->more = NULL;
			}
			if (r.filename[0] == '>')
			{
				if (r.filename[1] == '&')
					return (unvalid_identifier("unexpected token `&'", mini));
				r.filename = ft_substr(r.filename, 1, ft_strlen(r.filename) - 1);
				r.d = 1;
			}
			if ((r.i = ft_strchr_numb(r.morefiles, '>', 0)) != -1)
			{
				r.filename = ft_substr(r.morefiles, 0,r.i);
				r.morefiles = ft_substr(r.morefiles,r.i + 1, ft_strlen(r.morefiles) -r.i - 1);
			}
			else
				r.morefiles = ft_strdup("");
			// printf("r.ir.is %d r.morefiles %s r.filename %s\n",r.i, r.morefiles, r.filename);
			if (r.filename[0] == '&')
			{
				r.filename = ft_substr(r.filename, 1, ft_strlen(r.filename) - 1);
				if (r.k == 0)
				{
					mini->stdout = ft_atoi(r.filename);
					if (mini->stdout >= 3)
						return (unvalid_identifier("Bad file descriptor", mini));
				}
				if (r.k == 1)
				{
					mini->stdin = ft_atoi(r.filename);
					if (mini->stdin >= 3)
						return (unvalid_identifier("Bad file descriptor", mini));
				}
			}
			else if (r.d == 0 && r.k == 0)
				mini->stdout = open(r.filename, O_RDWR|O_CREAT|O_TRUNC, 0666);
			else if (r.d == 1 && r.k == 0)
				mini->stdout = open(r.filename, O_RDWR|O_CREAT|O_APPEND, 0666);
			else if (r.k == 1)
			{
				printf("filename is [%s]\n", r.filename);
				if ((r.fd = open(r.filename, O_RDWR, 0666)) == -1)
				{
					printf("open fail \n");
					return (unvalid_identifier("No such file or directory", mini));
				}
				mini->stdin = r.fd;
			}
			if (ft_strcmp("", mini->more) == 0)
				mini->more = NULL;
			r.filename = ft_strdup(r.morefiles);
			r.j = ft_strchr_numb(mini->more, '<', 0);
			r.i = ft_strchr_numb(mini->more, '>', 0);
			// printf("d is %d k is %d stdin is now %d std out is now %d\n", d, k, mini->stdin, mini->stdout);
		}
		free(r.filename);
		free(r.morefiles);
	}
	ft_memset(&r, 0, sizeof(r));
	return (0);
}

// int		ft_redir(t_mini *mini)
// {
// 	char *filename;
// 	char *morefiles;
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
// 		morefiles = ft_strdup(filename);
// 		while (ft_strcmp(morefiles, "") != 0)
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
// 			if ((i = ft_strchr_numb(morefiles, '>', 0)) != -1)
// 			{
// 				filename = ft_substr(morefiles, 0, i);
// 				morefiles = ft_substr(morefiles, i + 1, ft_strlen(morefiles) - i - 1);
// 			}
// 			else
// 				morefiles = ft_strdup("");
// 			// printf(" i is %d morefiles %s filename %s\n", i, morefiles, filename);
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
// 			filename = ft_strdup(morefiles);
// 			// printf("d is %d k is %d stdin is now %d std out is now %d\n", d, k, mini->stdin, mini->stdout);
// 		}
// 		free(filename);
// 		free(morefiles);
// 	}
// 	return (0);
// }


// int		ft_redir(t_mini *mini)
// {
// 	char *filename;
// 	char *morefiles;
// 	int i;
// 	int d;

// 	d = 0;
//     // Below is only for '>' and '>>' not '<' implement function for that
// 	printf("in redir with mini->more %s\n", mini->more);
// 	while ((i = ft_strchr_numb(mini->more, '>', 0)) != -1)
// 	{
// 		filename = ft_substr(mini->more, i + 1, ft_strlen(mini->more) - i - 1);
// 		mini->more = ft_substr(mini->more, 0, i);
// 		morefiles = ft_strdup(filename);
// 		while (ft_strcmp(morefiles, "") != 0)
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
// 			if ((i = ft_strchr_numb(morefiles, '>', 0)) != -1)
// 			{
// 				filename = ft_substr(morefiles, 0, i);
// 				morefiles = ft_substr(morefiles, i + 1, ft_strlen(morefiles) - i - 1);
// 			}
// 			else
// 				morefiles = ft_strdup("");
// 			printf(" i is %d morefiles %s filename %s\n", i, morefiles, filename);
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
// 			filename = ft_strdup(morefiles);
// 		}
// 		free(filename);
// 		free(morefiles);
// 	}
// 	return (0);
// }

