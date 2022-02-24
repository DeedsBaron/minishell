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

int	init_minishell(int argc, char *argv[], char *envp[])
{
	argv[0] = argv[0];
	set_str(NULL);
	if (argc != 1)
	{
		write(1, ARGS, ft_strlen(ARGS));
		return (1);
	}
	*get_envp() = make_envp_copy(envp);
	delete_old_pwd(get_envp());
	signal(SIGINT, &handler);
	signal(SIGQUIT, &handler);
	return (0);
}

void	tree_call(t_tree *tree)
{
	(*get_old_fd())[0] = dup(0);
	(*get_old_fd())[1] = dup(1);
	exec_tree(tree, get_envp(), 1, NULL);
	dup2((*get_old_fd())[0], 0);
	dup2((*get_old_fd())[1], 1);
}

void	set_to_null(char ***mas, t_tree **tree)
{
	(*mas) = NULL;
	(*tree) = NULL;
	g_exit_code = 0;
}

int	main(int argc, char *argv[], char *envp[])
{
	char	**mas;
	t_tree	*tree;

	if (init_minishell(argc, argv, envp) == 1)
		return (1);
	*get_str() = readline("minishell$ ");
	while (*get_str() != NULL)
	{
		add_history(*get_str());
		set_to_null(&mas, &tree);
		mas = make_tokens_massive(*get_str(), *(get_envp()));
		if (mas && (check_tokens(mas) == 1))
		{
			if (*mas)
				tree = make_tree(mas);
		}
		if (tree)
		{
			tree_call(tree);
			print_tree(tree,0);
		}
		free_norminette(tree);
		*get_str() = readline("minishell$ ");
	}
	printf("exit\n");
	free_mas(*get_envp());
	free(*get_str());
	return (0);
}
