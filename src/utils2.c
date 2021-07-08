/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaron <dbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 17:54:07 by dbaron            #+#    #+#             */
/*   Updated: 2021/06/05 17:57:11 by dbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void 	export_write(char **mas_cpy, int i)
{
	write(1, "declare -x ", 11);
	if (ft_strchr(mas_cpy[i], '='))
	{
		write(1, mas_cpy[i],
			  (ft_strchr(mas_cpy[i], '=') - mas_cpy[i]) + 1);
		write(1, "\"", 1);
		write(1, ft_strchr(mas_cpy[i], '=') + 1,
			  	ft_strlen(mas_cpy[i]) - (ft_strchr(mas_cpy[i],
					 '=') - mas_cpy[i] + 1));
		write(1, "\"\n", 2);
	}
	else
	{
		write(1, mas_cpy[i], ft_strlen(mas_cpy[i]));
		write(1, "\n", 1);
	}
}

void 	check_sq(char *src, int *i, int *k)
{
	src[(*k)++] = src[(*i)++];
	while (src[(*i)] != '\'' && src[(*i)] != '\0')
		src[(*k)++] = src[(*i)++];
	src[(*k)++] = src[(*i)++];
}

void	tree_init(t_tree *root)
{
	root->left = NULL;
	root->right = NULL;
	root->type = '0';
	root->command = (char *)malloc(sizeof(char) * 1);
	root->command[0] = '\0';
	root->f_arg = NULL;
}

void 	close_n_wait(int fd, int pid)
{
	close(fd);
	waitpid(pid, NULL, 0);
}