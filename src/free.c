#include "../includes/minishell.h"

void	free_mas(char **mas)
{
	int	i;

	i = 0;
	if (mas)
	{
		while (mas[i])
		{
			free(mas[i]);
			mas[i] = NULL;
			i++;
		}
		free(mas);
		mas = NULL;
	}
}

void	free_tree(t_tree *node)
{
	if (node)
	{
		if (node->command)
		{
			free(node->command);
			node->command = NULL;
		}
		if (node->f_arg)
		{
			free_mas(node->f_arg);
			node->f_arg = NULL;
		}
		if (node->left)
		{
			free_tree(node->left);
			free(node->left);
			node->left = NULL;
		}
		if (node->right)
		{
			free_tree(node->right);
			free(node->right);
			node->right = NULL;
		}
	}
}