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

void 	swap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

char	**sort_alp(char **mas)
{
	int		i;
	int		j;
	int		size;

	i = 0;
	size = mas_len(mas);
	while (i < size)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(mas[j], mas[j + 1]) > 0)
				swap(&mas[j], &mas[j + 1]);
			j++;
		}
		i++;
	}
	return (mas);
}

int 	check_dig_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
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

void	set_new_export_pwd(char **envp[])
{
	int		i;
	char	*tmp;
	char	*cwd;

	i = 0;
	while ((*envp)[i])
	{
		if (find_equal_arg(envp[0][i], "PWD") == 1
			|| ft_strcmp((*envp)[i], "PWD") == 0)
		{
			free((*envp)[i]);
			(*envp)[i] = ft_strjoin("", "PWD=");
			cwd = getcwd(NULL, 1);
			tmp = ft_strjoin((*envp)[i], cwd);
			free(cwd);
			free((*envp)[i]);
			(*envp)[i] = tmp;
		}
		i++;
	}
}
