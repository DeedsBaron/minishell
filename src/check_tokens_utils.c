/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wspectra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 19:32:25 by wspectra          #+#    #+#             */
/*   Updated: 2021/07/09 19:32:27 by wspectra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void 	dollar_2(char **str, int *dolla, char *env, char *name)
{
	int		i;
	char	*res;
	int		k;

	res = (char *)malloc(sizeof(char) * (ft_strlen(*str) - ft_strlen(name)
				+ ft_strlen(env)));
	i = -1;
	while (++i < (*dolla))
		res[i] = (*str)[i];
	k = 0;
	while (i < (int)(ft_strlen(env) + (*dolla)))
		res[i++] = env[k++];
	k = *dolla + ft_strlen(name) + 1;
	*dolla = k;
	while ((*str)[k] != '\0')
		res[i++] = (*str)[k++];
	res[i] = '\0';
	free(*str);
	*str = res;
}

int	check_tokens_while(char **str)
{
	int	j;

	j = 0;
	while ((*str)[j] != '\0')
	{
		if ((*str)[j] == '\'')
		{
			if (single_quote((*str), &j) == -1)
				return (-1);
			j--;
		}
		else if ((*str)[j] == '\"')
		{
			if (double_quote(str, &j) == -1)
				return (-1);
		}
		else
			j++;
	}
	return (0);
}
