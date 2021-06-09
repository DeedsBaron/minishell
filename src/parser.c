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

char *check_back_slash(char *s, char c)
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\\' && s[i + 1] == (char)c)
			i = i + 2;
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == s[i])
		return ((char *)&s[i]);
	return (NULL);
}

int	count_spaces(char *s)
{
	int	counter;

	counter = 0;
	while (*(s))
	{
		if (*s == '\'' && check_back_slash(s + 1, '\''))
			s = s + (check_back_slash(s + 1, '\'') - s);
		else if (*s == '\"' && check_back_slash(s + 1, '\"'))
			s = s + (check_back_slash(s + 1, '\"') - s);
		else if(*s == '|')
		{
			counter++;
			if(*(s + 1) != ' ' && *(s + 1) != '\0' &&(*(s + 1)
				!= '|'))
				counter++;
		}
		else if (*s == ' '  && *(s + 1) != '|')
			counter++;
		else if (((*s == '>'  && *(s + 1) == '>') || (*s == '<'  && *(s + 1) ==
		'<')) && *(s + 2) != ' ')
		{
			counter++;
			s++;
		}
		else if((*s == '<' || *s == '>') && (*(s + 1) != ' ')  && (*(s + 1)
		!= '<' && *(s + 1) != '>'))
			counter++;
		s++;
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
	return (0);
}

char *sq_case(char **s, int i, char *sq_p)
{
	int end;
	char	*token;
	char	*tmp;
	int		s_qoute;

	end = sq_p - *s;
	while((*s)[end] != ' ' && (*s)[end] != '\0')
	{
		end++;
//		if ((*s)[end] != '\'')
//			sq_case(s, end, (ft_strchr(*s + end + 1, '\'')));
//		if ((*s)[end] != '\"')
//			sq_case(s, end, (ft_strchr(*s + end + 1, '\"')));
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

char *dq_case(char **s, int i, char *sq_p)
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
	token = NULL;
	while ((*s)[i] != '\0')
	{
		if (((*s)[i] == '\'' && ft_strchr(*s + 1+ i, '\'')) || ((*s)[i] ==
		'\"' && ft_strchr(*s + 1+ i, '\"')))
			return (sq_case(s, i, ft_strchr(*s + 1+ i, (*s)[i])));
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
		if ((((*s)[i] == '>'  && (*s)[i + 1] == '>') || ((*s)[i] == '<'  &&
		(*s)[i + 1] == '<')) && (*s)[i + 2] != ' ')
		{
			token = ft_substr((*s), 0, i + 2);
			tmp = ft_substr((*s), i + 2, ft_strlen(*s) - i - 1);
			free(*s);
			(*s) = tmp;
			return (token);
		}
		if (((*s)[i] == '<'  || (*s)[i] == '>') && (*s)[i + 1] != ' ' && (*s)
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
	return(token);
}

char	**make_tokens_massive(char *s)
{
	char	**mas;
	int		i;
	int		c_str;

	i = 0;
	deletespaces(s);
	c_str = count_spaces(s);
	printf("Num of str to malloc %d\n", c_str);
	mas = (char **)malloc(sizeof(char *) * (c_str + 2));
	if (mas == NULL)
		return (NULL);
	while (i < c_str + 1)
	{
		mas[i] = make_token(&s);
		i++;
		// if (s[0] == '\0')
		// 	break;
	}
	free(s);
	mas[i] = NULL;
	return (mas);
}
