/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 13:16:52 by hchorfi           #+#    #+#             */
/*   Updated: 2021/05/06 13:18:41 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_3params(int *i, int *j, int *d)
{
	*i = 0;
	*j = 0;
	*d = 0;
}

int	my_ternary(int *splited, int i, int d)
{
	if (*splited == 1)
	{
		*splited = 0;
		return (i + 1);
	}
	*splited = 0;
	return (d);
}

void	ft_remove_all1(char *str, int *i, int *start)
{
	char	*s;

	if (str[*i] == '\'' && g_data.sq == 0 && g_data.dq == 0
		&& !(is_escaped(str, *i)))
	{
		g_data.sq = 1;
		s = ft_remove_slashes(str, *start, *i);
		g_data.ptr = ft_stock(g_data.ptr, s, ft_strlen(s));
		*start = (*i) + 1;
		free(s);
		(*i)++;
	}
	if (str[*i] == '\'' && g_data.sq == 1)
	{
		s = ft_substr(str, *start, (*i) - *start);
		g_data.ptr = ft_stock(g_data.ptr, s, (*i) - *start);
		*start = (*i) + 1;
		free(s);
		g_data.sq = 0;
	}
}

void	ft_remove_all2(char *str, int *i, int *start)
{
	char	*s;

	if (str[*i] == '"' && g_data.dq == 0 && g_data.sq == 0
		&& !(is_escaped(str, *i)))
	{
		g_data.dq = 1;
		s = ft_remove_slashes(str, *start, *i);
		g_data.ptr = ft_stock(g_data.ptr, s, ft_strlen(s));
		*start = (*i) + 1;
		free(s);
		(*i)++;
	}
	if (str[*i] == '"' && g_data.dq == 1 && str[*i] != '\0'
		&& !(is_escaped(str, *i)))
	{
		s = ft_remove_slashes_2(str, *start, *i);
		g_data.ptr = ft_stock(g_data.ptr, s, ft_strlen(s));
		*start = (*i) + 1;
		g_data.dq = 0;
		free(s);
	}
}

int	ft_remove_slashes_5(char *str, int i, int end)
{
	int	len;
	int	count;

	len = 0;
	count = 0;
	while (i < end)
	{
		if (str[i] == '\\')
			count++;
		else
		{
			if ((str[i] == '$' || str[i] == '"') && (count % 2))
				len += (count / 2) + 1;
			else
			{
				count++;
				len += count / 2 + 1;
			}
			count = 0;
		}
		i++;
	}
	if (count)
		len += count / 2;
	return (len);
}
