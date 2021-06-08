/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaron <dbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 23:06:30 by whitepunk         #+#    #+#             */
/*   Updated: 2021/01/08 18:07:24 by dbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdio.h>

//void			ft_bzero(void *s, size_t n)
//{
//	unsigned char	*dest;
//	size_t			i;
//
//	dest = s;
//	if (n == 0)
//		return ;
//	i = 0;
//	while (i < n)
//	{
//		dest[i] = '\0';
//		i++;
//	}
//	return ;
//}

char			*ft_dup_n_free(char *line, char *ost, int check)
{
	char	*save;

	if (check == 1)
	{
		save = line;
		line = ft_strjoin(line, ost);
		free(save);
		return (line);
	}
	save = line;
	line = ft_strdup(ost);
	free(save);
	return (line);
}

char			*check_ost(char **ost, char **line)
{
	char			*p2n;

	p2n = NULL;
	if (*ost)
	{
		if ((p2n = ft_strchr(*ost, '\n')))
		{
			*p2n = '\0';
			p2n++;
			*line = ft_dup_n_free(*line, *ost, 0);
			*ost = ft_dup_n_free(*ost, p2n, 0);
		}
		else
		{
			*line = ft_dup_n_free(*line, *ost, 0);
			ft_bzero(*ost, ft_strlen(*ost));
		}
	}
	return (p2n);
}

int				init(char **line, char **buff, int fd, int *size)
{
	*size = 0;
	if (!line)
		return (-1);
	if (fd < 0 || fd > 256)
		return (-1);
	if (BUFFER_SIZE <= 0)
		return (-1);
	if (!(*line = (char *)malloc(sizeof(char) * 1)))
		return (-1);
	**line = '\0';
	if (!(*buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (-1);
	if (read(fd, buff, 0) < 0)
		return (-1);
	return (0);
}

int				get_next_line(int fd, char **line)
{
	char			*buff;
	char			*p2n;
	static char		*ost;
	int				size;

	if (init(line, &buff, fd, &size) != 0)
		return (-1);
	p2n = check_ost(&ost, line);
	while (!p2n && (size = read(fd, buff, BUFFER_SIZE)))
	{
		buff[size] = '\0';
		if ((p2n = ft_strchr(buff, '\n')))
		{
			*p2n++ = '\0';
			ost = ft_dup_n_free(ost, p2n, 0);
		}
		*line = ft_dup_n_free(*line, buff, 1);
	}
	free(buff);
	if (size || p2n)
		return (1);
	free(ost);
	return (0);
}
