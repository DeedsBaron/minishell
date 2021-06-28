/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaron <dbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 15:12:57 by dbaron            #+#    #+#             */
/*   Updated: 2021/06/08 15:14:03 by dbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_error(char *command, char *argument, char *str)
{
	if (ft_strcmp("env", command) != 0)
		write(1, "minishell: ", 11);
	write(1, command, ft_strlen(command));
	write(1, ": ", 2);
	if (argument)
	{
		if (ft_strcmp(str, COM_NVI) == 0)
			write(1, "`", 1);
		write(1, argument, ft_strlen(argument));
		if (ft_strcmp(str, COM_NVI) == 0)
			write(1, "\'", 1);
		write(1, ": ", 2);
		if (!str)
		{
			write(1, strerror(errno), ft_strlen(strerror((errno))));
			write(1, "\n", 1);
		}
	}
	write(1, str, ft_strlen(str));
}
