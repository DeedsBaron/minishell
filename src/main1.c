/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaron <dbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 16:54:40 by dbaron            #+#    #+#             */
/*   Updated: 2021/06/08 16:21:02 by dbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
// int where_smb(char *str, char c)
// {
// 	int i = 0;
// 	while (str[i] != c && str[i] != '\0')
// 		i++;
// 	return (i);
// }

// void *make_tree(char *str)
// {
// 	t_calc *zero_node = malloc(sizeof(t_calc));
// 	t_calc *left = malloc(sizeof(t_calc));
// 	t_calc *right = malloc(sizeof(t_calc));
// 	zero_node->left = NULL;
// 	zero_node->right = NULL;
// 	zero_node->type = "NULL";
// 	zero_node->token = '0';
// 	if (ft_strchr(str, '+'))
// 	{
// 		zero_node->sign = '+';
// 		zero_node->left = make_tree(ft_substr(str, 0, where_smb(str, '|')));
// 		zero_node->right = make_tree(ft_substr(str, where_smb(str, '+') + 1,
// 					ft_strlen(str)));
// 	}
// 	else if (ft_strchr(str, '-'))
// 	{
// 		zero_node->sign = '-';
// 		zero_node->left = make_tree(ft_substr(str, 0, where_smb(str, '-')));
// 		zero_node->right = make_tree(ft_substr(str, where_smb(str, '-') + 1,
// 											   ft_strlen(str)));
// 	}
// 	else if (ft_strchr(str, '*'))
// 	{
// 		zero_node->sign = '*';
// 		zero_node->left = make_tree(ft_substr(str, 0, where_smb(str, '*')));
// 		zero_node->right = make_tree(ft_substr(str, where_smb(str, '*') + 1,
// 											   ft_strlen(str)));
// 	}
// 	else if (ft_strchr(str, '\\'))
// 	{
// 		zero_node->sign = '\\';
// 		zero_node->left = make_tree(ft_substr(str, 0, where_smb(str, '\\')));
// 		zero_node->right = make_tree(ft_substr(str, where_smb(str, '\\') + 1,
// 											   ft_strlen(str)));
// 	}
// 	else
// 	{
// 		zero_node->nb = ft_atoi(str);
// 		zero_node->left = NULL;
// 		zero_node->right = NULL;
// 	}
// 	return(zero_node);
// }

 void	insert_tabs(int level)
 {
 	int i = 0;
 	while (i < level)
 	{
 		printf("\t");
 		i++;
 	}
 }

 void	print_tree(t_tree *zero_node, int level)
 {
 	if (zero_node == NULL)
 	{
 		insert_tabs(level);
 		printf("---<empty>---");
 		return;
 	}
 	if (zero_node->command != NULL)
	{
		insert_tabs(level);
		printf("command = |%s|\n", zero_node->command);
		insert_tabs(level);
		printf("flags = |%s|\n", zero_node->flags);
		insert_tabs(level);
		printf("arguments = |%s|\n", zero_node->arguments);
	}
 	else
	{
		insert_tabs(level);
		printf("type = %c\n", zero_node->type);
	}
	print_tree(zero_node->left, level + 1);
 	insert_tabs(level);
 	printf("left\n");
 	print_tree(zero_node->right, level + 1);
 	insert_tabs(level);
 	printf("right\n");
 }

// int		calculate(t_calc *zero_node)
// {
// 	if (zero_node->sign == '+')
// 		return (calculate(zero_node->left) + calculate(zero_node->right));
// 	if (zero_node->sign == '-')
// 		return (calculate(zero_node->left) - calculate(zero_node->right));
// 	if (zero_node->sign == '*')
// 		return (calculate(zero_node->left) * calculate(zero_node->right));
// 	if (zero_node->sign == '\\')
// 		return (calculate(zero_node->left) / calculate(zero_node->right));
// 	return (zero_node->nb);
// }

int		main(int argc, char *argv[])
{
	char *str = NULL;
	char **mas;
	t_tree *tree;
	while (get_next_line(0, &str))
	{
		printf("str = |%s|\n", str);
		mas = NULL;
		mas = make_tokens_massive(str);
		//printmas(mas);
		printf("::::::::::::::::::::::::::::\n");
		if (check_tokens(mas) == 1)
		{
			//make_tree(mas);
			tree = make_tree(mas);
			print_tree(tree, 0);

		}
		free_tree(tree);
		free(tree);
	}
	free(str);
	return 1;
}