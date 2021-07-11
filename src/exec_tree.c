/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaron <dbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 16:40:25 by dbaron            #+#    #+#             */
/*   Updated: 2021/06/13 16:40:26 by dbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pipe_fork(t_tree *root, char **envp[], char *filename)
{
	int		fd[2];
	pid_t	pid;

	pid = pipe_fork_2(fd);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		if (root->left)
			exec_tree(root->left, envp, 1, filename);
		close(fd[1]);
		exit(g_exit_code);
	}
	close_n_wait(fd[1], pid, envp);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[0], 0);
		if (root->right)
			exec_tree(root->right, envp, 1, filename);
		close(fd[0]);
		exit(g_exit_code);
	}
	close_n_wait(fd[0], pid, envp);
	pipe_fork3();
}

void 	pipe_node(t_tree *root, char **envp[], char *filename)
{
	if (root->type == '|')
	{
		if (!root->left->command)
		{
			tokenz_er(root, envp);
			return ;
		}
		else if (!root->right->command)
		{
			write(1, MULTILINE, ft_strlen(MULTILINE));
			write(1, "\n", 1);
			set_exit_code(1, envp);
		}
		else
			pipe_fork(root, envp, filename);
	}
}

void 	redirect_node(t_tree *root, char **envp[], int flag, char *filename)
{
	if (root->type == '>' || root->type == 'r' || root->type == '<'
		|| root->type == 'l')
	{
		if (!root->right->command)
		{
			tokenz_er(root, envp);
			return ;
		}
		else
		{
			if (!filename)
				filename = redirect(root, *envp, &flag);
			if (root->right && (root->right->type == '>'
					|| root->right->type == 'r' || root->right->type == '<'
					|| root->right->type == 'l'))
				exec_tree(root->right, envp, 0, filename);
			if (root->left && (flag == 1 || flag == -2 || flag == -1))
			{
				exec_tree(root->left, envp, flag, filename);
				flag = 0;
			}
		}
	}
}

int 	command_node(t_tree *root, char **envp[], int flag, char *filename)
{
	if (root->type == 'c')
	{
		if (flag == -2 || flag == -1)
		{
			redirect_err(filename);
			set_exit_code(1, envp);
			return (2);
		}
		if (filename)
		{
			print_error(root->command, filename, NO_FILE);
			g_exit_code = 4;
			return (2);
		}
		if (ft_strcmp(root->command, "exit") != 0)
			set_exit_code(0, envp);
		if (if_builtin(root) == 1)
			exec_builtin(root, envp);
		else if (if_builtin(root) == 0)
			exec_bin(root, envp);
	}
	return (0);
}

void	exec_tree(t_tree *root, char **envp[], int flag, char *filename)
{
	pipe_node(root, envp, filename);
	redirect_node(root, envp, flag, filename);
	command_node(root, envp, flag, filename);
}
