/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 13:11:52 by hchorfi           #+#    #+#             */
/*   Updated: 2021/05/06 14:01:07 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_ch_do(int i, int c, char *s)
{
	while (s[i])
	{
		if (s[i] == '\\')
			c++;
		i++;
	}
	return (c);
}

int	ft_rep_var_2(int value_len, char *value, char *ptr, int *i)
{
	int	x;

	x = 0;
	while (x < value_len)
	{
		ptr[*i + x] = value[x];
		x++;
	}
	return (x);
}

char	*ft_replace_variable(char *str, char *value, int k, int j)
{
	int		i;
	char	*ptr;
	int		value_len;

	i = 0;
	value_len = ft_strlen(value);
	ptr = (char *)malloc(value_len + ft_strlen(str) - j + k + 1);
	while (i < k)
	{
		ptr[i] = str[i];
		i++;
	}
	i = i + ft_rep_var_2(value_len, value, ptr, &i);
	j++;
	while (str[j])
	{
		ptr[i] = str[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
	return (ptr);
}

void	ft_get_var3(int *s_quote, int *d_quote, int *j, char *str)
{
	if (str[*j] == '\"' && !(is_escaped(str, *j)))
	{
		if (*d_quote == 0)
			*d_quote = 1;
		else
			*d_quote = 0;
		(*j)++;
	}
	if (str[*j] == '\'' && !(is_escaped(str, *j)) && *d_quote == 0)
	{
		if (*s_quote == 0)
			*s_quote = 1;
		else
			*s_quote = 0;
		(*j)++;
	}
}

int	ft_get_var2(int j, char *str, int *k, int i)
{
	int		s_quote;
	int		d_quote;

	s_quote = 0;
	d_quote = 0;
	while (j < i)
	{
		ft_get_var3(&s_quote, &d_quote, &j, str);
		if (str[j] == '$' && s_quote == 0 && !(is_escaped(str, j)))
		{	
			*k = j;
			while (++j < i)
			{
				if (check_char(str[j]))
					break ;
			}
			break ;
		}
		j++;
	}
	return (j);
}
