/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 19:42:47 by dbaron            #+#    #+#             */
/*   Updated: 2021/07/03 19:42:48 by dbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void 	print_tree2(t_tree *root, int level)
{
	int	i;

	i = 0;
	if (root->command != NULL)
	{
		insert_tabs(level);
		printf("type = |%c|\n", root->type);
		insert_tabs(level);
		printf("command = |%s|\n", root->command);
		if (root->f_arg)
		{
			while (root->f_arg[i])
			{
				insert_tabs(level);
				printf("|%s|\n", root->f_arg[i]);
				i++;
			}
		}
	}
	else
	{
		insert_tabs(level);
		printf("type = %c\n", root->type);
	}
}

void	print_tree(t_tree *root, int level)
{
	if (root == NULL)
	{
		insert_tabs(level);
		printf("---<empty>---");
		return ;
	}
	print_tree2(root, level);
	print_tree(root->left, level + 1);
	insert_tabs(level);
	printf("left\n");
	print_tree(root->right, level + 1);
	insert_tabs(level);
	printf("right\n");
}

void	insert_tabs(int level)
{
	int	i;

	i = 0;
	while (i < level)
	{
		write(1, "\t", 1);
		i++;
	}
}

void	printmas(char **mas, int level)
{
	int	i;

	i = 0;
	while (mas[i] != NULL)
	{
		insert_tabs(level);
		write(1, "|", 1);
		write(1, mas[i], ft_strlen(mas[i]));
		write(1, "|", 1);
		write(1, "\n", 1);
		i++;
	}
}
