#include "../includes/minishell.h"

void	exec_export(char **envp[], t_tree *root)
{
	char	**tmp;
	int		i;
	int		k;
	int		m;

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
		k = 1;
		while (root->f_arg[k] != NULL)
		{
			if (ft_isalpha(root->f_arg[k][0]) == 1)
			{
				m = 0;
				while ((*envp)[m]
					   && find_equal_arg((*envp)[m], root->f_arg[k]) == 0)
					m++;
				if (!((*envp)[m]))
					tmp[i++] = ft_strdup(root->f_arg[k++]);
				else
				{
					if (ft_strchr(root->f_arg[k], '='))
					{
						free(tmp[m]);
						tmp[m] = ft_strdup(root->f_arg[k]);
					}
					k++;
				}
			}
			k++;
		}
		tmp[i] = NULL;
		free_mas(*envp);
		(*envp) = tmp;
	}
}

void	exec_unset(char **envp[], t_tree *root)
{
	char	**tmp;
	int		i;
	int		j;
	int		k;

	if (root->f_arg[1] == NULL)
		return ;
	else
	{
		tmp = (char **)malloc(sizeof(char *) * (mas_len((*envp))
												- count_unset_arguments(*envp, root) + 1));
		k = 0;
		i = 0;
//		while (i < (mas_len(*envp) - count_unset_arguments(*envp, root)))
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
				tmp[k] = ft_strdup(envp[0][i]);
				k++;
				i++;
			}
		}
		tmp[k] = NULL;
		free_mas(*envp);
		(*envp) = tmp;
	}
}
