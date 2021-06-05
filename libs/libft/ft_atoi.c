/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaron <dbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 20:00:39 by dbaron            #+#    #+#             */
/*   Updated: 2020/11/03 14:51:09 by dbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*count_sp_signs(const char *str, int *sign, int *count)
{
	while (*str == ' ' || *str == '\t' || *str == '\r'
		|| *str == '\v' || *str == '\n' || *str == '\f'
		|| *str == '-' || *str == '+')
	{
		if (*str == '-')
		{
			(*sign)++;
			if (!(*(str + 1) >= '0' && *(str + 1) <= '9'))
				return (NULL);
		}
		if (*str == '+')
		{
			(*count)++;
		}
		str++;
	}
	return ((char *)str);
}

int				ft_atoi(const char *str)
{
	long long int		res;
	int					sign;
	int					count;
	int					cdigits;

	res = 0;
	sign = 0;
	count = 0;
	cdigits = -1;
	str = count_sp_signs(str, &sign, &count);
	if (str == NULL)
		return (0);
	if (count + sign > 1)
		return (0);
	while ((*str >= '0' && *str <= '9') && (++cdigits >= 0))
		res = res * 10 + (*str++ - '0');
	if (cdigits > 19 && sign == 0)
		return (-1);
	if (cdigits > 19 && sign == 1)
		return (0);
	if (sign == 1)
		return (-res);
	return (res);
}
