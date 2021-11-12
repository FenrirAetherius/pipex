/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrozniec <mrozniec@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 18:02:37 by mrozniec          #+#    #+#             */
/*   Updated: 2021/10/06 17:46:29 by mrozniec         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_skip(const char *s, int n)
{
	if (s[n] == '\"')
	{
		n++;
		while (s[n] != '\"')
			n++;
	}
	return (n);
}

static char	**ft_ttabcrea(char const *s, char c)
{
	int		n;
	int		line;
	char	**strs;

	n = 0;
	line = 0;
	while (s[n] != '\0')
	{
		while (s[n] == c)
			n++;
		if (s[n] != c && s[n] != '\0')
			line++;
		n = ft_skip(s, n);
		while (s[n] != c && s[n] != '\0')
			n++;
	}
	strs = malloc(sizeof(char *) * (line + 1));
	if (!strs)
		return (NULL);
	return (strs);
}

static char	*ft_fillstr(char const *s, char c, int n)
{
	int		m;
	int		p;
	char	*strs;

	m = n;
	while (s[n] != '\0' && s[n] != c)
	{
		n = ft_skip(s, n);
		n++;
	}
	if (s[n - 1] == '\"')
	{
		m++;
		n--;
	}
	m = n - m;
	strs = malloc(sizeof(char) * (m + 1));
	if (!strs)
		return (NULL);
	p = m;
	while (m > 0)
	{
		strs[p - m] = s[n - m];
		m--;
	}
	strs[p] = '\0';
	return (strs);
}

static char	**ft_free_error(char **strs, int line)
{
	while (line > 0)
	{
		free(strs[line - 1]);
		line--;
	}
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		n;
	int		line;
	char	**strs;

	strs = ft_ttabcrea(s, c);
	n = 0;
	line = 0;
	while (s[n] != '\0')
	{
		while (s[n] == c)
			n++;
		if (s[n] != '\0' && s[n] != c)
		{
			line++;
			strs[line - 1] = ft_fillstr(s, c, n);
			if (!strs[line - 1])
				return (ft_free_error(strs, line - 1));
		}
		n = ft_skip(s, n);
		while (s[n] != c && s[n] != '\0')
			n++;
	}
	strs[line] = NULL;
//	n = -1;
//	while(strs[++n])
//		perror(strs[n]);
	return (strs);
}
