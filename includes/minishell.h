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
#define MINISHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../libs/libft/libft.h"
#include "errors.h"
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
typedef struct s_tree
{
	struct s_tree *left;
	struct s_tree *right;
	char 	*command;
	char 	**f_arg;
	char    type;
}				t_tree;
//parser
char		**make_tokens_massive(char *s);
void		deletespaces(char *src);
//utils
void		printmas(char **mas, int level);
void 		free_mas(char **mas);
void 		free_tree(t_tree *node);
void		print_env(char **mas);
void		print_export(char **mas);
char 		**make_envp_copy(char **envp);
char  *my_get_env(char **envp, char *str);

//error
void		print_error(char *command, char *argument, char* str);
//check_tokens
int	check_tokens(char **mas, char **envp);
char	*dollar(char *str, int *dolla, char **envp);
//tree
void *make_tree(char **mas);
int	mas_len(char **mas);
//main
void	insert_tabs(int level);
//exec_tree
void 	exec_tree(t_tree *root, char **envp[]);
//builtins
void	exec_env(char *envp[]);
void	exec_echo(t_tree *root);
void	exec_pwd(void);
void 	exec_cd(t_tree *root);
void	exec_export(char **envp[], t_tree *root);
void	exec_unset(char **envp[], t_tree *root);
void	exec_exit();
int		find_equal_arg(const char *s1, const char *s2);


#endif