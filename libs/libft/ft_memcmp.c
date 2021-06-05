/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaron <dbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:56:34 by dbaron            #+#    #+#             */
/*   Updated: 2020/11/01 20:20:15 by dbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *a;
	const unsigned char *b;

	a = (const unsigned char *)s1;
	b = (const unsigned char *)s2;
	while (n-- > 0)
	{
		if (*a++ != *b++)
			return (*--a - *--b);
	}
	return (0);
}
