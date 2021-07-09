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
		dollar_2(&str, dolla, env, name);
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

int	double_quote(char **str, int *j)
{
	int	i;
	int	k;
	int	start;
	int	end;

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
	int	i;
	int	k;

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

int	check_tokens(char **mas)
{
	int	i;

	i = 0;
	while (mas[i] != NULL)
	{
		if (check_quotes_case(mas[i]) || ft_strcmp(mas[i], "\"\"") == 0
			|| ft_strcmp(mas[i], "\'\'") == 0)
			i++;
		else
		{
			if (check_tokens_while(&mas[i]) == -1)
				return (-1);
			i++;
		}
	}
	mas = delete_empty(mas);
	return (1);
}
