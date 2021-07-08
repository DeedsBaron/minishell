/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 19:43:16 by dbaron            #+#    #+#             */
/*   Updated: 2021/07/03 19:43:17 by dbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char 	*redirect_out(t_tree *root, int *flag)
{
	int		fd;
	char	*name;

	if (root->right->type == '>' || root->right->type == 'r'
		|| root->right->type == '<' || root->right->type == 'l')
		name = root->right->left->command;
	else
		name = root->right->command;
	if (root->type == '>')
		fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		*flag = -2;
		return (name);
	}
	dup2(fd, 1);
	close(fd);
	return (NULL);
}

char	*redirect_in(t_tree *root, char **envp, int *flag)
{
	int		fd;
	char	*name;

	if (root->right->type == '<' || root->right->type == 'l'
		|| root->right->type == '>' || root->right->type == 'r')
		name = root->right->left->command;
	else
		name = root->right->command;
	if (root->type == '<')
		fd = open(name, O_RDONLY, 0644);
	else
		fd = here_doc(name, envp);
	if (fd < 0)
	{
		*flag = -1;
		return (name);
	}
	dup2(fd, 0);
	close(fd);
	return (NULL);
}

char	*redirect(t_tree *root, char **envp, int *flag)
{
	if (root->type == '>' || root->type == 'r')
		return (redirect_out(root, flag));
	else if (root->type == '<' || root->type == 'l')
		return (redirect_in(root, envp, flag));
	return (NULL);
}

void	here_doc_while(int *fd, char *name, char **envp)
{
	char	*str;
	int		i;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(fd[0]);
	str = readline("> ");
	while ((str != NULL) && ft_strcmp(str, name) != 0)
	{
		i = 0;
		while (str[i] != '\0')
		{
			if (str[i] == '$')
				str = dollar(str, &i, envp);
			else
				i++;
		}
		write(fd[1], str, ft_strlen(str));
		write(fd[1], "\n", 1);
		free(str);
		str = readline("> ");
	}
	exit(EXIT_SUCCESS);
}

int	here_doc(char *name, char **envp)
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		here_doc_while(fd, name, envp);
	wait(NULL);
	signal(SIGINT, &handler);
	signal(SIGQUIT, &handler);
	close(fd[1]);
	return (fd[0]);
}
