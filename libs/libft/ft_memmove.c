/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaron <dbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:24:18 by dbaron            #+#    #+#             */
/*   Updated: 2020/10/30 19:13:50 by dbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char				*a;
	const unsigned char			*b;

	a = dst;
	b = src;
	if (dst == NULL && src == NULL)
		return (dst);
	if (a < b)
	{
		while (len--)
			*a++ = *b++;
	}
	else
	{
		a = dst + len - 1;
		b = src + len - 1;
		while (len--)
			*a-- = *b--;
	}
	return (dst);
}
