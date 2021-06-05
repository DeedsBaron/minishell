/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaron <dbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:08:13 by dbaron            #+#    #+#             */
/*   Updated: 2020/10/31 19:17:51 by dbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	char	*p;

	p = (char *)s + ft_strlen(s);
	while (p >= s)
	{
		if (*p == c)
			return (p);
		p--;
	}
	return (NULL);
}
