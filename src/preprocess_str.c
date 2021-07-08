/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 19:41:05 by dbaron            #+#    #+#             */
/*   Updated: 2021/07/03 19:41:06 by dbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	count_while_2(char **s, int *counter)
{
	if (**s == ' ' && **(s + 1) != '|')
		(*counter)++;
	else if (**s == '|' && **(s + 1) == '\0')
		(*counter)++;
	else if (((**s == '>' && **(s + 1) == '>')
			  || (**s == '<' && **(s + 1) == '<')) && **(s + 2) != ' ')
	{
		(*counter)++;
		(*s)++;
	}
	else if ((**s == '<' || **s == '>') && (**(s + 1) != ' ')
		&& (**(s + 1) != '<' && **(s + 1) != '>'))
		(*counter)++;
}

void	count_while(char **s, int *counter)
{
	if ((**s) == '\'')
	{
		(*s)++;
		while ((**s) != '\'' && (**s) != '\0')
			(*s)++;
	}
	if ((**s) == '\"')
	{
		(*s)++;
		while ((**s) != '\"' && (**s) != '\0')
			(*s)++;
	}
	if (**s == '|' && **(s + 1) != '\0')
	{
		(*counter)++;
		if (**(s + 1) != ' ' && **(s + 1) != '\0' && (**(s + 1) != '|'))
			(*counter)++;
	}
	else
		count_while_2(s, counter);
}

int	count_spaces(char *s)
{
	int	counter;

	counter = 0;
	while (*(s) != '\0')
	{
		count_while(&s, &counter);
		s++;
	}
	return (counter);
}

void	deletespaces(char *src)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (src[i] == ' ')
		i++;
	while (src[i] != '\0')
	{
		if (src[i] == '\'')
			check_sq(src, &i, &k);
		else if (src[i] == '\"')
		{
			src[k++] = src[i++];
			while (src[i] != '\"' && src[i] != '\0')
				src[k++] = src[i++];
			src[k++] = src[i++];
		}
		else if ((src[i] == ' ' && src[i + 1] == ' ')
			|| (src[i] == ' ' && src[i + 1] == '\0'))
			i++;
		else
			src[k++] = src[i++];
	}
	src[k] = '\0';
}

char	*str_dollar(char *str, char **envp)
{
	int	i;
	int	k;

	k = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' && str[i] != '\0')
				i++;
		}
		if (str[i] == '$' && str[i + 1] != ' '
			&& str[i + 1] != '\0' && str[i + 1] != '\"')
			str = dollar(str, &i, envp);
		else if (str[i] != '\0')
			i++;
	}
	return (str);
}
