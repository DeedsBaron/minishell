/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_array_utilc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 19:19:09 by dbaron            #+#    #+#             */
/*   Updated: 2021/07/03 19:19:11 by dbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	mas_len(char **mas)
{
	int	i;

	i = 0;
	while (mas[i])
		i++;
	return (i);
}

char	**submas(char **mas, long int start, long int len)
{
	int		i;
	char	**new_mas;

	i = 0;
	if (!mas)
		return (NULL);
	if (mas_len(mas) - start < len)
		len = mas_len(mas) - start;
	if (start > mas_len(mas))
		len = 0;
	new_mas = (char **)malloc(sizeof(char *) * (len + 1));
	if (!new_mas)
		return (NULL);
	while (i < len)
	{
		new_mas[i] = ft_strdup(mas[start + i]);
		i++;
	}
	new_mas[i] = NULL;
	return (new_mas);
}

char	**find_str(char **mas, char *str)
{
	long int	i;

	i = 0;
	while (mas[i])
	{
		if (ft_strcmp(mas[i], str) == 0)
			return ((char **)&mas[i]);
		i++;
	}
	return (NULL);
}

char	**new_mas(char **mas, int start, int end)
{
	char	**tmp;
	int		i;
	int		k;

	tmp = (char **)malloc(sizeof(char *) * (mas_len(mas) - (end - start)));
	i = 1;
	k = 0;
	while (i < start)
		tmp[k++] = ft_strdup(mas[i++]);
	i = end;
	while (mas[i] != NULL)
		tmp[k++] = ft_strdup(mas[i++]);
	tmp[k] = NULL;
	return (tmp);
}
