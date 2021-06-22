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
	int	i;

	i = 2;
	if (ft_strcmp("-n", root->f_arg[1]) == 0)
		i = 2;
	else
		i = 1;
	while (root->f_arg[i])
	{
		write(1, root->f_arg[i], ft_strlen(root->f_arg[i]));
		if (root->f_arg[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (ft_strcmp("-n", root->f_arg[1]) != 0)
		write(1, "\n", 1);
}

void	exec_cd(t_tree *root)
{
	char	*res;

	if (root->f_arg[1] == NULL || (ft_strcmp("~", root->f_arg[1]) == 0))
		chdir(getenv("HOME"));
	else if (root->f_arg[1] != NULL && root->f_arg[1][0] == '~')
	{
		res = ft_strjoin(getenv("HOME"), root->f_arg[1] + 1);
		if (chdir(res) != 0)
			print_error(root->command, root->f_arg[1], NULL);
		free(res);
	}
	else if (chdir(root->f_arg[1]) != 0)
		print_error(root->command, root->f_arg[1], NULL);
}

void	exec_export(char **envp[], t_tree *root)
{
	char	**tmp;
	int		i;
	int		k;

	if (root->f_arg[1] == NULL)
		print_export((*envp));
	else
	{
		tmp = (char **)malloc(sizeof(char *) * (mas_len((*envp))
					+ mas_len(root->f_arg)));
		i = 0;
		while ((*envp)[i] != NULL)
		{
			tmp[i] = ft_strdup((*envp)[i]);
			i++;
		}
		k = 1;
		while (root->f_arg[k] != NULL)
		{
			if (ft_isdigit(root->f_arg[k][0]) == 0)
				tmp[i] = ft_strdup(root->f_arg[k]);
			else
				print_error(root->command, root->f_arg[k], COM_NVI);
			i++;
			k++;
		}
		tmp[i] = NULL;
		free_mas(*envp);
		(*envp) = tmp;
	}
}

void	exec_unset(char **envp[], t_tree *root)
{
	char	**tmp;
	int		i;
	int		k;
	int		m;
	char	c;

	if (root->f_arg[1] == NULL)
		return ;
	else
	{
		tmp = (char **)malloc(sizeof(char *) * (mas_len((*envp))
					- mas_len(root->f_arg) + 2));
		i = 0;
		k = 0;
		while ((*envp)[k] != NULL)
		{
			m = 0;
			while (root->f_arg[m] && ft_strcmp((*envp)[k], root->f_arg[m]) != 0)
				m++;
			c = (*envp)[k][ft_strlen(root->f_arg[m]) + 1];
			if (!root->f_arg[m] && c != '=')
			{
				tmp[i] = ft_strdup((*envp)[k]);
				i++;
				k++;
			}
			else
				k++;
		}
		tmp[i] = NULL;
		free_mas(*envp);
		(*envp) = tmp;
	}
}

void	exec_exit(void)
{
	exit(EXIT_SUCCESS);
}

void	exec_env(char *envp[])
{
	print_env(envp);
}

void	exec_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 1);
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	free(pwd);
}
