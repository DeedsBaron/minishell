/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 19:44:05 by dbaron            #+#    #+#             */
/*   Updated: 2021/07/03 19:44:08 by dbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		set_exit_code(1, get_envp());
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \b\b\n", 5);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \b\b", 4);
	}
}

int 	status_return(int status)
{
	int	b;

	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
		{
			write(1, "\n", 1);
			return (130);
		}
		if (WTERMSIG(status) == 3)
		{
			write(1, "Quit: 3\n", 9);
			return (131);
		}
	}
	b = status - 255;
	if (b <= 0)
		return (0);
	else
		return (b);
}
