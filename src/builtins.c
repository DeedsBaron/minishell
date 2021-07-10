/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaron <dbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 14:49:13 by dbaron            #+#    #+#             */
/*   Updated: 2021/06/14 14:49:16 by dbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void 	exec_cd2(t_tree *root, char **envp[], char *res, int exit)
{
	if (root->f_arg[1] != NULL && root->f_arg[1][0] == '~')
	{
		res = ft_strjoin(my_get_env(*envp, "~"), root->f_arg[1] + 1);
		exit = chdir(res);
		if (exit != 0)
		{
			print_error(root->command, root->f_arg[1], NULL);
			set_exit_code(1, envp);
		}
		free(res);
	}
	else if (!getcwd(NULL, 1))
	{
		chdir(root->f_arg[1]);
		write(1, "cd: error retrieving current directory: getcwd: ", 48);
		write(1, "cannot access parent directories: ", 34);
		write(1, "No such file or directory\n", 26);
		set_exit_code(1, envp);
	}
	else if (chdir(root->f_arg[1]) != 0)
	{
		print_error(root->command, root->f_arg[1], NULL);
		set_exit_code(1, envp);
	}
}

void	set_new_export_pwd(char **envp[])
{
	int i;

	i = 0;
	while (envp)
}

void	exec_cd(t_tree *root, char **envp[])
{
	char	*res;
	int		exit;

	set_old_pwd(envp);
	exit = 0;
	res = NULL;
	if (root->f_arg[1] == NULL)
	{
		if (my_get_env(*envp, "HOME") == NULL)
		{
			print_error(root->command, NULL, "HOME not set\n");
			set_exit_code(1, envp);
			return ;
		}
		chdir(my_get_env(*envp, "HOME"));
	}
	else
		exec_cd2(root, envp, res, exit);
	set_new_export_pwd(envp);
}

void	exec_echo(t_tree *root, char **envp)
{
	int	i;

	i = 2;
	if (ft_strcmp("-n", root->f_arg[1]) == 0)
		i = 2;
	else
		i = 1;
	while (root->f_arg[i])
	{
		if (ft_strcmp("~", root->f_arg[i]) == 0)
			write(1, my_get_env(envp, "~"), ft_strlen(my_get_env(envp, "~")));
		else
			write(1, root->f_arg[i], ft_strlen(root->f_arg[i]));
		if (root->f_arg[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (ft_strcmp("-n", root->f_arg[1]) != 0)
		write(1, "\n", 1);
}

void	exec_exit(t_tree *root, char **envp[])
{
	if (mas_len(root->f_arg) > 2)
	{
		print_error(root->command, NULL, "too many arguments\n");
		set_exit_code(1, envp);
		exit(ft_atoi(my_get_env(*envp, "?")));
	}
	if (mas_len(root->f_arg) == 2)
	{
		if (check_dig_str(root->f_arg[1]) == 0)
		{
			print_error(root->command, root->f_arg[1],
				"numeric argument required\n");
			set_exit_code(1, envp);
			exit(ft_atoi(my_get_env(*envp, "?")));
		}
		set_exit_code(ft_atoi(root->f_arg[1]), envp);
		exit(ft_atoi(my_get_env(*envp, "?")));
	}
	else
		exit(ft_atoi(my_get_env(*envp, "?")));
}

void	exec_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 1);
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	free(pwd);
}
