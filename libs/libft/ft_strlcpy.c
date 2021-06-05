/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaron <dbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 14:24:15 by dbaron            #+#    #+#             */
/*   Updated: 2020/11/01 14:56:31 by dbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	char		*src_cpy;

	if (dst == NULL || src == NULL)
		return (0);
	if (dstsize == 0)
		return (ft_strlen(src));
	src_cpy = (char *)src;
	if (ft_strlen(src) + 1 <= dstsize)
	{
		while (*src_cpy != '\0')
			*dst++ = *src_cpy++;
		*dst = '\0';
	}
	else
	{
		while (--dstsize > 0)
			*dst++ = *src_cpy++;
		*dst = '\0';
	}
	return (ft_strlen(src));
}
