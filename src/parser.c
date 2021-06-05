/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaron <dbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 19:24:31 by dbaron            #+#    #+#             */
/*   Updated: 2021/06/05 20:31:29 by dbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	deletespaces(char *src)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (src[i] == ' ')
		i++;
	while (src[i] != '\0')
	{
		if ((src[i] == ' ' && src[i + 1] == ' ')
			|| (src[i] == ' ' && src[i + 1] == '\0'))
			i++;
		else
		{
			src[k] = src[i];
			k++;
			i++;
		}
	}
	src[k] = '\0';
}

int	count_spaces(char *s)
{
	int	counter;

	counter = 0;
	while (*(s++))
	{
		if (*s == '\'' && ft_strchr(s + 1, '\''))
			s = s + (ft_strchr(s + 1, '\'') - s);
		if (*s == ' ' && *(s + 1) != ' ')
			counter++;
	}
	return (counter);
}

int		find_single_qoute(char *s)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'')
			return (1);
		i++;
	}
	//quote flag
	return (0);
}

char *sq_case(char **s, int i, char *sq_p)
{
	int end;
	char	*token;
	char	*tmp;
	

	end = sq_p - *s;
	while((*s)[end] != ' ' && (*s)[end] != '\0')
		end++;
	token = ft_substr(*s, 0, end);
	if ((*s)[end] != '\0')
	{
			tmp = ft_substr(*s, end + 1, ft_strlen(*s) - end);
			free(*s);
			*s = tmp;
	}
	return (token);
}

char	*make_token(char **s)
{
	int		i;
	char	*token;
	char	*tmp;
	char	*sq_p;

	i = 0;
	sq_p = NULL;
	while ((*s)[i] != '\0')
	{
		if ((*s)[i] == '\'' && ft_strchr(*s + 1+ i, '\''))
		{
			return (sq_case(s, i, ft_strchr(*s + 1+ i, '\'')));
			// sq_p = ft_strchr((*s) + i + 1, '\'');
			// if (sq_p && sq_p + 1 != '\0')
			// {
			// 	token = ft_substr((*s), 0, sq_p - (*s) + 1);
			// 	tmp = ft_strdup(sq_p + 1);
			// 	free(*s);
			// 	(*s) = tmp;
			// 	return (token);
			// }
		}
		if ((*s)[i] == ' ')
		{
			token = ft_substr((*s), 0, i);
			tmp = ft_substr((*s), i + 1, ft_strlen(*s) - i);
			free(*s);
			(*s) = tmp;
			return (token);
		}
		i++;
	}
	token = ft_substr((*s), 0, i);
	return (token);
}

char	**make_tokens_massive(char *s)
{
	char	**mas;
	int		i;
	int		c_str;

	i = 0;
	deletespaces(s);
	printf("str = |%s|\n", s);
	c_str = count_spaces(s);
	printf("Num of str to malloc %d\n", c_str);
	mas = (char **)malloc(sizeof(char *) * (c_str + 2));
	if (mas == NULL)
		return (NULL);
	while (i < c_str + 2)
	{
		mas[i] = make_token(&s);
		i++;
		// if (s[0] == '\0')
		// 	break;
	}
	mas[i - 1] = NULL;
	printmas(mas);
	free(s);
	return (mas);
}
