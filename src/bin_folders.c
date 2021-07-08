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

char	*bin_in_folder(char **folder, char *command)
{
	int i;
	DIR *p_fold;
	char *res;
	struct dirent *entry;
	char *tmp;

	i = 0;
	while (folder[i])
	{
		p_fold = opendir(folder[i]);
		if (p_fold)
		{
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
		}
		i++;
	}
	return (NULL);
}
