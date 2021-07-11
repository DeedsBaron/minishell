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

char 	*make_token3(char **s, int i, char *token)
{
	char	*tmp;

	token = ft_substr((*s), 0, i);
	tmp = ft_substr((*s), i, ft_strlen(*s) - i + 1);
	free(*s);
	(*s) = tmp;
	return (token);
}

char 	*make_token4(char **s, int i, char *token)
{
	char	*tmp;

	token = ft_substr((*s), 0, i + 1);
	tmp = ft_substr((*s), i + 1, ft_strlen(*s) - i);
	free(*s);
	(*s) = tmp;
	return (token);
}

char 	*make_token5(char **s, int i, char *token)
{
	char	*tmp;

	token = ft_substr((*s), 0, i + 2);
	tmp = ft_substr((*s), i + 2, ft_strlen(*s) - i - 1);
	free(*s);
	(*s) = tmp;
	return (token);
}

char 	*make_token6(char **s, int i, char *token)
{
	char	*tmp;

	token = ft_substr((*s), 0, i + 1);
	tmp = ft_substr((*s), i + 1, ft_strlen(*s) - i);
	free(*s);
	(*s) = tmp;
	return (token);
}

void 	*make_token7(char **s, int i, char *token)
{
	char	*tmp;

	if ((*s)[0] != '\0')
	{
		token = ft_substr((*s), 0, i);
		tmp = ft_substr((*s), i + 1, ft_strlen(*s) - i);
		free(*s);
		(*s) = tmp;
		return (token);
	}
	return (NULL);
}
