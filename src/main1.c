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

// void	insert_tabs(int level)
// {
// 	int i = 0;
// 	while (i < level)
// 	{
// 		printf("\t");
// 		i++;
// 	}
// }

// void	print_tree(t_calc *zero_node, int level)
// {
// 	if (zero_node == NULL)
// 	{	
// 		insert_tabs(level);
// 		printf("---<empty>---");
// 		return;
// 	}
// 	insert_tabs(level);
// 	if (zero_node->nb != -1)
// 		printf("nb = %d\n", zero_node->nb);
// 	else
// 		printf("sign = %c\n", zero_node->sign);
// 	print_tree(zero_node->left, level + 1);
// 	insert_tabs(level);
// 	printf("left\n");
// 	print_tree(zero_node->right, level + 1);
// 	insert_tabs(level);
// 	printf("right\n");
// }

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
//	char *str = ft_strdup(argv[1]);
//	char **mas= make_tokens_massive(str);
//	while(1);
	char *str;
	char **mas;
	while (get_next_line(0, &str))
	{
		printf("str = |%s|\n", str);
		mas = make_tokens_massive(str);
	}
	return 1;
}