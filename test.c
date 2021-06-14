#include "./includes/minishell.h"
#include "libs/libft/libft.h"

int main(void)
{
	char *str = getenv("PATH");
	char **mas = ft_split(str, ':');
	char *name;
	struct dirent *entry;
	//printmas(mas, 0);
	printf("::::::::::::::::::::::::::\n");
	DIR *folder = opendir("/bin");
	while ((entry = readdir(folder)) != NULL)
	{
		if (ft_strcmp(entry->d_name, "cat") == 0)
			printf("YES");
		//free(entry);
	}
	closedir(folder);
	//printf("%s\n", str);
	//printf("res = %d\n", ft_strcmp("echo", "echo1"));
	return (0);
}