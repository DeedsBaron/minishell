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

int	main(int argc, char *argv[], char *envp[])
{
	char	**mas;
	t_tree	*tree;
	int		in;
	int		out;

	argv[0] = NULL;
	set_str(NULL);
	if (argc != 1)
	{
		write(1, ARGS, ft_strlen(ARGS));
		return (1);
	}
	*get_envp() = make_envp_copy(envp);
	delete_old_pwd(get_envp());
	signal(SIGINT, &handler_int);
	signal(SIGQUIT, &handler_quit);
	*get_str() = readline("minishell$ ");
	while (*get_str() != NULL)
	{
		add_history(*get_str());
		mas = NULL;
		tree = NULL;
		mas = make_tokens_massive(*get_str(), *(get_envp()));
		if (mas && (check_tokens(mas, *get_envp()) == 1))
		{
			if (*mas)
				tree = make_tree(mas);
		}
		if (tree)
		{
			in = dup(0);
			out = dup(1);
			exec_tree(tree, get_envp(), 1, NULL);
			dup2(in, 0);
			dup2(out, 1);
		}
		free_tree(tree);
		free(tree);
		*get_str() = readline("minishell$ ");
	}
	printf("exit\n");
	free_mas(*get_envp());
	free(*get_str());
	return (0);
}
