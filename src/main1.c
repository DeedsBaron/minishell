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
 	int i = 0;
 	if (root == NULL)
 	{
 		insert_tabs(level);
 		printf("---<empty>---");
 		return;
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

int		main(int argc, char *argv[], char *envp[])
{
	char *str = NULL;
	char **mas;
	t_tree *tree;
	while (write(1, "minishell$ ", 12) && get_next_line(0, &str))
	{
		mas = NULL;
		tree = NULL;
		mas = make_tokens_massive(str);
		if (mas && (check_tokens(mas) == 1))
		{
			if (*mas)
			{
				tree = make_tree(mas);
				print_tree(tree, 0);
			}
		}
		if (tree)
		{
			int in = dup(0);
			int out = dup(1);
			//pid_t pid;
			//pid = fork();
			//waitpid(pid, NULL, 0);
			//if (pid == 0)
			//{
				exec_tree(tree, envp);
				//exit(EXIT_SUCCESS);
			//}
			dup2(in, 0);
			dup2(out, 1);
		}
		free_tree(tree);
		free(tree);
	}
	free(str);
	return 1;
}