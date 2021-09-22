#include "pipex.h"

void child(char *cmd, char **envp)
{
	char **cmd_split;
	char *path;

	cmd_split = ft_split(cmd, ' ');
	path = ft_strjoin("/bin/", cmd_split[0]);
	if (cmd_split == NULL)
		return (perror("malloc split"));
	if (execve("/bin/", &cmd_split[1], envp) == -1)
		return (perror("excecve error"));
}

void    pipex(int f1, int f2, char *cmd1, char *cmd2, char **envp)
{
	int		pipend[2];
	int		status;
	pid_t	child1;
	pid_t	child2;

	if (pipe(pipend) == -1)
		perror("pipe error");
	child1 = fork();
	if (child1 < 0)
		return (perror("fork error"));
	if (child1 == 0)
	{
		dup2(f1, 0);
		dup2(pipend[1], 1);
		close(pipend[0]);
		child(cmd1, envp);
	}
	else
	{
		child2 = fork();
		if (child2 < 0)
			return (perror("fork error"));
		if (child2 == 0)
		{
			perror("hello");
			dup2(f2, 1);
			dup2(pipend[0], 0);
			close(pipend[1]);
			child(cmd2, envp);
		}
	}
	close(pipend[0]);
	close(pipend[1]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
}

int main(int argc, char **argv, char **envp)
{
	int f1;
	int f2;
	f1 = open(argv[1], O_RDONLY);
	f2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (f1 < 0 || f2 < 0)
		return (-1);
	pipex(f1, f2, argv[2], argv[3], envp);
	close(f1);
	close(f2);
	return (0);
}
