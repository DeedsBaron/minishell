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
				printf("command found\n");
				closedir(p_fold);
				return (res);
			}
		}
		closedir(p_fold);
		i++;
	}
	return (NULL);
}

void 	exec_command(t_tree *root, char *envp[])
{
	char	**folders;
	char 	*bin;
	pid_t	pid;

	folders = make_bin_folders();
	bin = NULL;

	if (ft_strcmp(root->command, "echo") == 0)
		exec_echo(root);
	else if (ft_strcmp(root->command, "env") == 0)
		exec_env(envp);
	else if (ft_strcmp(root->command, "pwd") == 0)
		exec_pwd();
	else if (ft_strcmp(root->command, "cd") == 0)
		exec_cd(root);
	else
	{
		bin = bin_in_folder(folders, root->command);
		if (bin)
		{
			if (execve(bin, root->f_arg, envp) == -1)
				print_error(root->command, root->f_arg[1]);
			free(bin);
		}
	}
	free_mas(folders);
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
		exec_command(root, envp);
	}
}