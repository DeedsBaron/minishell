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

void	print_tree(t_tree *root, int level)
{
	int	i;

	i = 0;
	if (root == NULL)
	{
		insert_tabs(level);
		printf("---<empty>---");
		return ;
	}
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
	print_tree(root->left, level + 1);
	insert_tabs(level);
	printf("left\n");
	print_tree(root->right, level + 1);
	insert_tabs(level);
	printf("right\n");
}

void handler(int num)
{
	write(1, "\n", 1);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*str;
	char	**mas;
	char	**envp_copy;
	t_tree	*tree;
	int		in;
	int		out;

	argv[0] = NULL;
	str = NULL;
	if (argc != 1)
	{
		write(1, ARGS, ft_strlen(ARGS));
		return (1);
	}
	envp_copy = make_envp_copy(envp);
	delete_old_pwd(&envp_copy);
	//signal(SIGINT, handler);

	str = readline("minishell$ ");
	while(str)
	{
		add_history(str);
		mas = NULL;
		tree = NULL;
		mas = make_tokens_massive(str);
		if (mas && (check_tokens(mas, envp_copy) == 1))
		{
			if (*mas)
				tree = make_tree(mas);
			print_tree(tree, 0);
		}
		if (tree)
		{
			in = dup(0);
			out = dup(1);
			exec_tree(tree, &envp_copy, 1, NULL);
			dup2(in, 0);
			dup2(out, 1);
		}
		free_tree(tree);
		free(tree);
		str = readline("minishell$ ");
	}
	free_mas(envp_copy);
	free(str);
	return (0);
}
