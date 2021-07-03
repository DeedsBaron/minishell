#include "../includes/minishell.h"

void 	inc_shlvl(char **envp[], int incdecr)
{
	int	i;
	int level;
	char *tmp;
	char *buf;

	i = 0;
	buf = my_get_env(*envp, "SHLVL");
	level = ft_atoi(buf);
	free(buf);
	while ((*envp)[i])
	{
		if (find_equal_arg((*envp)[i], "SHLVL") == 1)
		{
			free((*envp)[i]);
			tmp = ft_itoa(level + incdecr);
			(*envp)[i] = ft_strjoin("SHLVL=", tmp);
			free(tmp);
		}
		i++;
	}
}

void	delete_old_pwd(char ***tmp)
{
	int		i;
	char	**mas;
	char	*buf;

	i = 0;
	mas = (char **)malloc(sizeof(char *) * (mas_len(*tmp) + 3));
	while ((*tmp)[i])
	{
		if (find_equal_arg((*tmp)[i], "OLDPWD") == 1)
			mas[i] = ft_strdup("OLDPWD");
		else
			mas[i] = ft_strdup((*tmp)[i]);
		i++;
	}
	mas[i] = ft_strdup("?=0");
	buf = my_get_env(*tmp, "HOME");
	mas[i + 1]= ft_strjoin("~=", buf);
	mas[i + 2] = NULL;
	inc_shlvl(&mas, 1);
	free_mas(*tmp);
	free(buf);
	*tmp = mas;
}

char	**make_envp_copy(char **envp)
{
	char		**tmp;
	int			i;
	static int	flag;

	flag = 0;
	tmp = (char **)malloc ((sizeof(char *) * (mas_len(envp)) + 1));
	i = 0;
	while (envp[i] != NULL)
	{
		tmp[i] = ft_strdup(envp[i]);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}