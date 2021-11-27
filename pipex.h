/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrozniec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 14:18:16 by mrozniec          #+#    #+#             */
/*   Updated: 2021/11/27 14:18:23 by mrozniec         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_free_tab(char **tab);
char	**ft_init_child(char **envp);
void	ft_init_child2(int *f, int par, int pipend[2]);
void	ft_wait_end(int pipend[2], pid_t child_p[2], int *status);
int		ft_init_pipex(int *status, int pipend[2], pid_t child_p[2]);
#endif
