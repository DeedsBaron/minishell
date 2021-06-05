/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaron <dbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:51:38 by dbaron            #+#    #+#             */
/*   Updated: 2020/11/09 17:47:29 by dbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char *s1_cpy;

	s1_cpy = (char *)malloc(ft_strlen(s1) * sizeof(char) + 1);
	if (s1_cpy == NULL)
		return (NULL);
	ft_strlcpy(s1_cpy, s1, ft_strlen(s1) * sizeof(char) + 1);
	return (s1_cpy);
}
