#include "../includes/minishell.h"

int mas_len(char **mas)
{
	int i;
	while(mas[i])
		i++;
	return(i);
}
char **submas(char **mas, long int start, long int len)
{
	int i;
	char **new_mas;

	i = 0;
	if (!mas)
		return (NULL);
	if (mas_len(mas) - start < len)
		len = mas_len(mas) - start;
	if (start > mas_len(mas))
		len = 0;
	new_mas = (char **)malloc(sizeof(char*) * (len + 1));
	if (!new_mas)
		return (NULL);
	while(i < len)
	{
		new_mas[i] = mas[start + i];
		i++;
	}
	new_mas[i] = NULL;
	return(new_mas);
}

char **find_str(char **mas,  char *str)
{
	long int	i;

	i = 0;
	while (mas[i])
	{
		if (ft_strncmp(mas[i], str, ft_strlen(mas[i])) == 0)
			return ((char **)&mas[i]);
		i++;
	}
		return (NULL);
}

void make_flags_arguments(char **mas, t_tree *node)
{
	int k;
	char *tmp;

	k = 1;
	node->command = mas[0];
	if(mas[k] && mas[k][0] == '-')
	{
		node->flags  = (char *)malloc(sizeof(char) * 1);
		node->flags[0] = '\0';
	}
	while(mas[k] && mas[k][0] == '-')
	{
		tmp = ft_strjoin(node->flags, mas[k] + 1);
		free (node->flags);
		node->flags = tmp;
		k++;
	}
	if(mas[k])
	{
		node->arguments  = (char *)malloc(sizeof(char) * 1);
		node->arguments[0] = '\0';
	}

	while(mas[k])
	{
		tmp = ft_strjoin(node->arguments, mas[k]);
		free(node->arguments);
		node->arguments = tmp;
		if (mas[k + 1])
		{
			tmp = ft_strjoin(node->arguments, " ");
			free(node->arguments);
			node->arguments = tmp;
		}
		k++;
	}
}

void *make_tree(char **mas)
{
	t_tree *zero_node = malloc(sizeof(t_tree));
 	zero_node->left = NULL;
 	zero_node->right = NULL;
 	zero_node->type = '0';
 	zero_node->command = NULL;
 	if (find_str(mas, "|"))
 	{
 		zero_node->type = '|';
 		zero_node->left = make_tree(submas(mas, 0, (find_str(mas, "|") - mas)));
 		zero_node->right = make_tree(submas(mas, (find_str(mas, "|") - mas) + 1,
											mas_len((mas))));
 	}
 	else if (find_str(mas, "<"))
 	{
 		zero_node->type = '<';
 		zero_node->left = make_tree(submas(mas, 0, (find_str(mas, "<") - mas)));
 		zero_node->right = make_tree(submas(mas, (find_str(mas, "<") - mas) + 1,
 											   mas_len(mas)));
 	}
 	else if (find_str(mas, "<<"))
 	{
 		zero_node->type = 'l';
 		zero_node->left = make_tree(submas(mas, 0, (find_str(mas, "<<") - mas)));
 		zero_node->right = make_tree(submas(mas, (find_str(mas, "<<") - mas) + 1,
 											   mas_len(mas)));
 	}
 	else if (find_str(mas, ">"))
 	{
 		zero_node->type = '>';
 		zero_node->left = make_tree(submas(mas, 0, (find_str(mas, ">") - mas)));
 		zero_node->right = make_tree(submas(mas, (find_str(mas, ">") - mas) + 1,
 											   mas_len(mas)));
 	}
	else if (find_str(mas, ">>"))
	{
		zero_node->type = '>';
		zero_node->left = make_tree(submas(mas, 0, (find_str(mas, ">>") -
		mas)));
		zero_node->right = make_tree(submas(mas, (find_str(mas, ">>") - mas)
		+ 1,
											mas_len(mas)));
	}
 	else
 	{
 		zero_node->type = 'c';
 		make_flags_arguments(mas, zero_node);
 		zero_node->left = NULL;
 		zero_node->right = NULL;
 	}
//	free_mas(mas);
 	return(zero_node);
}
