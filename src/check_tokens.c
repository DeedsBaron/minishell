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

void single_quote(char *str)
{
	int	i;
	int k;

	i = 0;
	k = 0;
	if (count_quotes(str, '\'') % 2 != 0)
		print_error(MULTILINE);
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			i++;
		else
			str[k++] = str[i++];
	}
	str[k] = '\0';
}

void double_quote(char *str)
{

}

char	*dollar(char *str, int dolla)
{
	char	*name;
	char	*env;
	char 	*res;
	int 	i;
	int		k;

	k = 0;
	i = dolla;
	env = NULL;
	while (str[i] != '\0' && str[i] != '\'' && str[i] != '\"')
		i++;
	name = ft_substr(str + dolla, 1, i - dolla - 1);
	env = getenv(name);
	if(!env)
	{
		while (str[i] != '\0')
			str[dolla++] = str[i++];
		str[dolla] = '\0';
	}
	else
	{
		int z =(ft_strlen(str) - ft_strlen(name) +
				ft_strlen(env) + 1);
		res = (char *)malloc(sizeof(char) * (ft_strlen(str) - ft_strlen(name) +
				ft_strlen(env)));
		i = -1;
		while (++i < dolla)
			res[i] = str[i];
		while (i < ft_strlen(env) + dolla)
			res[i++] = env[k++];
		k = dolla + ft_strlen(name) + 1;
		while (str[k] != '\0')
			res[i++] = str[k++];
		res[i] = '\0';
		free(str);
		str = res;
	}
	return (str);
}

void	check_tokens(char **mas)
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
				single_quote(mas[i]);
				break;
			}
			if(mas[i][j] == '\"')
			{
				double_quote(mas[i]);
				break;
			}
			if(mas[i][j] == '$')
			{
				mas[i] = dollar(mas[i], j);
			}
			j++;
		}
		//printf("new str = |%s|\n", mas[i]);
		i++;
	}
}