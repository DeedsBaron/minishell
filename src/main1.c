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

char ***get_envp()
{
	static 	char	**envp_copy;
	return (&envp_copy);
}
//
//void	set_envp_flag(int code)
//{
//	*(envp_flag()) = value;
//	return ;
//}
//
//int	get_sigint_flag()
//{
//	return (*sigint_flag());
//}

void handler_int_child(int sig)
{
	write(1, "\n", 1);
}

void handler_int(int sig)
{
	set_exit_code(1, get_envp());
	write(1, "                               ", 31);
	write(1, "\r", 1);
	write(1, "minishell$ ", 11);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

char	**get_str()
{
	static char *str;
	return (&str);
}

void 	set_str(char *value)
{
	*get_str() = value;
}

void handler_quit(int sig)
{
//	write(1, "           ", 11);
//	write(1, "\r", 1);
//	write(1, "minishell$ ", 11);
//	write(1, *get_str(), ft_strlen(*get_str()));
	write(1, "\b\bHERE\a\\", 7);
}
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
	while(*get_str() != NULL)
	{
		add_history(*get_str());
		mas = NULL;
		tree = NULL;
		mas = make_tokens_massive(*get_str(), *(get_envp()));
		if (mas && (check_tokens(mas, *get_envp()) == 1))
		{
			if (*mas)
				tree = make_tree(mas);
			//print_tree(tree, 0);
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
	printf("           ");
	printf("\033[Aexit\n");
	free_mas(*get_envp());
	free(*get_str());
	return (0);
}
