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

void	remove_quotes(char **str)
{
	int	i;
	int	k;

	i = 0;
	k = 1;
	while ((*str)[k] != '\0')
		(*str)[i++] = (*str)[k++];
	(*str)[i - 1] = '\0';
}

void	make_com_fl_arg(char **mas, t_tree *node)
{
	int		k;
	char	*tmp;

	k = 1;
	tmp = node->command;
	if (ft_strcmp(mas[0], "\">\"") == 0
		|| ft_strcmp(mas[0], "\">>\"") == 0
		|| ft_strcmp(mas[0], "\"<\"") == 0
		|| ft_strcmp(mas[0], "\"<<\"") == 0
		|| ft_strcmp(mas[0], "\'>\'") == 0
		|| ft_strcmp(mas[0], "\'>>\'") == 0
		|| ft_strcmp(mas[0], "\'<\'") == 0
		|| ft_strcmp(mas[0], "\'<<\'") == 0)
		remove_quotes(&mas[0]);
	if (ft_strcmp(mas[0], "\"\"") == 0 || ft_strcmp(mas[0], "\'\'") == 0)
		node->command = ft_strdup("");
	else
		node->command = ft_strjoin(node->command, mas[0]);
	ft_tolower(&node->command);
	if (ft_strcmp(mas[k], "\"\"") == 0 || ft_strcmp(mas[k], "\'\'") == 0)
	free(tmp);
	node->f_arg = (char **)malloc(sizeof(char *) * mas_len(mas) + 1);
	k = 0;
	while (mas[k])
	{
		if (ft_strcmp(mas[k], "\">\"") == 0
			|| ft_strcmp(mas[k], "\">>\"") == 0
			|| ft_strcmp(mas[k], "\"<\"") == 0
			|| ft_strcmp(mas[k], "\"<<\"") == 0
			|| ft_strcmp(mas[k], "\'>\'") == 0
			|| ft_strcmp(mas[k], "\'>>\'") == 0
			|| ft_strcmp(mas[k], "\'<\'") == 0
			|| ft_strcmp(mas[k], "\'<<\'") == 0)
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
	int i;

	i = 0;
	while (mas[i] != NULL && (ft_strcmp(mas[i], ">") == 0 || ft_strcmp(mas[i],
			">>") == 0 || ft_strcmp(mas[i], "<") == 0
			|| ft_strcmp(mas[i], "<<") == 0))
	{
		if (mas[i + 1] && ft_strcmp(mas[i + 1], ">") != 0 && ft_strcmp
			(mas[i +1], ">>") !=0 && ft_strcmp(mas[i + 1], "<") != 0 &&
				ft_strcmp(mas[i + 1], "<<") != 0)
			i = i + 2;
		else
			i++;
	}
	return (i);
}

int find_end(int start, char **mas)
{
	int i;

	i = start;
	while(mas[i] != NULL && ft_strcmp(mas[i], ">") != 0 && ft_strcmp(mas[i],
			">>") != 0 && ft_strcmp(mas[i], "<") != 0
		  && ft_strcmp(mas[i], "<<") != 0)
		i++;

	return (i);
}

void	*make_tree(char **mas)
{
	int		i;
	int start;
	int end;
	t_tree	*root;

	root = (t_tree *)malloc(sizeof(t_tree));
	root->left = NULL;
	root->right = NULL;
	root->type = '0';
	root->command = (char *)malloc(sizeof(char) * 1);
	root->command[0] = '\0';
	root->f_arg = NULL;
	start = 0;
	end = 0;
	if (find_str(mas, "|"))
	{
		root->type = '|';
		root->left = make_tree(submas(mas, 0, (find_str(mas, "|") - mas)));
		root->right = make_tree(submas(mas, (find_str(mas, "|") - mas) + 1,
					mas_len((mas))));
	}
	else if (find_str(mas, ">>") || find_str(mas, ">")
		|| find_str(mas, "<<") || find_str(mas, "<"))
	{
		i = 0;
		while (mas[i] && ft_strcmp(mas[i], ">") != 0
			&& ft_strcmp(mas[i], ">>") != 0 && ft_strcmp(mas[i], "<") != 0
			&& ft_strcmp(mas[i], "<<") != 0)
			i++;
		if (ft_strcmp(mas[i], ">") == 0)
			root->type = '>';
		if (ft_strcmp(mas[i], "<") == 0)
			root->type = '<';
		if (ft_strcmp(mas[i], ">>") == 0)
			root->type = 'r';
		if (ft_strcmp(mas[i], "<<") == 0)
			root->type = 'l';
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
