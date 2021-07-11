/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 19:28:00 by dbaron            #+#    #+#             */
/*   Updated: 2021/07/03 19:28:02 by dbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void 	export_while(t_tree *root, int *i, char **envp[], char ***tmp)
{
	int	k;
	int	m;

	k = 1;
	while (root->f_arg[k] != NULL)
	{
		if (check_identifier_validity(root->f_arg[k]) == 1)
		{
			m = 0;
			while ((*envp)[m]
				   && find_equal_arg((*envp)[m], root->f_arg[k]) == 0)
				m++;
			if (!((*envp)[m]))
				(*tmp)[(*i)++] = ft_strdup(root->f_arg[k]);
			else
			{
				if (ft_strchr(root->f_arg[k], '='))
				{
					free((*tmp)[m]);
					(*tmp)[m] = ft_strdup(root->f_arg[k]);
				}
			}
		}
		k++;
	}
}

void	exec_export(char **envp[], t_tree *root)
{
	char	**tmp;
	int		i;

	if (root->f_arg[1] == NULL)
	{
		print_export((*envp));
	}
	else if (count_arguments(root->f_arg, root, 0, envp) != 1)
	{
		tmp = (char **)malloc(sizeof(char *) * (mas_len((*envp))
					+ count_arguments(root->f_arg, root, 1, envp)));
		i = 0;
		while ((*envp)[i] != NULL)
		{
			tmp[i] = ft_strdup((*envp)[i]);
			i++;
		}
		export_while(root, &i, envp, &tmp);
		tmp[i] = NULL;
		free_mas(*envp);
		(*envp) = tmp;
	}
}

void 	unset_while(t_tree *root, char **envp[], char ***tmp)
{
	int	i;
	int	k;
	int	j;

	k = 0;
	i = 0;
	while ((*envp)[i])
	{
		j = 1;
		while (root->f_arg[j] && find_equal_arg((*envp)[i],
			root->f_arg[j]) != 1)
			j++;
		if (find_equal_arg((*envp)[i], root->f_arg[j]) == 1)
			i++;
		else
		{
			(*tmp)[k] = ft_strdup(envp[0][i]);
			k++;
			i++;
		}
	}
	(*tmp)[k] = NULL;
}

void	exec_unset(char **envp[], t_tree *root)
{
	char	**tmp;

	if (root->f_arg[1] == NULL)
		return ;
	else
	{
		tmp = (char **)malloc(sizeof(char *) * (mas_len((*envp))
					- count_unset_arguments(*envp, root) + 1));
		unset_while(root, envp, &tmp);
		free_mas(*envp);
		(*envp) = tmp;
	}
}

void	exec_env(t_tree *root, char **envp[])
{
	if (root->f_arg[1] == NULL)
		print_env(*envp);
	else if (open(root->f_arg[1], O_RDONLY) == -1)
	{
		print_error(root->command, root->f_arg[1], NULL);
		set_exit_code(126, envp);
	}
	else
	{
		print_error(root->command, root->f_arg[1], NO_FILE);
		set_exit_code(127, envp);
	}
}
