/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaron <dbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 16:56:54 by dbaron            #+#    #+#             */
/*   Updated: 2021/06/08 15:14:26 by dbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libs/libft/libft.h"
# include "errors.h"
# include <sys/types.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include "../libs/readline/readline.h"
# include "../libs/readline/history.h"
# include <signal.h>

typedef struct s_tree
{
	struct s_tree	*left;
	struct s_tree	*right;
	char			*command;
	char			**f_arg;
	char			type;
}t_tree;
//2d_array_utils
int		mas_len(char **mas);
char	**submas(char **mas, long int start, long int len);
char	**find_str(char **mas, char *str);
char	**new_mas(char **mas, int start, int end);
//bin_folders
char	**make_bin_folders(void);
char	*bin_in_folder(char **folder, char *command);
//builtins
void	exec_cd(t_tree *root, char **envp[]);
void	exec_echo(t_tree *root, char **envp);
void	exec_exit(t_tree *root, char **envp[]);
void	exec_env(t_tree *root, char **envp[]);
void	exec_pwd(void);
//builtins2
void	exec_export(char **envp[], t_tree *root);
void	exec_unset(char **envp[], t_tree *root);
//builtins_utils
int		count_arguments(char **mas, t_tree *root, int flag, char **envp[]);
int		count_unset_arguments(char **envp, t_tree *root);
void	set_old_pwd(char **envp[]);
void	print_env(char **mas);
void	print_export(char **mas);
//check_tokens
char	*dollar(char *str, int *dolla, char **envp);
int		single_quote(char *str, int *j);
int		double_quote(char **str, int *j, char **envp);
char	**delete_empty(char **mas);
int		check_tokens(char **mas, char **envp);
//envp
void	inc_shlvl(char **envp[], int incdecr);
void	delete_old_pwd(char ***tmp);
char	**make_envp_copy(char **envp);
//error
void	print_error(char *command, char *argument, char *str);
void	set_exit_code(int code, char **envp[]);
void	tokenz_er(t_tree *root, char **envp[]);
//exec_tree
int		if_builtin(t_tree *root);
void	exec_builtin(t_tree *root, char **envp[]);
void	exec_bin(t_tree *root, char **envp[]);
void	exec_tree(t_tree *root, char **envp[], int flag, char *filename);
//free
void	free_mas(char **mas);
void	free_tree(t_tree *node);
//make_tokens
char	*sq_case(char **s, char *sq_p);
char	*make_token(char **s);
char	**make_tokens_massive(char *s, char **envp);
//make_tree
void	remove_quotes(char **str);
void	make_com_fl_arg(char **mas, t_tree *node);
int		find_start(char **mas);
int		find_end(int start, char **mas);
void	*make_tree(char **mas);
//preprocess_str
int		count_spaces(char *s);
void	deletespaces(char *src);
char	*str_dollar(char *str, char **envp);
//print
void	print_tree(t_tree *root, int level);
void	insert_tabs(int level);
void	printmas(char **mas, int level);
//redirects
char	*redirect_out(t_tree *root, int *flag);
char	*redirect_in(t_tree *root, char **envp, int *flag);
char	*redirect(t_tree *root, char **envp, int *flag);
int		here_doc(char *name, char **envp);
//signals
void	handler_quit(int sig);
void	handler_int(int sig);
int		status_return(int status);
//singltones
char	***get_envp(void);
char	**get_str(void);
void	set_str(char *value);
char	*my_get_env(char **envp, char *str);
//utils
void	swap(char **s1, char **s2);
char	**sort_alp(char **mas);
int		check_dig_str(char *str);
int		find_equal_arg(const char *s1, const char *s2);
#endif