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

int	if_builtin(t_tree *root)
{
	if (ft_strcmp(root->command, "echo") == 0)
		return (1);
	else if (ft_strcmp(root->command, "env") == 0)
		return (1);
	else if (ft_strcmp(root->command, "pwd") == 0)
		return (1);
	else if (ft_strcmp(root->command, "cd") == 0)
		return (1);
	else if (ft_strcmp(root->command, "export") == 0)
		return (1);
	else if (ft_strcmp(root->command, "unset") == 0)
		return (1);
	else if (ft_strcmp(root->command, "exit") == 0)
		return (1);
	else if (ft_strcmp(root->command, ".") == 0)
		return (1);
	else
		return (0);
}

void	exec_builtin(t_tree *root, char **envp[])
{
	if (ft_strcmp(root->command, "echo") == 0)
		exec_echo(root, *envp);
	else if (ft_strcmp(root->command, "env") == 0)
		exec_env(root, envp);
	else if (ft_strcmp(root->command, "pwd") == 0)
		exec_pwd();
	else if (ft_strcmp(root->command, "cd") == 0)
		exec_cd(root, envp);
	else if (ft_strcmp(root->command, "export") == 0)
		exec_export(envp, root);
	else if (ft_strcmp(root->command, "unset") == 0)
		exec_unset(envp, root);
	else if (ft_strcmp(root->command, "exit") == 0)
		exec_exit(root, envp);
	else if (ft_strcmp(root->command, ".") == 0)
	{
		write(2, "bash: .: filename argument required\n", 36);
		write(1, ".: usage: . filename [arguments]\n", 33);
	}
}

void	exec_bin(t_tree *root, char **envp[])
{
	char	**folders;
	char	*bin;
	pid_t	pid;
	int		status;

	bin = NULL;
	if (if_builtin(root) == 0)
	{
		folders = make_bin_folders(*envp);
		bin = bin_in_folder(folders, root->command);
		if (bin || ft_strcmp(root->command, "./minishell") == 0)
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			pid = fork();
			if (pid == 0)
			{
				if (ft_strcmp(root->command, "./minishell") == 0)
					inc_shlvl(envp, 1);
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				execve(bin, root->f_arg, *envp);
			}
			waitpid(pid, &status, 0);
			signal(SIGINT, &handler);
			signal(SIGQUIT, &handler);
			set_exit_code(status_return(status), envp);
			free(bin);
		}
		else
		{
			if (root->command)
			{
				write(2, "minishell: ", 11);
				write(2, root->command, ft_strlen(root->command));
				write(2, ": ", 2);
				write(2, COM_NF, ft_strlen(COM_NF));
				set_exit_code(127, envp);
			}
		}
		free_mas(folders);
	}
}

void	exec_tree(t_tree *root, char **envp[], int flag, char *filename)
{
	int		fd[2];
	pid_t	pid;

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
			set_exit_code(1, envp);
		}
		else
		{
			pipe (fd);
			pid = fork();
			if (pid == 0)
			{
				close(fd[0]);
				dup2(fd[1], 1);
				if (root->left)
					exec_tree(root->left, envp, 1, filename);
				close(fd[1]);
				exit(EXIT_SUCCESS);
			}
			close(fd[1]);
			waitpid(pid, NULL, 0);
			pid = fork();
			if (pid == 0)
			{
				dup2(fd[0], 0);
				if (root->right)
					exec_tree(root->right, envp, 1, filename);
				close(fd[0]);
				exit(EXIT_SUCCESS);
			}
			waitpid(pid, NULL, 0);
			close(fd[0]);
		}
	}
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
	if (root->type == 'c')
	{
		if (flag == -2 || flag == -1)
		{
			write(1, "minishel: ", 10);
			write(1, filename, ft_strlen(filename));
			write(1, ": ", 2);
			write(1, strerror(errno), ft_strlen(strerror(errno)));
			write(1, "\n", 1);
			return ;
		}
		if (filename)
		{
			print_error(root->command, filename, NO_FILE);
			return ;
		}
		if (ft_strcmp(root->command, "exit") != 0)
			set_exit_code(0, envp);
		if (if_builtin(root) == 1)
		{
			exec_builtin(root, envp);
		}
		else if (if_builtin(root) == 0)
		{
			exec_bin(root, envp);
		}
	}
}
