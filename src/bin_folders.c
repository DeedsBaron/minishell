/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_folders.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 19:20:13 by dbaron            #+#    #+#             */
/*   Updated: 2021/07/03 19:20:14 by dbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**make_bin_folders(char **envp)
{
	char	*str;
	char	**mas;

	str = my_get_env(envp, "PATH");
	free(str);
	mas = ft_split(str, ':');
	return (mas);
}

char	*make_command_path(char *folder, char *command, DIR *p_fold)
{
	char			*tmp;
	char			*res;

	res = ft_strjoin(folder, "/");
	tmp = ft_strjoin(res, command);
	free(res);
	res = tmp;
	closedir(p_fold);
	return (res);
}

void	check_absolute_path(t_tree *root)
{
	int		i;
	int		j;
	char	*buf;

	i = 0;
	while (root->command[i] != '\0')
	{
		if (root->command[i] == '/')
		{
			j = ft_strlen(root->command);
			while (j > 0)
			{
				if (root->command[j] == '/')
				{
					buf = ft_strdup(root->command + j + 1);
					free(root->command);
					root->command = buf;
				}
				j--;
			}
		}
		i++;
	}
}

char	*bin_in_folder(char **folder, t_tree *root)
{
	int				i;
	DIR				*p_fold;
	struct dirent	*entry;

	i = 0;
	check_absolute_path(root);
	while (folder[i])
	{
		p_fold = opendir(folder[i]);
		if (p_fold)
		{
			entry = readdir(p_fold);
			while (entry != NULL)
			{
				if (ft_strcmp(root->command, entry->d_name) == 0)
					return (make_command_path(folder[i],
							  root->command, p_fold));
				entry = readdir(p_fold);
			}
			closedir(p_fold);
		}
		i++;
	}
	return (NULL);
}
