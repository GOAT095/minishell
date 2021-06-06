/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 14:35:22 by hchorfi           #+#    #+#             */
/*   Updated: 2021/05/06 14:35:24 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_close_fd(void)
{
	t_list	*tmp_list;

	while (g_data.fd_close)
	{
		tmp_list = g_data.fd_close;
		close(*(int *)(g_data.fd_close)->content);
		free(g_data.fd_close->content);
		g_data.fd_close = g_data.fd_close->next;
		free(tmp_list);
	}
}

void	ft_free_list(void)
{
	t_list	*tmp_list;

	while (g_data.cmds)
	{
		tmp_list = g_data.cmds;
		ft_free_d_p(((t_command *)g_data.cmds->content)->tokens);
		if (((t_command *)g_data.cmds->content)->input_file > 0)
			close(((t_command *)g_data.cmds->content)->input_file);
		if (((t_command *)g_data.cmds->content)->output_file > 1)
			close(((t_command *)g_data.cmds->content)->output_file);
		free(g_data.cmds->content);
		g_data.cmds = g_data.cmds->next;
		free(tmp_list);
	}
	while (g_data.n_pipe_cmd)
	{
		tmp_list = g_data.n_pipe_cmd;
		free(g_data.n_pipe_cmd->content);
		g_data.n_pipe_cmd = g_data.n_pipe_cmd->next;
		free(tmp_list);
	}
}

void	ft_free_d_p(char **str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	while (len >= 0)
	{
		free(str[len]);
		len--;
	}
	free(str);
}

int	ft_strchr_set(char *str, char *set, char *token)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (set[j] != '\0')
		{
			if (str[i] == set[j])
			{
				if (str[i] == '+' && token[i + 1] != '\0'
					&& token[i + 1] == '=')
				{
					j++;
					continue ;
				}
				else
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
