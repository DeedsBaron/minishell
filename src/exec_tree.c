/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaron <dbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 16:40:25 by dbaron            #+#    #+#             */
/*   Updated: 2021/06/13 16:40:26 by dbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char 	**make_bin_folders(char )

void	exec_echo(t_tree *root)
{
	if ((root->flags)[0] == 'n')
		write(1, root->arguments, ft_strlen(root->arguments));
	else
	{
		write(1, root->flags, ft_strlen(root->flags));
		write(1, root->arguments, ft_strlen(root->arguments));
		write(1, "\n", 1);
	}
}

void 	exec_command(t_tree *root)
{
	char	**folders;

	folders = make_bin_folders(folders)
	if (ft_strcmp(root->command, "echo") == 0)
		exec_echo(root);
}

void 	exec_tree(t_tree *root)
{
	if (root->type == 'c')
		exec_command(root);
}