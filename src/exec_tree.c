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

char	**make_bin_folders(void)
{
	char	*str;
	char	**mas;

	str = getenv("PATH");
	mas = ft_split(str, ':');
	return (mas);
}

char	*bin_in_folder(char **folder, char *command)
{
	int				i;
	DIR				*p_fold;
	char			*res;
	struct dirent	*entry;
	char			*tmp;

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
//	else if (ft_strcmp(root->command, "./minishell") == 0)
//		return (1);
	else
		return (0);
}

void	exec_builtin(t_tree *root, char **envp[])
{
	if (ft_strcmp(root->command, "echo") == 0)
		exec_echo(root);
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
}

int 	status_return(int status)
{
	int b;
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
		{
			write(1, "\n", 1);
			return (130);
		}
		if (WTERMSIG(status) == 3)
		{
			write(1, "Quit: 3\n", 9);
			return (131);
		}
	}
	b = status - 255;
	if (b <= 0)
		return (0);
	else
		return (b);
}

void	exec_bin(t_tree *root, char **envp[])
{
	char	**folders;
	char	*bin;
	pid_t	pid;
	int 	status;

	bin = NULL;
	if (if_builtin(root) == 0)
	{
		folders = make_bin_folders();
		bin = bin_in_folder(folders, root->command);
		if (bin || ft_strcmp(root->command, "./minishell") == 0)
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			pid = fork();
			if (pid == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				execve(bin, root->f_arg, *envp);
			}
			waitpid(pid, &status, 0);
			signal(SIGINT, &handler_int);
			signal(SIGQUIT, &handler_quit);
			set_exit_code(status_return(status), envp);
			free(bin);
		}
		else
		{
			if (root->command)
			{
				write(1, "minishell: ", 11);
				write(1, root->command, ft_strlen(root->command));
				write(1, ": ", 2);
				write(1, COM_NF, ft_strlen(COM_NF));
				set_exit_code(127, envp);
			}
		}
		free_mas(folders);
	}
}

int	here_doc(char *name, char **envp)
{
	int		fd[2];
	char	*str;
	int		i;
	pid_t	pid;

	pipe(fd);
	pid = fork();
	wait(NULL);
	if (pid == 0)
	{
		close(fd[0]);
		while ((str = readline("> ")) && ft_strcmp(str, name) != 0)
		{
			i = 0;
			while (str[i] != '\0')
			{
				if (str[i] == '$')
					str = dollar(str, &i, envp);
				else
					i++;
			}
			write(fd[1], str, ft_strlen(str));
			write(fd[1], "\n", 1);
			free(str);
		}
		exit(EXIT_SUCCESS);
	}
	close(fd[1]);
	return (fd[0]);
}

char 	*redirect_out(t_tree *root, int *flag)
{
	int		fd;
	char	*name;

	if (root->right->type == '>' || root->right->type == 'r' ||
		root->right->type == '<' || root->right->type == 'l')
		name = root->right->left->command;
	else
		name = root->right->command;
	if (root->type == '>')
		fd = open(name, O_WRONLY | O_CREAT | O_TRUNC);
	else
		fd = open(name, O_WRONLY | O_CREAT | O_APPEND);
	if (fd < 0)
	{
		*flag = -2;
		return (name);
	}
	dup2(fd, 1);
	close(fd);
	return (NULL);
}

char	*redirect_in(t_tree *root, char **envp, int *flag)
{
	int		fd;
	char	*name;

	if (root->right->type == '<' || root->right->type == 'l'
		|| root->right->type == '>' || root->right->type == 'r')
		name = root->right->left->command;
	else
		name = root->right->command;
	if (root->type == '<')
		fd = open(name, O_RDONLY, 0644);
	else
		fd = here_doc(name, envp);
	if (fd < 0)
	{
		*flag = -1;
		return (name);
	}
	dup2(fd, 0);
	close(fd);
	return (NULL);
}

char	*redirect(t_tree *root, char **envp, int *flag)
{
	if (root->type == '>' || root->type == 'r')
		return (redirect_out(root, flag));
	else if (root->type == '<' || root->type == 'l')
		return (redirect_in(root, envp, flag));
	return (NULL);
}

void	tokenz_er(t_tree *root, char **envp[])
{
	write(1, "minishell: ", 11);
	write(1, "syntax error near unexpected token `", 36);
	if (root->type == 'l')
		write(1, "<<", 2);
	else if (root->type == 'r')
		write(1, ">>", 2);
	else
		write(1, &root->type, 1);
	write(1, "\'\n", 2);
	set_exit_code(258, envp);
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
			return;
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
			if (root->right && (root->right->type == '>' || root->right->type
			== 'r' || root->right->type == '<' || root->right->type == 'l'))
				exec_tree(root->right, envp, 0, filename);
			if (root->left  && (flag == 1 || flag == -2 || flag == -1))
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
