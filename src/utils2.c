/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaron <dbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 17:54:07 by dbaron            #+#    #+#             */
/*   Updated: 2021/06/05 17:57:11 by dbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void 	export_write(char **mas_cpy, int i)
{
	write(1, "declare -x ", 11);
	if (ft_strchr(mas_cpy[i], '='))
	{
		write(1, mas_cpy[i],
			  (ft_strchr(mas_cpy[i], '=') - mas_cpy[i]) + 1);
		write(1, "\"", 1);
		write(1, ft_strchr(mas_cpy[i], '=') + 1,
			  	ft_strlen(mas_cpy[i]) - (ft_strchr(mas_cpy[i],
					 '=') - mas_cpy[i] + 1));
		write(1, "\"\n", 2);
	}
	else
	{
		write(1, mas_cpy[i], ft_strlen(mas_cpy[i]));
		write(1, "\n", 1);
	}
}

void 	check_sq(char *src, int *i, int *k)
{
	src[(*k)++] = src[(*i)++];
	while (src[(*i)] != '\'' && src[(*i)] != '\0')
		src[(*k)++] = src[(*i)++];
	src[(*k)++] = src[(*i)++];
}

void	tree_init(t_tree *root)
{
	root->left = NULL;
	root->right = NULL;
	root->type = '0';
	root->command = (char *)malloc(sizeof(char) * 1);
	root->command[0] = '\0';
	root->f_arg = NULL;
}

void	close_n_wait(int fd, int pid, char **envp[])
{
	int	status;

	close(fd);
	waitpid(pid, &status, 0);
	if (status != 0)
	{
		if ((status))
		{
			if (status == 256)
				set_exit_code(1, envp);
			if (status == 512)
				set_exit_code(130, envp);
			else if (status == 768)
				set_exit_code(131, envp);
			else if (status == 1024)
				set_exit_code(258, envp);
			else if (status == 1280)
				set_exit_code(127, envp);
		}
	}
}

int	check_identifier_validity(char *str)
{
	int	i;

	if (ft_isalpha(str[0]) == 0 && str[0] != '_')
		return (0);
	i = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (ft_isalpha(str[i]) == 1 || ft_isdigit(str[i]) == 1 || str[i] == '_')
			i++;
		else
			return (0);
	}
	return (1);
}
