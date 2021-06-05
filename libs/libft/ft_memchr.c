/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaron <dbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:16:49 by dbaron            #+#    #+#             */
/*   Updated: 2020/11/13 19:13:27 by dbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_c;
	unsigned int	i;

	s_c = (unsigned char *)s;
	i = 0;
	while (i < n && s_c[i] != (unsigned char)c)
		i++;
	if (i == n)
		return (NULL);
	return ((void *)&s_c[i]);
}
