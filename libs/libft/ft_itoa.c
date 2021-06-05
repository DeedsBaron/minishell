/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaron <dbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:49:37 by dbaron            #+#    #+#             */
/*   Updated: 2020/11/06 18:00:53 by dbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			cdigits(int n)
{
	int		i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		n = n * (-1);
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char			*fillabovezero(char *str, int i, int n)
{
	i = cdigits(n);
	str[i] = '\0';
	while (--i + 1 > 0)
	{
		str[i] = n % 10 + '0';
		n = n / 10;
	}
	return (str);
}

static char			*fillbelozero(char *str, int i, int n, long gg)
{
	str[0] = '-';
	i = cdigits(n);
	gg = (long int)n * (-1);
	str[i + 1] = '\0';
	while (i > 0)
	{
		str[i] = gg % 10 + '0';
		gg = gg / 10;
		i--;
	}
	return (str);
}

char				*ft_itoa(int n)
{
	char			*str;
	int				i;
	long long int	gg;

	i = 0;
	gg = 0;
	if (n >= 0)
	{
		str = (char *)malloc((cdigits(n) + 1) * sizeof(char));
		if (str == NULL)
			return (NULL);
		fillabovezero(str, i, n);
	}
	else
	{
		str = (char *)malloc((cdigits(n) + 2) * sizeof(char));
		if (str == NULL)
			return (NULL);
		fillbelozero(str, i, n, gg);
	}
	return (str);
}
