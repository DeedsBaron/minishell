/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singltones.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 19:45:24 by dbaron            #+#    #+#             */
/*   Updated: 2021/07/03 19:45:26 by dbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	***get_envp(void)
{
	static char	**envp_copy;

	return (&envp_copy);
}

char	**get_str(void)
{
	static char	*str;

	return (&str);
}

void 	set_str(char *value)
{
	*get_str() = value;
}

char	*my_get_env(char **envp, char *str)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (envp[i] && find_equal_arg(envp[i], str) == 0)
		i++;
	if (!(envp[i]))
		return (NULL);
	else
		return (ft_strdup(ft_strchr(envp[i], '=') + 1));
}

int	**get_old_fd(void)
{
	static int	old_fd[2];
	static int	*p_oldfd;

	p_oldfd = old_fd;
	return (&p_oldfd);
}
