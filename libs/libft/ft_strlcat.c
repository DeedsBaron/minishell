/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaron <dbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 14:49:06 by dbaron            #+#    #+#             */
/*   Updated: 2020/11/01 19:57:52 by dbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		dst_len;
	size_t		src_len;
	char		*dst_cpy;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	dst_cpy = dst + dst_len;
	if (dst_len >= dstsize)
		return (src_len + dstsize);
	while ((dstsize - dst_len - 1) && *src != '\0')
	{
		*dst_cpy++ = *src++;
		dstsize--;
	}
	*dst_cpy = '\0';
	return (src_len + dst_len);
	return (0);
}
