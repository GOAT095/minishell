/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 13:20:03 by hchorfi           #+#    #+#             */
/*   Updated: 2021/05/06 13:22:28 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_other_var2(char *str, int i, int d_quote, int s_quote)
{
	int	dollar;

	dollar = 0;
	while (str[i])
	{
		if (str[i] == '\"' && !(is_escaped(str, i++)))
		{
			if (d_quote == 0)
				d_quote = 1;
			else
				d_quote = 0;
		}
		if (str[i] == '\'' && !(is_escaped((char *)str, i)) && d_quote == 0)
		{
			if (s_quote == 0)
				s_quote = 1;
			else
				s_quote = 0;
		}
		if (str[i] == '$' && s_quote == 0 && !(is_escaped(str, i)))
			dollar++;
		if (str[i] != '\0')
			i++;
	}
	return (dollar);
}

void	fill_with(char *s, int start, int len, char c)
{
	int	i;

	i = 0;
	while (i < len)
	{
		s[start + i] = c;
		i++;
	}
}

char	*ft_variable_value(char *var)
{
	t_list	*newlist;
	char	*old_var;
	char	*tmp_str;
	int		tmp_len;
	int		len;

	newlist = g_data.env_var;
	while (newlist)
	{
		old_var = ft_get_oldvar(newlist->content);
		if (ft_strcmp(old_var, var) == 0)
		{
			if (ft_strchr(newlist->content, '='))
			{
				free(old_var);
				return (ft_strchr(newlist->content, '=') + 1);
			}
		}
		ft_free_exist(old_var, newlist->content, '=');
		newlist = newlist->next;
	}
	return ("");
}

char	*ft_check_dollar_slash(char	*s, int i, int c)
{
	char	*value;

	value = (char *)malloc(ft_strlen(s) + ft_ch_do(0, 0, s) + 1);
	while (s[i])
	{
		if (s[i] == '\\')
		{
			value[c] = '\\';
			c++;
			value[c] = '\\';
			c++;
			i++;
		}
		else
		{
			value[c] = s[i];
			if (s[i] != '\0')
			{
				i++;
				c++;
			}
		}	
	}
	value[c] = '\0';
	return (value);
}

char	*ft_get_variables(char *str, int start, int i)
{
	char	*var;
	int		j;
	int		k;
	char	*value;

	k = 0;
	j = ft_get_var2(start, str, &k, i) - 1;
	if (k == j)
	{
		str = ft_replace_variable(str, "$", k, j);
		return (str);
	}
	var = ft_put_variable(str, k, j);
	value = ft_variable_value(var);
	free(var);
	value = ft_check_dollar_slash(value, 0, 0);
	str = ft_replace_variable(str, value, k, j);
	free(value);
	return (str);
}
