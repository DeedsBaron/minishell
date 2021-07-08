/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 19:13:29 by dbaron            #+#    #+#             */
/*   Updated: 2021/07/08 19:13:31 by dbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	root_type(char *str, t_tree *root)
{
	if (ft_strcmp(str, ">") == 0)
		root->type = '>';
	if (ft_strcmp(str, "<") == 0)
		root->type = '<';
	if (ft_strcmp(str, ">>") == 0)
		root->type = 'r';
	if (ft_strcmp(str, "<<") == 0)
		root->type = 'l';
}

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

int 	check_quotes_case(char *str)
{
	if (ft_strcmp(str, "\">\"") == 0
		|| ft_strcmp(str, "\">>\"") == 0
		|| ft_strcmp(str, "\"<\"") == 0
		|| ft_strcmp(str, "\"<<\"") == 0
		|| ft_strcmp(str, "\'>\'") == 0
		|| ft_strcmp(str, "\'>>\'") == 0
		|| ft_strcmp(str, "\'<\'") == 0
		|| ft_strcmp(str, "\'<<\'") == 0)
		return (1);
	else
		return (0);
}

void	make_com_fl_arg_2(char **mas, t_tree *node, int k)
{
	char	*tmp;

	if (check_quotes_case(mas[0]))
		remove_quotes(&mas[0]);
	if (ft_strcmp(mas[0], "\"\"") == 0 || ft_strcmp(mas[0], "\'\'") == 0)
	{
		free(node->command);
		node->command = ft_strdup("");
	}
	else
	{
		tmp = ft_strjoin(node->command, mas[0]);
		free(node->command);
		node->command = tmp;
	}
	if (!ft_strchr(node->command, '$'))
		ft_tolower(&node->command);
	if (mas[0] && (ft_strcmp(mas[k], "\"\"") == 0
			|| ft_strcmp(mas[k], "\'\'") == 0))
		free(tmp);
	node->f_arg = (char **)malloc(sizeof(char *) * mas_len(mas) + 1);
}
