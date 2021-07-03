#include "../includes/minishell.h"

char ***get_envp()
{
	static 	char	**envp_copy;
	return (&envp_copy);
}

char	**get_str()
{
	static char *str;
	return (&str);
}

void 	set_str(char *value)
{
	*get_str() = value;
}

char	*my_get_env(char **envp, char *str)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (envp[i] && find_equal_arg(envp[i], str) == 0)
		i++;
	if (!(envp[i]))
		return (NULL);
	else
		return (ft_strdup(ft_strchr(envp[i], '=') + 1));
}