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

void 	set_old_pwd(char **envp[])
{
	int		i;
	char	*tmp;
	char	*cwd;

	i = 0;
	while ((*envp)[i])
	{
		if (find_equal_arg(envp[0][i], "OLDPWD") == 1 || ft_strcmp
		((*envp)[i], "OLDPWD") == 0)
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

void 	set_exit_code(int code, char **envp[])
{
	int	i;
	char *tmp;

	i = 0;
	while ((*envp)[i])
	{
		if (find_equal_arg((*envp)[i], "?") == 1)
		{
			free((*envp)[i]);
			tmp = ft_itoa(code);
			(*envp)[i] = ft_strjoin("?=", tmp);
			free(tmp);
		}
		i++;
	}
}

void	exec_cd(t_tree *root, char **envp[])
{
	char	*res;
	int		exit;
	char 	*tmp;

	set_old_pwd(envp);

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
	else if (root->f_arg[1] != NULL && root->f_arg[1][0] == '~')
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
	else if (chdir(root->f_arg[1]) != 0)
	{
		print_error(root->command, root->f_arg[1], NULL);
		set_exit_code(1, envp);
	}
}

int	find_equal_arg(const char *s1, const char *s2)
{
	int		i;

	if (s1 == NULL || s2 == NULL)
		return (-1);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && s1[i] != '=' && s2[i] != '=')
		i++;
	if ((s1[i] == '\0' && s2[i] == '\0') || (s1[i] == '=' && s2[i] == '\0')
		|| (s2[i] == '=' && s1[i] == '\0') || (s1[i] == '=' && s2[i] == '='))
		return (1);
	else
		return (0);
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

void	exec_export(char **envp[], t_tree *root)
{
	char	**tmp;
	int		i;
	int		k;
	int		m;

	if (root->f_arg[1] == NULL)
	{
		print_export((*envp));
	}
	else if (count_arguments(root->f_arg, root, 0, envp) != 1)
	{
		tmp = (char **)malloc(sizeof(char *) * (mas_len((*envp))
					+ count_arguments(root->f_arg, root, 0, envp)));
		i = 0;
		while ((*envp)[i] != NULL)
		{
			tmp[i] = ft_strdup((*envp)[i]);
			i++;
		}
		k = 1;
		while (root->f_arg[k] != NULL)
		{
			if (ft_isalpha(root->f_arg[k][0]) == 1)
			{
				m = 0;
				while ((*envp)[m]
					&& find_equal_arg((*envp)[m], root->f_arg[k]) == 0)
					m++;
				if (!((*envp)[m]))
					tmp[i++] = ft_strdup(root->f_arg[k++]);
				else
				{
					if (ft_strchr(root->f_arg[k], '='))
					{
						free(tmp[m]);
						tmp[m] = ft_strdup(root->f_arg[k]);
					}
					k++;
				}
			}
		}
		tmp[i] = NULL;
		free_mas(*envp);
		(*envp) = tmp;
	}
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

void	exec_unset(char **envp[], t_tree *root)
{
	char	**tmp;
	int		i;
	int		j;
	int		k;

	if (root->f_arg[1] == NULL)
		return ;
	else
	{
		tmp = (char **)malloc(sizeof(char *) * (mas_len((*envp))
					- count_unset_arguments(*envp, root) + 1));
		k = 0;
		i = 0;
//		while (i < (mas_len(*envp) - count_unset_arguments(*envp, root)))
		while ((*envp)[i])
		{
			j = 1;
			while (root->f_arg[j] && find_equal_arg((*envp)[i],
				root->f_arg[j]) != 1)
				j++;
			if (find_equal_arg((*envp)[i], root->f_arg[j]) == 1)
				i++;
			else
			{
				tmp[k] = ft_strdup(envp[0][i]);
				k++;
				i++;
			}
		}
		tmp[k] = NULL;
		free_mas(*envp);
		(*envp) = tmp;
	}
}

int 	check_dig_str(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
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

void	exec_env(t_tree *root, char **envp[])
{
	if (root->f_arg[1] == NULL)
		print_env(*envp);
	else if (open(root->f_arg[1], O_RDONLY) == -1)
	{
		print_error(root->command, root->f_arg[1], NULL);
		set_exit_code(126, envp);
	}
	else
	{
		print_error(root->command, root->f_arg[1], NO_FILE);
		set_exit_code(127, envp);
	}
}

void	exec_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 1);
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	free(pwd);
}
