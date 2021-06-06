/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 13:13:54 by hchorfi           #+#    #+#             */
/*   Updated: 2021/05/06 13:15:41 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_remove_slashes3(int i, char *str, int end)
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
			len += count / 2 + 1;
			count = 0;
		}
		i++;
	}
	if (count)
		len += count / 2;
	return (len);
}

void	ft_remove_slashes4(char *str, char **back, int end, int i)
{
	int	count;
	int	j;

	count = 0;
	j = 0;
	while (i < end)
	{
		if (str[i] == '\\')
			count++;
		else
		{
			fill_with(*back, j, count / 2, '\\');
			j += count / 2;
			count = 0;
			(*back)[j] = str[i];
			j++;
		}
		i++;
	}
	if (count)
		fill_with(*back, j, count / 2, '\\');
	j += count / 2;
	(*back)[j] = '\0';
}

void	ft_remove_slashes_7(int count, int *j, char **back)
{
	if (count)
		fill_with(*back, *j, count / 2, '\\');
	(*j) += count / 2;
	(*back)[*j] = '\0';
}

char	*ft_remove_slashes_6(char *str, int i, int end, int len)
{
	char	*back;
	int		count;
	int		j;

	back = malloc(sizeof(char) * (len + 1));
	count = 0;
	j = 0;
	while (i < end)
	{
		if (str[i] == '\\')
			count++;
		else
		{
			if (!((str[i] == '$' || str[i] == '"') && (count % 2)))
				count++;
			fill_with(back, j, count / 2, '\\');
			j += count / 2;
			count = 0;
			back[j] = str[i];
			j++;
		}
		i++;
	}
	ft_remove_slashes_7(count, &j, &back);
	return (back);
}

char	*ft_remove_slashes_2(char *str, int start, int end)
{
	int		len;
	char	*back;

	len = ft_remove_slashes_5(str, start, end);
	back = ft_remove_slashes_6(str, start, end, len);
	return (back);
}
