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

void		printmas(char **mas, int level)
{
	int		i;

	i = 0;
	while (mas[i] != NULL)
	{
		insert_tabs(level);
		printf("|%s|\n", mas[i]);
		i++;
	}
}

void	free_mas(char **mas)
{
	int	i;

	i = 0;
	if (mas)
	{
		while(mas[i])
		{
			if (mas[i])
				free(mas[i]);
			i++;
		}
		free(mas);
	}
}

void 	free_tree(t_tree *node)
{
	if (node)
	{
		if (node->command)
			free(node->command);
		if (node->flags)
			free(node->flags);
		if (node->arguments)
			free(node->arguments);
		if (node->left)
		{
			free_tree(node->left);
			free(node->left);
		}
		if (node->right)
		{
			free_tree(node->right);
			free(node->right);
		}
	}
}