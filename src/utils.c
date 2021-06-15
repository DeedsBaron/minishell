/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaron <dbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 17:54:07 by dbaron            #+#    #+#             */
/*   Updated: 2021/06/05 17:57:11 by dbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	insert_tabs(int level)
{
	int i = 0;
	while (i < level)
	{
		write(1, "\t", 1);
		i++;
	}
}

void printmas(char **mas, int level)
{
	int i;

	i = 0;
	while (mas[i] != NULL)
	{
		insert_tabs(level);
		write(1, mas[i], ft_strlen(mas[i]));
		i++;
	}
}

void free_mas(char **mas)
{
	int i;

	i = 0;
	if (mas)
	{
		while (mas[i])
		{
			free(mas[i]);
			mas[i] = NULL;
			i++;
		}
		free(mas);
		mas = NULL;
	}
}

void free_tree(t_tree *node)
{
	if (node)
	{
		if (node->command)
		{
			free(node->command);
			node->command = NULL;
		}
		if (node->f_arg)
		{
			free_mas(node->f_arg);
			node->f_arg = NULL;
		}
		if (node->left)
		{
			free_tree(node->left);
			free(node->left);
			node->left = NULL;
		}
		if (node->right)
		{
			free_tree(node->right);
			free(node->right);
			node->right = NULL;
		}
	}
}