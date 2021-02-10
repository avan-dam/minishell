/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/29 23:26:56 by salbregh      #+#    #+#                 */
/*   Updated: 2021/02/10 09:46:30 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <stdio.h> // delete after
# include <stdlib.h>
# include <sys/syslimits.h> // not sure if allowed?
# include <fcntl.h>
# include <signal.h>


# define STDIN		0
# define STDOUT		1
# define STDERR		2
# define TYPE_END	3
# define TYPE_PIPE	4
# define TYPE_BREAK	5

typedef struct		s_base
{
	char			**argv;
	int				size;
	int				type;
	int				fd[2];
	struct s_base	*prev;
	struct s_base	*next;
	int				redir;
}					t_base;

typedef struct		s_line
{
	int				s;		//number of single quotes that are registered as such
	int				d;		//number of double quotes that are registered as such
	char			*line;
}					t_line;

typedef struct		s_list
{
	char			*var1;
	char			*var2;
	struct s_list	*next;
}					t_list;

typedef struct		s_mini
{
	t_list			*env1;
	int				stdout;
	int				stderr;
	int				numb_cmds; // Command counter new struct
	char			*cmd_part;
	int				type_end;
	int				stdin;
	int				exit;
}					t_mini;

typedef struct		s_piper
{
	int				check;
	char			*write_side;
	char			*read_side;
	int				fd[2]; // fd[0] - read fd[1] - write made by pipe(fd);
}					t_piper;

/* LIST FUNCTIONS */
t_list				*ft_lstnew(void *var1, void *var2);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstadd_back_new(t_base **ptr, t_base *new); // new replace this one or old one
void				ft_lstprint(t_list *lst, t_mini *mini, int i);
void				ft_lstclear(t_list **lst);
int  				ft_split_into_tlist(t_mini *mini, char *line);
void				ft_lstprintold(t_list *lst);
void				ft_baseclear(t_base **lst);

/* BUILTIN FUNCTION */
int 			  	ft_echo(t_base *ptr, t_mini *mini);
int					ft_export(t_base *ptr, t_mini *mini);
int					ft_unset(t_mini *mini, char *unset);
void				ft_cd(t_base *ptr, t_mini *mini);
void				ft_pwd(t_mini *mini);

/* PARSER FUNCTIONS */
int					parse_input_string(char *line, t_mini *mini, char **envp);
int					ft_start_parsing(char *line, t_mini *mini, char **envp); // new
char				*ft_check_dolla_quotes(char *line, t_mini *mini, int i, int j);

/* EXECVE FUNCTIONS */
int					exec_cmds(t_base *ptr, char **envp, t_mini *mini);
int					look_for_non_builtin(t_base *ptr);
int					unvalid_identifier(char *error, t_mini *mini, int exitstatus);
int         		ft_is_builtin_command(char *str);

/* UTILS */
int 				ft_strchr_numb(char *line, char c, int i);
int					ft_strrchr_numb(char *line, char c, int i);
int  				numb_char(char *line, char c);
int     			ft_is_str_int(char *str);


void				clear_mini(t_mini *mini, int i);

// int					ft_redir(t_mini *mini, int d);


// int					ft_builtin(t_mini *mini, char *command, char *more, char **envp);
int					ft_execve(t_mini *mini, char **envp);
t_base				*ft_redir(t_mini *mini, t_base *ptr);
// int					ft_redir(t_mini *mini, t_base *ptr);
int					ft_parse_input(char *command, char *more, t_mini *mini, char **envp);
void				ft_printf_exit_status(t_mini *mini);
char				*ft_string_insert(char *string, int i, char *middle);
void 				ft_reset_fds(t_mini *mini);
void				ft_exit(t_mini *mini, int exitstatus);
char				*ft_strjoin_three(char *start, char *newvar, char *end);
void				handle_sigint(int sig);
void				ft_signals(t_mini *mini, int i);
void				ft_add_env(char *env, char *path, t_mini *mini); // or static
char				*ft_get_env(char *env, t_mini *mini); // of static

void				ft_set_env(char **argv, char **envp, t_mini *mini);


#endif
