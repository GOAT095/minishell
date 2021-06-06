/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:25:34 by hchorfi           #+#    #+#             */
/*   Updated: 2021/04/29 11:44:54 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	rtrim(char const *s1, char const *set, int l1)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	start = 0;
	while (s1[i] != '\0')
	{
		while (set[j] != '\0')
		{
			if (set[j] != s1[i])
				j++;
			else
			{
				i++;
				j = 0;
			}
		}
		start = i;
		i = l1;
	}
	return (start);
}

static	int	ltrim(char const *s1, char const *set, int start, int l1)
{
	int		j;
	int		last;

	j = 0;
	l1 = l1 - 1;
	last = l1;
	while (l1 >= start)
	{
		while (set[j] != '\0')
		{
			if (set[j] != s1[l1])
				j++;
			else
			{
				l1--;
				j = 0;
			}
		}
		last = l1;
		l1 = start - 1;
	}
	return (last);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		l1;
	int		i;
	char	*strtrim;
	int		start;
	int		last;

	if (!s1)
		return (0);
	l1 = ft_strlen(s1);
	start = rtrim(s1, set, l1);
	i = 0;
	last = ltrim(s1, set, start, l1);
	strtrim = malloc((last - start + 2) * sizeof(char));
	l1 = last - start + 1;
	while (i < l1)
	{
		strtrim[i] = s1[start];
		i++;
		start++;
	}
	strtrim[i] = '\0';
	return (strtrim);
}
