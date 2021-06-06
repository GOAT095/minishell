/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:14:39 by anassif           #+#    #+#             */
/*   Updated: 2021/05/06 13:56:47 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_other_variables(char *str)
{	
	int		i;
	int		dollar;
	char	*tmp_free;

	dollar = get_other_var2(str, 0, 0, 0);
	i = 0;
	while (i < dollar)
	{
		str = ft_get_variables(str, 0, ft_strlen(str));
		i++;
	}
	if (!str || *str == '\0')
		return (str);
	else
	{	
		tmp_free = str;
		str = ft_strtrim(str, " ");
		if (i > 0)
			free(tmp_free);
		return (str);
	}
}

char	*ft_remove_slashes(char *str, int start, int end)
{
	int		len;
	char	*back;

	len = ft_remove_slashes3(start, str, end);
	back = malloc(sizeof(char) * (len + 1));
	ft_remove_slashes4(str, &back, end, start);
	return (back);
}

char	*remove_all_quotes(char *str)
{
	int		start;
	int		i;
	char	*s;

	g_data.sq = 0;
	g_data.dq = 0;
	i = 0;
	start = 0;
	g_data.ptr = ft_strdup("");
	while (str[i])
	{
		ft_remove_all1(str, &i, &start);
		ft_remove_all2(str, &i, &start);
		if (str[i] != '\0')
			i++;
		if (str[i] == '\0')
		{
			s = ft_remove_slashes(str, start, i);
			g_data.ptr = ft_stock(g_data.ptr, s, ft_strlen(s));
			free(s);
			break ;
		}
	}
	return (g_data.ptr);
}

char	**split_parse2(char *s, char **str, char c, int splited)
{
	char	*tmp_free;
	int		i;
	int		j;
	int		d;

	init_3params(&i, &j, &d);
	while (2)
	{
		if (((s[i] == c && i != 0) || (s[i] == '\0' && i > 0))
			&& chec_before(s, i, c) && !is_escaped(s, i))
		{
			tmp_free = ft_substr(s, d, i - d);
			if (check_cots(tmp_free, 0, 0))
			{
				str[j++] = ft_substr(s, d, i - d);
				splited = 1;
			}
			free(tmp_free);
		}
		d = my_ternary(&splited, i, d);
		if (s[i++] == '\0')
			break ;
	}
	str[j] = NULL;
	return (str);
}

char	**ft_split_pars(char *s, char c)
{
	char	**str;
	int		j;

	if (s != NULL)
		s = ft_strtrim(s, " ");
	str = (char **)malloc(sizeof(char *) * (countt(s, c) + 1));
	str = split_parse2(s, str, c, 0);
	if (s)
		free (s);
	return (str);
}
