#include "pipex.h"

static char	**ft_fill_tab(char **tstr1, char **tstr2, char *str)
{
	int i;

	i = -1;
	while (tstr1[++i])
	{
		tstr2[i] = ft_strjoin(tstr1[i], str);
		if (tstr2[i] == NULL)
		{
			ft_free_tab(tstr1);
			ft_free_tab(tstr2);
			return (NULL);
		}
	}
	while(--i >= 0)
		free(tstr1[i]);
	return (tstr2);
}

static char	**ft_fill_path(char *cmd, char **path)
{
	char	**tmp_path;
	int		i;

	i = 0;
	while(path[i])
		i++;
	tmp_path = malloc(sizeof(char *) * (i + 1));
	if (!tmp_path)
		return (NULL);
	tmp_path = ft_fill_tab(path, tmp_path, "/");
	if (tmp_path == NULL)
		return (NULL);
	path = ft_fill_tab(tmp_path, path, cmd);
	if (path == NULL)
		return (NULL);
	free(tmp_path);
	return (path);
}

static void	child(char *cmd, char **envp)
{
	char **cmd_split;
	char **path;
	int i;

	cmd_split = ft_split(cmd, ' ');
	path = ft_init_child(envp); //mac envp[4] linux envp[14]
	if (cmd_split == NULL || path == NULL)
		return (perror("malloc"));
	path = ft_fill_path(cmd_split[0], path);
	if (path == NULL)
		return(perror("malloc"));
	i = -1;
	while (path[++i])
	{
		if (access(path[i], X_OK) >= 0)
		{
			if (execve(path[i], cmd_split, envp) < 0)
				perror("Fail to execve");
			return;
		}
	}
	if (access(cmd_split[0], X_OK) >= 0)
		if (execve(cmd_split[0], cmd_split, envp) < 0)
			perror("Fail to execve");
	return (perror("execve error"));
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

	if (argc == 5)
	{
		f1 = open(argv[1], O_RDONLY);
		f2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (f1 < 0 || f2 < 0)
			return (-1);
		if (argv[2][0] == '\0' && argv[3][0] != '\0')
			pipex(f1, f2, argv[3], argv[3], envp);
		else if (argv[3][0] == '\0' && argv[2][0] != '\0')
			pipex(f1, f2, argv[2], argv[2], envp);
		else
			pipex(f1, f2, argv[2], argv[3], envp);
		close(f1);
		close(f2);
		return (0);
	}
	return (-1);
}
