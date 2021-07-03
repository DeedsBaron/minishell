/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                    :+:         :+:* :+: * */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaron <dbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 15:12:57 by dbaron            #+#    #+#             */
/*   Updated: 2021/06/08 15:14:03 by dbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*dollar(char *str, int *dolla, char **envp)
{
	char	*name;
	char	*env;
	char	*res;
	int		i;
	int		k;

	i = (*dolla) + 1;
	env = NULL;
	name = NULL;
	while (str[i] != '\0' && str[i] != '\'' && str[i] != '\"' && str[i] != '$'
		&& str[i] != ' ')
		i++;
	if (str[*dolla])
		name = ft_substr(str + (*dolla), 1, i - (*dolla) - 1);
	env = my_get_env(envp, name);
	k = *dolla;
	if (!env)
	{
		while (str[i] != '\0')
			str[k++] = str[i++];
		str[k] = '\0';
	}
	else
	{
		res = (char *)malloc(sizeof(char) * (ft_strlen(str) - ft_strlen(name)
					+ ft_strlen(env)));
		i = -1;
		while (++i < (*dolla))
			res[i] = str[i];
		k = 0;
		while (i < (int)(ft_strlen(env) + (*dolla)))
			res[i++] = env[k++];
		k = *dolla + ft_strlen(name) + 1;
		while (str[k] != '\0')
			res[i++] = str[k++];
		res[i] = '\0';
		free(str);
		str = res;
	}
	free(name);
	return (str);
}

int	single_quote(char *str, int *j)
{
	int	i;
	int	k;

	i = *j + 1;
	k = *j;
	while (str[i] != '\0' && str[i] != '\'')
		str[k++] = str[i++];
	if (str[i] == '\0')
	{
		printf("%s\n", MULTILINE);
		return (-1);
	}
	*j = k;
	i++;
	while (str[i] != '\0')
		str[k++] = str[i++];
	str[k] = '\0';
	return (0);
}

int	double_quote(char **str, int *j, char **envp)
{
	int	i;
	int	k;
	int	start;
	int	end;
	int	old_len;

	i = *j + 1;
	k = *j;
	start = *j;
	while ((*str)[i] != '\0' && (*str)[i] != '\"')
		(*str)[k++] = (*str)[i++];
	if ((*str)[i] == '\0')
	{
		printf("%s\n", MULTILINE);
		return (-1);
	}
	end = k;
	*j = k;
	i++;
	while ((*str)[i] != '\0')
		(*str)[k++] = (*str)[i++];
	(*str)[k] = '\0';
	*j = end - 1;
	return (0);
}

char	**delete_empty(char **mas)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (mas[i] != NULL)
	{
		if (mas[i][0] == '\0')
		{
			i++;
		}
		else
			mas[k++] = mas[i++];
	}
	mas[k] = NULL;
	return (mas);
}

int	check_tokens(char **mas, char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (mas[i] != NULL)
	{
		j = 0;
		if (ft_strcmp(mas[i], "\">\"") == 0 ||ft_strcmp(mas[i], "\">>\"") == 0
			|| ft_strcmp(mas[i], "\"<\"") == 0
			|| ft_strcmp(mas[i], "\"<<\"") == 0
			|| ft_strcmp(mas[i], "\'>\'") == 0
			||ft_strcmp(mas[i], "\'>>\'") == 0
			|| ft_strcmp(mas[i], "\'<\'") == 0
			||ft_strcmp(mas[i], "\'<<\'") == 0)
			i++;
		else if (ft_strcmp(mas[i], "\"\"") == 0 || ft_strcmp(mas[i], "\'\'") == 0)
			i++;
		else
		{
			while (mas[i][j] != '\0')
			{
				if (mas[i][j] == '\'')
				{
					if (single_quote(mas[i], &j) == -1)
						return (-1);
					j--;
				}
				else if (mas[i][j] == '\"')
				{
					if (double_quote(&mas[i], &j, envp) == -1)
						return (-1);
				}
				else
					j++;
			}
			i++;
		}
	}
	mas = delete_empty(mas);
	return (1);
}
