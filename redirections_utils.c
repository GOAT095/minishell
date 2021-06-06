/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 14:34:17 by hchorfi           #+#    #+#             */
/*   Updated: 2021/05/22 11:01:37 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_in2(char *tmp_in)
{
	int		j;
	int		cot;

	j = 0;
	if (tmp_in[j] == '\"' || tmp_in[j] == '\'')
	{
		cot = j++;
		while (tmp_in[j] != tmp_in[cot] && tmp_in[j] != '\0')
			j++;
	}
	else
	{
		while (tmp_in[j] != ' ' && tmp_in[j] != '\0')
			j++;
	}
	return (j);
}

int	ft_check_out(char **tmp_out)
{
	int		j;
	int		cot;

	j = 0;
	if ((*tmp_out)[0] == '>')
	{
		(*tmp_out)++;
		while ((*tmp_out)[j] == ' ' && (*tmp_out)[j] != '\0')
			j++;
		g_data.append = 1;
	}
	if (((*tmp_out)[j] == '\"' || (*tmp_out)[j] == '\''))
	{
		cot = j++;
		while ((*tmp_out)[j] != (*tmp_out)[cot] && (*tmp_out)[j] != '\0')
		{
			j++;
		}
	}
	else
	{
		while ((*tmp_out)[j] != ' ' && (*tmp_out)[j] != '\0')
			j++;
	}
	return (j);
}

void	ft_close_get_out(int out)
{
	if (g_data.command->output_file > 1)
		close(g_data.command->output_file);
	g_data.command->output_file = out;
}

void	ft_out_red_file2(char *file, char c, int out, int priority)
{
	struct stat	path_stat;
	char		*tmp_free;

	if (c != '\'')
	{
		tmp_free = file;
		file = get_other_variables(file);
		if (*file == '\0')
		{
			ft_putstrs_er("minishell: ", tmp_free, ": ambiguous redirect\n", NULL);
			g_data.ret = 1;
		}
		free(tmp_free);
	}
	tmp_free = file;
	file = remove_all_quotes(file);
	free(tmp_free);
	if (g_data.append == 0)
	{
		priority = 1;
		out = open(file, O_RDWR | O_CREAT | O_TRUNC, 0777);
		free(file);
	}
	else
	{
		if (priority == 0 || stat(file, &path_stat))
			out = open(file, O_RDWR | O_CREAT | O_APPEND, 0777);
		free(file);
	}
	ft_close_get_out(out);
}
