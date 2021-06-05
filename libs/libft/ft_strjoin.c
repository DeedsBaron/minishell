/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaron <dbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:52:44 by dbaron            #+#    #+#             */
/*   Updated: 2020/11/03 16:06:36 by dbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*summ;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	summ = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (summ == NULL)
		return (NULL);
	ft_strlcpy(summ, s1, ft_strlen(s1) + 1);
	ft_strlcpy(summ + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	return (summ);
}
