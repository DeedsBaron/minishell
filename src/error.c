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

void		print_error(char *command, char *argument)
{
	write(1, "minishell: ", 11);
	write(1, command, ft_strlen(command));
	write(1,": ", 2);
	if (argument)
	{
		write(1, argument, ft_strlen(argument));
		write(1, ": ", 2);
		write(1, strerror(errno), ft_strlen(strerror((errno))));
		write(1, "\n", 1);
	}
	write(1, COM_NF, ft_strlen(COM_NF));
}