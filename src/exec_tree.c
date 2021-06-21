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

char 	**make_bin_folders(void)
{
	char *str;
	char **mas;

	str = getenv("PATH");
	mas = ft_split(str, ':');
	return (mas);
}

char 	*bin_in_folder(char **folder, char *command)
{
	int	i;
	DIR *p_fold;
	char *res;
	struct dirent *entry;
	char *tmp;

	i = 0;
	while (folder[i])
	{
		p_fold = opendir(folder[i]);
		while ((entry = readdir(p_fold)) != NULL)
		{
			if (ft_strcmp(command, entry->d_name) == 0)
			{
				res = ft_strjoin(folder[i], "/");
				tmp = ft_strjoin(res, command);
				free(res);
				res = tmp;
				closedir(p_fold);
				return (res);
			}
		}
		closedir(p_fold);
		i++;
	}
	return (NULL);
}

int 	if_builtin(t_tree *root)
{
	if (ft_strcmp(root->command, "echo") == 0)
		return (1);
	else if (ft_strcmp(root->command, "env") == 0)
		return (1);
	else if (ft_strcmp(root->command, "pwd") == 0)
		return (1);
	else if (ft_strcmp(root->command, "cd") == 0)
		return (1);
	else
		return (0);
}

void 	exec_builtin(t_tree *root, char *envp[])
{
	if (ft_strcmp(root->command, "echo") == 0)
		exec_echo(root);
	else if (ft_strcmp(root->command, "env") == 0)
		exec_env(envp);
	else if (ft_strcmp(root->command, "pwd") == 0)
		exec_pwd();
	else if (ft_strcmp(root->command, "cd") == 0)
		exec_cd(root);
}

void 	exec_bin(t_tree *root, char *envp[])
{
	char	**folders;
	char 	*bin;
	pid_t 	pid;

	bin = NULL;
	if (if_builtin(root) == 0)
	{
		folders = make_bin_folders();
		bin = bin_in_folder(folders, root->command);
		if (bin)
		{
			pid = fork();
			if (pid == 0)
			{
				if (execve(bin, root->f_arg, envp) == -1)
					print_error(root->command, root->f_arg[1]);
			}
			//else
			//	while(waitpid(pid, NULL, 0) <= 0);
			waitpid(pid, NULL, 0);
			free(bin);
		}
		free_mas(folders);
	}
}

void 	redirect_out(t_tree *root)
{
	int fd;
	char *name;

	if (root->right->type == '>' || root->right->type == 'r')
		name = root->right->left->command;
	else
		name = root->right->command;
	if (root->type == '>')
		fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		write(1, strerror(errno), ft_strlen(strerror(errno)));
		write(1, "\n", 1);
	}
	dup2(fd, 1);
	close(fd);
}

void 	redirect_in(t_tree *root)
{
	int fd;
	char *name;

	if (root->right->type == '<' || root->right->type == 'r')
		name = root->right->left->command;
	else
		name = root->right->command;
	if (root->type == '<')
		fd = open(name, O_RDONLY, 0644);
	else
		fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(fd, 0);
	close(fd);
}

void 	redirect(t_tree *root)
{
	if (root->type == '>' || root->type == 'r')
		redirect_out(root);
	else if (root->type == '<' || root->type == 'l')
		redirect_in(root);
}

void 	exec_tree(t_tree *root, char *envp[])
{
	int fd[2];
	pid_t pid;

	if (root->type == '|')
	{
		pipe (fd);
		pid = fork();
		if (pid == 0)
		{
			close(fd[0]);
			dup2(fd[1], 1);
			if (root->left)
				exec_tree(root->left, envp);
			close(fd[1]);
			exit(EXIT_SUCCESS);
		}
		close(fd[1]);
		waitpid(pid, NULL, 0);
		//close(fd[1]); //???????????????????????
		pid = fork();
		if (pid == 0)
		{
			//close(fd[1]);
			dup2(fd[0], 0);
			if (root->right)
				exec_tree(root->right, envp);
			close(fd[0]);
			exit(EXIT_SUCCESS);
		}
		waitpid(pid, NULL, 0);
		close(fd[0]);

	}
	if (root->type == '>' || root->type == 'r' || root->type == '<')
	{
		redirect(root);
		if(root->right)
			exec_tree(root->right, envp);
		if (root->left)
			exec_tree(root->left, envp);
	}
	if (root->type == 'c')
	{
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