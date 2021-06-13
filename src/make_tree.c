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

int mas_len(char **mas)
{
	int i = 0;
	while(mas[i])
		i++;
	return(i);
}
char **submas(char **mas, long int start, long int len)
{
	int i;
	char **new_mas;

	i = 0;
	if (!mas)
		return (NULL);
	if (mas_len(mas) - start < len)
		len = mas_len(mas) - start;
	if (start > mas_len(mas))
		len = 0;
	new_mas = (char **)malloc(sizeof(char*) * (len + 1));
	if (!new_mas)
		return (NULL);
	while(i < len)
	{
		new_mas[i] = ft_strdup(mas[start + i]);
		i++;
	}
	new_mas[i] = NULL;
	return(new_mas);
}

char **find_str(char **mas,  char *str)
{
	long int	i;

	i = 0;
	while (mas[i])
	{
		if (ft_strncmp(mas[i], str, ft_strlen(mas[i])) == 0)
			return ((char **)&mas[i]);
		i++;
	}
		return (NULL);
}

void make_com_fl_arg(char **mas, t_tree *node)
{
	int k;
	char *tmp;

	k = 1;
	tmp = node->command;
	node->command = ft_strjoin(node->command, mas[0]);
	free(tmp);
	while (mas[k] && mas[k][0] == '-')
	{
		tmp = ft_strjoin(node->flags, mas[k] + 1);
		free(node->flags);
		node->flags = tmp;
		k++;
	}
	while(mas[k])
	{
		tmp = ft_strjoin(node->arguments, mas[k]);
		free(node->arguments);
		node->arguments = tmp;
		if (mas[k + 1])
		{
			tmp = ft_strjoin(node->arguments, " ");
			free(node->arguments);
			node->arguments = tmp;
		}
		k++;
	}
}

void *make_tree(char **mas)
{
	t_tree *root = (t_tree *)malloc(sizeof(t_tree));
	root->left = NULL;
	root->right = NULL;
	root->type = '0';
	root->command  = (char *)malloc(sizeof(char) * 1);
	root->command[0] = '\0';
	root->flags  = (char *)malloc(sizeof(char) * 1);
	root->flags[0] = '\0';
	root->arguments  = (char *)malloc(sizeof(char) * 1);
	root->arguments[0] = '\0';
 	if (find_str(mas, "|"))
 	{
		root->type = '|';
		root->left = make_tree(submas(mas, 0, (find_str(mas, "|") - mas)));
		root->right = make_tree(submas(mas, (find_str(mas, "|") - mas) + 1,
									   mas_len((mas))));
 	}
 	else if (find_str(mas, "<"))
 	{
		root->type = '<';
		root->left = make_tree(submas(mas, 0, (find_str(mas, "<") - mas)));
		root->right = make_tree(submas(mas, (find_str(mas, "<") - mas) + 1,
									   mas_len(mas)));
 	}
 	else if (find_str(mas, "<<"))
 	{
		root->type = 'l';
		root->left = make_tree(submas(mas, 0, (find_str(mas, "<<") - mas)));
		root->right = make_tree(submas(mas, (find_str(mas, "<<") - mas) + 1,
									   mas_len(mas)));
 	}
 	else if (find_str(mas, ">"))
 	{
		root->type = '>';
		root->left = make_tree(submas(mas, 0, (find_str(mas, ">") - mas)));
		root->right = make_tree(submas(mas, (find_str(mas, ">") - mas) + 1,
									   mas_len(mas)));
 	}
	else if (find_str(mas, ">>"))
	{
		root->type = '>';
		root->left = make_tree(submas(mas, 0, (find_str(mas, ">>") -
											   mas)));
		root->right = make_tree(submas(mas, (find_str(mas, ">>") - mas)
											+ 1,
									   mas_len(mas)));
	}
 	else
 	{
		root->type = 'c';
 		make_com_fl_arg(mas, root);
		root->left = NULL;
		root->right = NULL;
 	}
	free_mas(mas);
 	return(root);
}
