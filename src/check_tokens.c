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

int count_quotes(char *s, char c)
{
	int i;
	int	counter;

	i = 0;
	counter = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			counter++;
		i++;
	}
	return (counter);
}

char	*dollar(char *str, int *dolla)
{
	char	*name;
	char	*env;
	char 	*res;
	int 	i;
	int		k;

	i = (*dolla) + 1;
	env = NULL;
	while (str[i] != '\0' && str[i] != '\'' && str[i] != '\"' && str[i] != '$'
	&& str[i] != ' ')
		i++;
	name = ft_substr(str + (*dolla), 1, i - (*dolla) - 1);
	env = getenv(name);
	k = *dolla;
	if(!env)
	{
		while (str[i] != '\0')
			str[k++] = str[i++];
		str[k] = '\0';
	}
	else
	{
		res = (char *)malloc(sizeof(char) * (ft_strlen(str) - ft_strlen(name) +
											 ft_strlen(env)));
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

int single_quote(char *str, int *j)
{
	int i;
	int k;

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

int double_quote(char **str, int *j)
{
	int i;
	int k;
	int start;
	int end;
	int old_len;

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
	while (start < end)
	{
		if ((*str)[start] == '$')
		{
			old_len = (int)ft_strlen(*str);
			*str = dollar(*str, &start);
			end = end + ((int)ft_strlen(*str) - old_len);
		}
		else
			start++;
	}
	*j = end - 1;
	return (0);
}


void back_slash(char *str, int j)
{

	int i;

	i = j + 1;

	while (str[i] != '\0')
		str[j++] = str[i++];
	str[j] = '\0';
}

int	check_tokens(char **mas)
{
	int i;
	int j;

	i = 0;
	while(mas[i] != NULL)
	{
		//printf("ols str = |%s|\n", mas[i]);
		j = 0;
		while(mas[i][j] != '\0')
		{
			if(mas[i][j] == '\'')
			{
				if (single_quote(mas[i], &j) == -1)
					return (-1);
				j--;
			}
			else if(mas[i][j] == '\"')
			{
				if (double_quote(&mas[i], &j) == -1)
					return (-1);

			}
			else if(mas[i][j] == '$')
			{
				mas[i] = dollar(mas[i], &j);
			}
			else
				j++;
		}

		//printf("new str = |%s|\n", mas[i]);
		i++;
	}
	return (1);
}