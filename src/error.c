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
		write(2, "minishell: ", 11);
	write(2, command, ft_strlen(command));
	write(2, ": ", 2);
	if (argument)
	{
		if (ft_strcmp(str, COM_NVI) == 0)
			write(2, "`", 1);
		write(2, argument, ft_strlen(argument));
		if (ft_strcmp(str, COM_NVI) == 0)
			write(2, "\'", 1);
		write(2, ": ", 2);
		if (!str)
		{
			write(2, strerror(errno), ft_strlen(strerror((errno))));
			write(2, "\n", 1);
		}
	}
	write(2, str, ft_strlen(str));
}

void 	set_exit_code(int code, char **envp[])
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*envp)[i])
	{
		if (find_equal_arg((*envp)[i], "?") == 1)
		{
			free((*envp)[i]);
			tmp = ft_itoa(code);
			(*envp)[i] = ft_strjoin("?=", tmp);
			free(tmp);
		}
		i++;
	}
}

void	tokenz_er(t_tree *root, char **envp[])
{
	write(2, "minishell: ", 11);
	write(2, "syntax error near unexpected token `", 36);
	if (root->type == 'l')
		write(2, "<<", 2);
	else if (root->type == 'r')
		write(2, ">>", 2);
	else
		write(2, &root->type, 1);
	write(2, "\'\n", 2);
	set_exit_code(258, envp);
	g_exit_code = 4;
}

void	redirect_err(char *filename)
{
	write(2, "minishel: ", 10);
	write(2, filename, ft_strlen(filename));
	write(2, ": ", 2);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
}
