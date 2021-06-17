#include "./includes/minishell.h"
#include "libs/libft/libft.h"

int main(int argc, char *argv[], char *envp[])
{
	char *cat[3];
	cat[0] = "cat";
	cat[1] = "3.txt";
	cat[2] = NULL;
	char res[100];
	int fd[2];
	pipe(fd);
	int pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		read(fd[1], res, 100);
		printf("Child fd[1] = %s\n", res);
		execve("/bin/cat", cat, envp);
	}
	char *grep[3];
	grep[0] = "grep";
	grep[1] = "h";
	grep[2] = NULL;
	int pid1 = fork();
	if (pid1 == 0)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		execve("/usr/bin/grep", grep, envp);
	}
	close(fd[0]);
	close(fd[1]);
	return (0);
}