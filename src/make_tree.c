/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaron <dbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 16:40:33 by dbaron            #+#    #+#             */
/*   Updated: 2021/06/13 16:40:36 by dbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	make_com_fl_arg(char **mas, t_tree *node)
{
	int		k;

	make_com_fl_arg_2(mas, node, 1);
	k = 0;
	while (mas[k])
	{
		if (check_quotes_case(mas[k]))
			remove_quotes(&mas[k]);
		if (ft_strcmp(mas[k], "\"\"") == 0 || ft_strcmp(mas[k], "\'\'") == 0)
			node->f_arg[k] = ft_strdup("");
		else
			node->f_arg[k] = ft_strdup(mas[k]);
		k++;
	}
	node->f_arg[k] = NULL;
}

int 	find_start(char **mas)
{
	int	i;

	i = 0;
	while (mas[i] != NULL && (ft_strcmp(mas[i], ">") == 0
			|| ft_strcmp(mas[i], ">>") == 0
			|| ft_strcmp(mas[i], "<") == 0 || ft_strcmp(mas[i], "<<") == 0))
	{
		if (mas[i + 1] && ft_strcmp(mas[i + 1], ">") != 0
			&& ft_strcmp(mas[i + 1], ">>") != 0
			&& ft_strcmp(mas[i + 1], "<") != 0
			&& ft_strcmp(mas[i + 1], "<<") != 0)
			i = i + 2;
		else
			i++;
	}
	return (i);
}

int	find_end(int start, char **mas)
{
	int	i;

	i = start;
	while (mas[i] != NULL && ft_strcmp(mas[i], ">") != 0 && ft_strcmp(mas[i],
			">>") != 0 && ft_strcmp(mas[i], "<") != 0
		  && ft_strcmp(mas[i], "<<") != 0)
		i++;
	return (i);
}

void	if_quotes(char **mas, 	t_tree	*root, int start, int end)
{
	int	i;

	i = 0;
	while (mas[i] && ft_strcmp(mas[i], ">") != 0
		   && ft_strcmp(mas[i], ">>") != 0 && ft_strcmp(mas[i], "<") != 0
		   && ft_strcmp(mas[i], "<<") != 0)
		i++;
	root_type(mas[i], root);
	if (i == 0)
	{
		start = find_start(mas);
		end = find_end(start, mas);
		root->left = make_tree(submas(mas, start, end - start));
		root->right = make_tree(new_mas(mas, start, end));
	}
	else
	{
		root->left = make_tree(submas(mas, 0, &mas[i] - mas));
		root->right = make_tree(submas(mas, &mas[i] - mas + 1,
					mas_len((mas))));
	}
}

void	*make_tree(char **mas)
{
	t_tree	*root;

	root = (t_tree *)malloc(sizeof(t_tree));
	tree_init(root);
	if (find_str(mas, "|"))
	{
		root->type = '|';
		root->left = make_tree(submas(mas, 0, (find_str(mas, "|") - mas)));
		root->right = make_tree(submas(mas, (find_str(mas, "|") - mas) + 1,
					mas_len((mas))));
	}
	else if (find_str(mas, ">>") || find_str(mas, ">")
		|| find_str(mas, "<<") || find_str(mas, "<"))
		if_quotes(mas, root, 0, 0);
	else
	{
		root->type = 'c';
		make_com_fl_arg(mas, root);
		root->left = NULL;
		root->right = NULL;
	}
	free_mas(mas);
	return (root);
}
