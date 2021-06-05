/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaron <dbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:07:08 by dbaron            #+#    #+#             */
/*   Updated: 2020/11/11 18:21:02 by dbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_is_space(char const *s1, char const *set)
{
	while (*s1 != '\0' && *set != '\0')
	{
		while (*set != '\0')
		{
			if (*s1 == *set)
				return (1);
			set++;
		}
		s1++;
	}
	return (0);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char		*res;
	char const	*start;
	char const	*end;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = s1;
	while (ft_is_space(start, set))
		start++;
	end = s1 + ft_strlen(s1) - 1;
	while (ft_is_space(end, set) && end > start)
		end--;
	res = (char *)malloc((end - start + 2) * sizeof(char));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, start, end - start + 2);
	return (res);
}
