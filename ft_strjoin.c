/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrozniec <mrozniec@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 18:02:37 by mrozniec          #+#    #+#             */
/*   Updated: 2021/09/13 22:31:23 by mrozniec         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	n;
	unsigned int	m;
	unsigned int	pos;
	char			*s3;

	n = 0;
	m = 0;
	pos = 0;
	while (s1[n] != '\0')
		n++;
	while (s2[m] != '\0')
		m++;
	s3 = malloc(sizeof(char) * (n + m + 1));
	if (!s3)
		return (NULL);
	while (pos < (n + m))
	{
		if (pos < n)
			s3[pos] = s1[pos];
		else
			s3[pos] = s2[pos - n];
		pos++;
	}
	s3[pos] = '\0';
	return (s3);
}
