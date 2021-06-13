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

typedef struct s_tree
{
	struct s_tree *left;
	struct s_tree *right;
	char 	*command;
	char 	*flags;
	char 	*arguments;
	char 	*file_name;
	char    type;
}				t_tree;
//parser
char		**make_tokens_massive(char *s);
void		deletespaces(char *src);
//utils
void		printmas(char **mas, int level);
void 		free_mas(char **mas);
void 		free_tree(t_tree *node);
//error
void		print_error(char *str);
//check_tokens
int	check_tokens(char **mas);
//tree
void *make_tree(char **mas);
//main
void	insert_tabs(int level);

#endif