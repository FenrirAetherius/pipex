//
// Created by Maximilien Rozniecki on 9/22/21.
//

#include "pipex.h"

void	ft_free_tab(char **tab)
{
	int i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

char	**ft_init_child(char **envp)
{
	int i;

	i = 0;
	while (envp[i] && (envp[i][0] != 'P' || envp[i][1] != 'A' ||\
	envp[i][2] != 'T' || envp[i][3] != 'H' || envp[i][4] != '='))
		i++;
	if (!envp[i])
		return (NULL);
	return (ft_split(envp[i] + 5, ':')); //mac envp[4] linux envp[14]
}