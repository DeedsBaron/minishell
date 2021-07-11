/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_n_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wspectra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 18:18:06 by wspectra          #+#    #+#             */
/*   Updated: 2021/07/11 18:18:11 by wspectra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

pid_t 	pipe_fork_2(int *fd)
{
	pid_t	pid;

	pipe (fd);
	pid = fork();
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	return (pid);
}

void	pipe_fork3(void)
{
	signal(SIGINT, &handler);
	signal(SIGQUIT, &handler);
}
