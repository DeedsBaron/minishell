/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 19:29:54 by dbaron            #+#    #+#             */
/*   Updated: 2021/07/03 19:29:56 by dbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void 	set_old_pwd(char **envp[])
{
	int		i;
	char	*tmp;
	char	*cwd;

	i = 0;
	while ((*envp)[i])
	{
		if (find_equal_arg(envp[0][i], "OLDPWD") == 1
			|| ft_strcmp((*envp)[i], "OLDPWD") == 0)
		{
			free((*envp)[i]);
			(*envp)[i] = ft_strjoin("", "OLDPWD=");
			cwd = getcwd(NULL, 1);
			tmp = ft_strjoin((*envp)[i], cwd);
			free(cwd);
			free((*envp)[i]);
			(*envp)[i] = tmp;
		}
		i++;
	}
}

int	count_arguments(char **mas, t_tree *root, int flag, char **envp[])
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (mas[i])
	{
		if (ft_isalpha(mas[i][0]) == 1)
			counter++;
		else
		{
			if (flag == 0)
				print_error(root->command, mas[i], COM_NVI);
			set_exit_code(1, envp);
		}
		i++;
	}
	return (counter);
}

int	count_unset_arguments(char **envp, t_tree *root)
{
	int	i;
	int	j;
	int	counter;

	j = 1;
	counter = 0;
	while (root->f_arg[j])
	{
		i = 0;
		while (envp[i])
		{
			if (find_equal_arg(envp[i], root->f_arg[j]))
			{
				counter++;
				break ;
			}
			i++;
		}
		j++;
	}
	return (counter);
}

void	print_env(char **mas)
{
	int	i;

	i = 0;
	while (mas[i] != NULL)
	{
		if (find_equal_arg(mas[i], "?") != 1 && find_equal_arg(mas[i], "~")
			!= 1 && ft_strchr(mas[i], '='))
		{
			write(1, mas[i], ft_strlen(mas[i]));
			write(1, "\n", 1);
		}
		i++;
	}
}

void	print_export(char **mas)
{
	int		i;
	char	**mas_cpy;

	i = 0;
	mas_cpy = make_envp_copy(mas);
	mas_cpy = sort_alp(mas_cpy);
	while (mas_cpy[i] != NULL)
	{
		if (find_equal_arg(mas_cpy[i], "?") != 1
			&& find_equal_arg(mas_cpy[i], "~" ) != 1)
		{
			export_write(mas_cpy, i);
			i++;
		}
		else
			i++;
	}
	free_mas(mas_cpy);
}
