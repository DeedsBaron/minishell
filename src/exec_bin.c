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

void	set_sig_n_fork(t_tree *root, char **envp[], char *bin)
{
	int		status;
	pid_t	pid;

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

void	exec_bin(t_tree *root, char **envp[])
{
	char	**folders;
	char	*bin;

	bin = NULL;
	if (if_builtin(root) == 0)
	{
		folders = make_bin_folders(*envp);
		bin = bin_in_folder(folders, root->command);
		if (bin || ft_strcmp(root->command, "./minishell") == 0)
			set_sig_n_fork(root, envp, bin);
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
