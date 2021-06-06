/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 14:35:37 by hchorfi           #+#    #+#             */
/*   Updated: 2021/05/21 12:40:34 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstrs_fd(char *s1, char *s2, char *s3, char *s4)
{
	if (s1 != NULL)
		ft_putstr_fd(s1, 1);
	if (s2 != NULL)
		ft_putstr_fd(s2, 1);
	if (s3 != NULL)
		ft_putstr_fd(s3, 1);
	if (s4 != NULL)
		ft_putstr_fd(s4, 1);
}

void	ft_putstrs_er(char *s1, char *s2, char *s3, char *s4)
{
	if (s1 != NULL)
		ft_putstr_fd(s1, 2);
	if (s2 != NULL)
		ft_putstr_fd(s2, 2);
	if (s3 != NULL)
		ft_putstr_fd(s3, 2);
	if (s4 != NULL)
		ft_putstr_fd(s4, 2);
}

int	ft_check_syntax_last(char *line)
{
	int	len;

	if (line)
		len = ft_strlen(line) - 1;
	while (line[len] == ' ')
		len--;
	if (line[len] == '|' || line[len] == '>' || line[len] == '<')
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (0);
	}
	return (1);
}

int	ft_check_syntax2(char *line)
{
	if ((*line == ';') || remove_tabs_check(line, ';'))
	{
		printf("minishell: syntax error near unexpected token `;'\n");
		return (0);
	}
	if (remove_tabs_check(line, '<'))
	{
		printf("minishell: syntax error near unexpected token `<'\n");
		return (0);
	}
	return (1);
}

int	ft_check_syntax(char *line)
{
	while (line && *line == ' ')
		line++;
	if (*line == '|' || *line == ';')
	{
		printf("minishell: syntax error near unexpected token `%c'\n", *line);
		return (g_data.ret = 258);
	}
	if ((*line == '|') || remove_tabs_check(line, '|'))
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (g_data.ret = 258);
	}
	if (!ft_check_syntax2(line))
		return (g_data.ret = 258);
	if (!ft_check_syntax_last(line))
		return (g_data.ret = 258);
	return (0);
}
