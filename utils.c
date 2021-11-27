/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrozniec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 14:16:10 by mrozniec          #+#    #+#             */
/*   Updated: 2021/11/27 14:16:39 by mrozniec         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

char	**ft_init_child(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && (envp[i][0] != 'P' || envp[i][1] != 'A' || \
	envp[i][2] != 'T' || envp[i][3] != 'H' || envp[i][4] != '='))
		i++;
	if (!envp[i])
		return (NULL);
	return (ft_split(envp[i] + 5, ':'));
}

void	ft_init_child2(int *f, int par, int pipend[2])
{
	if (par == 0)
	{
		dup2(*f, 0);
		dup2(pipend[1], 1);
		close(pipend[0]);
	}
	else
	{
		dup2(*f, 1);
		dup2(pipend[0], 0);
		close(pipend[1]);
	}
}

void	ft_wait_end(int pipend[2], pid_t child_p[2], int *status)
{
	close(pipend[0]);
	close(pipend[1]);
	waitpid(child_p[0], status, 0);
	waitpid(child_p[1], status, 0);
}

int	ft_init_pipex(int *status, int pipend[2], pid_t child_p[2])
{
	*status = 0;
	if (pipe(pipend) == -1)
	{
		perror("pipe error");
		return (-1);
	}
	child_p[0] = fork();
	if (child_p[0] < 0)
	{
		perror("fork error");
		return (-1);
	}
	return (0);
}
