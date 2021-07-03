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

char	**make_bin_folders(void)
{
	char	*str;
	char	**mas;

	str = getenv("PATH");
	mas = ft_split(str, ':');
	return (mas);
}

char	*make_res(char *folder, char *res, DIR *p_fold, char *command)
{
	char	*tmp;

	res = ft_strjoin(folder, "/");
	tmp = ft_strjoin(res, command);
	free(res);
	res = tmp;
	closedir(p_fold);
	return (res);
}

char	*bin_in_folder(char **folder, char *command)
{
	int				i;
	DIR				*p_fold;
	char			*res;
	struct dirent	*entry;

	i = 0;
	while (folder[i])
	{
		p_fold = opendir(folder[i]);
		entry = readdir(p_fold);
		while (entry != NULL)
		{
			if (ft_strcmp(command, entry->d_name) == 0)
				return (make_res(folder[i], res, p_fold, command));
			entry = readdir(p_fold);
		}
		closedir(p_fold);
		i++;
	}
	return (NULL);
}
