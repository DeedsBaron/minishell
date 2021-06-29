#include "./includes/minishell.h"
#include "libs/libft/libft.h"

void 	handler(int shit)
{
	write(1, "\b\bHERE\n", 7);
	exit(0);
}

int main(int argc, char *argv[], char *envp[])
{
	signal(SIGINT, handler);
	while(1);
	return (0);
}