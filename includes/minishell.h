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

typedef struct s_calc
{
	struct s_calc *left;
	struct s_calc *right;
	char	*type;
	char    *token;
}				t_calc;
//parser
char		**make_tokens_massive(char *s);
void		deletespaces(char *src);
//utils
void		printmas(char **mas);
void 		free_mas(char **mas);
//error
void		print_error(char *str);
//check_tokens
int	check_tokens(char **mas);
#endif