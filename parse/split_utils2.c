/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 13:09:25 by hchorfi           #+#    #+#             */
/*   Updated: 2021/05/06 13:27:48 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_char(char c)
{
	if (c == ' ' || c == '"' || c == '\'' || c == '/' || c == '$' || c == ':'
		|| c == '=' || c == '|' || c == ',' || c == '\\' || c == '\''
		|| c == '"' || c == '[' || c == ']' || c == '@')
		return (1);
	return (0);
}

int	check_cots(char *s, int d_quote, int s_quote)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' && s_quote == 0 && d_quote == 0 && !(is_escaped(s, i)))
		{
			s_quote = 1;
			i++;
		}
		if (s[i] == '\'' && s_quote == 1)
			s_quote = 0;
		if (s[i] == '"' && d_quote == 0 && s_quote == 0 && !(is_escaped(s, i)))
		{
			d_quote = 1;
			i++;
		}
		if (s[i] == '"' && d_quote == 1 && s[i] != '\0' && !(is_escaped(s, i)))
			d_quote = 0;
		if (s[i] != '\0')
			i++;
	}
	if (s_quote == 0 && d_quote == 0)
		return (1);
	return (0);
}

int	remove_tabs_check(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c && s[i - 1] != '\\')
		{
			i++;
			while (s[i] == '\t' || s[i] == ' ')
				i++;
			if (s[i] == c)
				return (1);
		}
		if (s[i] != '\0')
			i++;
	}
	return (0);
}

char	*ft_stock(char *line, char *buff, int i)
{
	char	*newline;
	int		len;
	int		j;

	j = 0;
	len = 0;
	if (line)
		len = ft_strlen(line);
	newline = (char *)malloc(len + i + 1);
	while (j < len)
	{
		newline[j] = line[j];
		j++;
	}
	if (line)
		free(line);
	while (j < len + i)
	{
		newline[j] = buff[j - len];
		j++;
	}
	newline[j] = '\0';
	return (newline);
}

char	*ft_put_variable(char *str, int k, int j)
{
	char	*var;
	int		i;

	i = 0;
	k++;
	var = (char *)malloc(j - k + 2);
	while (i <= j - k)
	{
		var[i] = str[k + i];
		i++;
	}
	var[i] = '\0';
	return (var);
}
