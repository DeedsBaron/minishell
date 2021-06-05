/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaron <dbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 20:35:11 by dbaron            #+#    #+#             */
/*   Updated: 2020/11/15 16:47:13 by dbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int			ccount(char const *s, char c)
{
	int		i;
	int		counter;

	i = 0;
	counter = 0;
	while (*s != '\0')
	{
		if (*s != c && ((*(s + 1) == c) || !*(s + 1)))
		{
			counter++;
		}
		s++;
	}
	return (counter);
}

static int			cuntilc(char const *s, char c)
{
	int		i;

	i = 0;
	while (*s != '\0' && *s != c)
	{
		i++;
		s++;
	}
	return (i);
}

static char			**free_ptr(char **ptr)
{
	int		i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}

static char			**fill_w_strs(char const *s, int words, char c, char **ptr)
{
	int		i;
	int		j;
	int		len;

	i = -1;
	while (++i < words)
	{
		while (*s == c)
			s++;
		len = cuntilc(s, c);
		if (!(ptr[i] = (char *)malloc((len + 1) * sizeof(char))))
			return (free_ptr(ptr));
		j = 0;
		while (j < len)
			ptr[i][j++] = *(s++);
		ptr[i][j] = '\0';
	}
	ptr[i] = NULL;
	return (ptr);
}

char				**ft_split(char const *s, char c)
{
	char	**ptr;
	int		words;

	if (s == NULL)
		return (NULL);
	words = ccount(s, c);
	if (!(ptr = (char **)malloc((ccount(s, c) + 1) * sizeof(char *))))
		return (NULL);
	ptr = fill_w_strs(s, words, c, ptr);
	return (ptr);
}
