#include "./includes/minishell.h"
#include "libs/libft/libft.h"

int main(int argc, char *argv[], char *envp[])
{
//	char *str = getenv("PATH");
//	char **mas = ft_split(str, ':');
//	char *name;
//	struct dirent *entry;
//	//printmas(mas, 0);
//	printf("::::::::::::::::::::::::::\n");
//	DIR *folder = opendir("/bin");
//	while ((entry = readdir(folder)) != NULL)
//	{
//		printf("%s\n", entry->d_name);
//		if (ft_strcmp(entry->d_name, "cat") == 0)
//			printf("YES");
//		//free(entry);
//	}
//	closedir(folder);
//	//printf("%s\n", str);
//	//printf("res = %d\n", ft_strcmp("echo", "echo1"));
	char *str;
	char *mas[4];
	mas[0] = "cat";
	mas[3] = NULL;
	execve("/bin/cat", mas, envp);
	return (0);
}