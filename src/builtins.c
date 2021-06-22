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

void	exec_echo(t_tree *root)
{
	int i;

	i = 2;
	if (ft_strcmp("-n", root->f_arg[1]) == 0)
		i = 2;
	else
		i = 1;
	while(root->f_arg[i])
	{
		write(1, root->f_arg[i], ft_strlen(root->f_arg[i]));
		if (root->f_arg[i + 1] != NULL)
			write(1, " ", 1);
		i++;

	}
	if (ft_strcmp("-n", root->f_arg[1]) != 0)
		write(1, "\n", 1);
}

void 	exec_cd(t_tree *root)
{
	char *res;

	if (root->f_arg[1] == NULL || (ft_strcmp("~", root->f_arg[1]) == 0))
		chdir(getenv("HOME"));
	else if (root->f_arg[1] != NULL && root->f_arg[1][0] == '~')
	{
		res = ft_strjoin(getenv("HOME"), root->f_arg[1] + 1);
		if (chdir(res) != 0)
			print_error(root->command, root->f_arg[1]);
		free(res);
	}
	else if (chdir(root->f_arg[1]) != 0)
		print_error(root->command, root->f_arg[1]);
}


void	exec_export(char *envp[], t_tree *root)
{
//	if (root->f_arg[1] == NULL)

}

void	exec_exit()
{
	exit(EXIT_SUCCESS);
}
void	exec_env(char *envp[])
{
	printmas(envp, 0);
}

void	exec_pwd(void)
{
	char *pwd;

	pwd = getcwd(NULL, 1);
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	free(pwd);
}