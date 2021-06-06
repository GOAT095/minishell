/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 13:06:49 by hchorfi           #+#    #+#             */
/*   Updated: 2021/05/06 13:27:43 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_escaped(char *s, int j)
{
	int	i;

	i = 0;
	j--;
	while (j >= 0 && s[j] == '\\')
	{
		j--;
		i++;
	}
	return (i % 2);
}

int	chec_before(char *s, int i, char c)
{
	if (s[i - 1] == c && !is_escaped(s, i - 1))
		return (0);
	return (1);
}

int	countt(char *s, char c)
{
	int	i;
	int	w;

	i = 0;
	w = 0;
	while (1)
	{
		if (((s[i] == c && i != 0) || (s[i] == '\0' && i > 0))
			&& chec_before(s, i, c) && !is_escaped(s, i))
			w++;
		if (s[i] == '\0')
			break ;
		i++;
	}
	return (w);
}

char	**ft_free(char **s, int j)
{
	while (j)
	{
		free(s[j--]);
	}
	free(s);
	return (NULL);
}

int	ft_count(const char *s, int l)
{
	int	i;

	i = 0;
	while (i < l && s[i] != '\0')
	{
		i++;
	}
	return (i);
}
