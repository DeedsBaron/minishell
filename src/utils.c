/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaron <dbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 17:54:07 by dbaron            #+#    #+#             */
/*   Updated: 2021/06/05 17:57:11 by dbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	insert_tabs(int level)
{
	int	i;

	i = 0;
	while (i < level)
	{
		write(1, "\t", 1);
		i++;
	}
}

void	printmas(char **mas, int level)
{
	int	i;

	i = 0;
	while (mas[i] != NULL)
	{
		insert_tabs(level);
		write(1, "|", 1);
		write(1, mas[i], ft_strlen(mas[i]));
		write(1, "|", 1);
		write(1, "\n", 1);
		i++;
	}
}

char	**delete_old_pwd(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		if (find_equal_arg(tmp[i], "OLDPWD") == 1)
			tmp[i][6] = '\0';
		i++;
	}
	return (tmp);
}


char	**make_envp_copy(char **envp)
{
	char	**tmp;
	int		i;
	static	int flag;

	flag = 0;
	tmp = (char **)malloc ((sizeof(char *) * (mas_len(envp)) + 1));
	i = 0;
	while (envp[i] != NULL)
	{
		tmp[i] = ft_strdup(envp[i]);
		i++;
	}
	tmp[i] = NULL;
	if (flag == 0)
	{
		//tmp = delete_old_pwd(tmp);
		flag = 1;
	}
	return (tmp);
}

void	print_env(char **mas)
{
	int	i;

	i = 0;
	while (mas[i] != NULL)
	{
		if (ft_strchr(mas[i], '='))
		{
			write(1, mas[i], ft_strlen(mas[i]));
			write(1, "\n", 1);
		}
		i++;
	}
}

void 	swap(char **s1, char **s2)
{
	char *tmp;

	*s2 = tmp;
	*s2 = *s1;
	*s1 = tmp;
}

char	**sort_alp(char **mas)
{
	int i;
	int j;
	int size;

	i = 0;
	size = mas_len(mas);
	while(i < size)
	{
		j = 0;
		while(j < size - i - 1)
		{
			if (ft_strcmp(mas[j], mas[j + 1]) > 0)
				swap(&mas[j], &mas[j + 1]);
			j++;
		}
		i++;
	}
	return(mas);
}

void	print_export(char **mas)
{
	int	i;
	char **mas_cpy;

	i = 0;
	mas_cpy = make_envp_copy(mas);
	mas_cpy = sort_alp(mas_cpy);
	while (mas_cpy[i] != NULL)
	{
		write(1, "declare -x ", 11);
		if (ft_strchr(mas_cpy[i], '='))
		{
			write(1, mas_cpy[i], (ft_strchr(mas_cpy[i], '=') - mas_cpy[i]) + 1);
			write(1, "\"", 1);
			write(1, ft_strchr(mas_cpy[i], '=') + 1,
				ft_strlen(mas_cpy[i]) - (ft_strchr(mas_cpy[i], '=') -
				mas_cpy[i] +
				1));
			write(1, "\"\n", 2);
		}
		else
		{
			write(1, mas_cpy[i], ft_strlen(mas_cpy[i]));
			write(1, "\n", 1);
		}
		i++;
	}
	free_mas(mas_cpy);
}

void	free_mas(char **mas)
{
	int	i;

	i = 0;
	if (mas)
	{
		while (mas[i])
		{
			free(mas[i]);
			mas[i] = NULL;
			i++;
		}
		free(mas);
		mas = NULL;
	}
}

void	free_tree(t_tree *node)
{
	if (node)
	{
		if (node->command)
		{
			free(node->command);
			node->command = NULL;
		}
		if (node->f_arg)
		{
			free_mas(node->f_arg);
			node->f_arg = NULL;
		}
		if (node->left)
		{
			free_tree(node->left);
			free(node->left);
			node->left = NULL;
		}
		if (node->right)
		{
			free_tree(node->right);
			free(node->right);
			node->right = NULL;
		}
	}
}

char  *my_get_env(char **envp, char *str)
{
	int	i;
	int k;
	i = 0;
	k = 0;
	while (envp[i] && find_equal_arg(envp[i], str) == 0)
		i++;
	if (!(envp[i]))
		return(NULL);
	else
		return(ft_strdup(ft_strchr(envp[i], '=') + 1));
}