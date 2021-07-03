/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaron <dbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 19:24:31 by dbaron            #+#    #+#             */
/*   Updated: 2021/06/08 15:48:42 by dbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*sq_case(char **s, char *sq_p)
{
	int		end;
	char	*token;
	char	*tmp;

	end = sq_p - *s + 1;
	while ((*s)[end] != ' ' && (*s)[end] != '\0')
	{
		if ((*s)[end] == '\'')
		{
			end++;
			while ((*s)[end] != '\'' && (*s)[end] != '\0')
				end++;
		}
		else if ((*s)[end] == '\"')
		{
			end++;
			while ((*s)[end] != '\"' && (*s)[end] != '\0')
				end++;
		}
		end++;
	}
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
	token = NULL;
	while ((*s)[i] != '\0')
	{
		if (((*s)[i] == '\'' && ft_strchr(*s + 1 + i, '\'')) || ((*s)[i] ==
		'\"' && ft_strchr(*s + 1 + i, '\"')))
			return (sq_case(s, ft_strchr(*s + 1 + i, (*s)[i])));
		if ((*s)[i] == ' ')
		{
			token = ft_substr((*s), 0, i);
			tmp = ft_substr((*s), i + 1, ft_strlen(*s) - i);
			free(*s);
			(*s) = tmp;
			return (token);
		}
		if (((*s)[i] == '|') && i != 0)
		{
			token = ft_substr((*s), 0, i);
			tmp = ft_substr((*s), i, ft_strlen(*s) - i + 1);
			free(*s);
			(*s) = tmp;
			return (token);
		}
		if (((*s)[i] == '|' || (*s)[i] == ';') && i == 0 && (*s)[i + 1] != ' ')
		{
			token = ft_substr((*s), 0, i + 1);
			tmp = ft_substr((*s), i + 1, ft_strlen(*s) - i);
			free(*s);
			(*s) = tmp;
			return (token);
		}
		if ((((*s)[i] == '>' && (*s)[i + 1] == '>') || ((*s)[i] == '<' &&
		(*s)[i + 1] == '<')) && (*s)[i + 2] != ' ')
		{
			token = ft_substr((*s), 0, i + 2);
			tmp = ft_substr((*s), i + 2, ft_strlen(*s) - i - 1);
			free(*s);
			(*s) = tmp;
			return (token);
		}
		if (((*s)[i] == '<' || (*s)[i] == '>') && (*s)[i + 1] != ' ' && (*s)
		[i + 1] != '>' && (*s)[i + 1] != '<')
		{
			token = ft_substr((*s), 0, i + 1);
			tmp = ft_substr((*s), i + 1, ft_strlen(*s) - i);
			free(*s);
			(*s) = tmp;
			return (token);
		}
		i++;
	}
	if ((*s)[0] != '\0')
	{
		token = ft_substr((*s), 0, i);
		tmp = ft_substr((*s), i + 1, ft_strlen(*s) - i);
		free(*s);
		(*s) = tmp;
	}
	return (token);
}

char	**make_tokens_massive(char *s, char **envp)
{
	char	**mas;
	int		i;
	int		c_str;

	i = 0;
	deletespaces(s);
	s = str_dollar(s, envp);
	c_str = count_spaces(s);
	if (*s == '\0')
	{
		free(s);
		return (NULL);
	}
	mas = (char **)malloc(sizeof(char *) * (c_str + 2));
	if (mas == NULL)
		return (NULL);
	while (i < c_str + 1)
	{
		mas[i] = make_token(&s);
		i++;
	}
	free(s);
	mas[i] = NULL;
	return (mas);
}
