/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 22:58:17 by hchorfi           #+#    #+#             */
/*   Updated: 2019/10/23 16:45:32 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nw(char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (s[0] != '\0')
		j = 1;
	while (s[i] == c && s[i] != '\0')
		i++;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i - 1] != c)
		{
			i++;
			j++;
		}
		else
			i++;
	}
	return (j);
}

static int	ft_w(char *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] != c && s[i] != '\0')
	{
		len++;
		i++;
	}
	return (len);
}

char	**ft_split(char const *s, char c, int k)
{
	char	**split;
	int		i;
	int		j;

	i = 0;
	j = 0;
	split = malloc(sizeof(char *) * (ft_nw((char *)s, c) + 1));
	if (!s || !split)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			split[j] = malloc(sizeof(char) * (ft_w((char *)s, c, i) + 1));
			while (s[i] != c && s[i] != '\0')
				split[j][k++] = s[i++];
			split[j++][k] = '\0';
			k = 0;
		}
	}
	split[j] = 0;
	return (split);
}
