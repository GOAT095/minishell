/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 14:34:34 by hchorfi           #+#    #+#             */
/*   Updated: 2021/05/21 18:38:01 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_in_red_file(char **new_pipe, char **tmp_in, int j)
{
	char	*file;
	char	*tmp_free;
	int		in;

	file = ft_substr(*tmp_in, 0, j);
	tmp_free = file;
	file = get_other_variables(file);
	free(tmp_free);
	tmp_free = file;
	file = remove_all_quotes(file);
	free(tmp_free);
	in = open(file, O_RDONLY);
	if (in == -1)
	{
		ft_putstrs_er(
			"minishell: ", file, ": No such file or directory\n", NULL);
		g_data.command->check_pos = g_data.command->pipe_pos;
	}
	if (g_data.command->input_file > 0)
		close(g_data.command->input_file);
	g_data.command->input_file = in;
	tmp_free = *new_pipe;
	*new_pipe = ft_strjoin(*new_pipe, (*tmp_in) + j);
	free(tmp_free);
	free(*tmp_in);
	free(file);
}

char	*ft_check_in(char *pipe_cmds, char *new_pipe, char *tmp_free, int i)
{
	char	**str;
	char	*tmp_in;

	str = ft_split_pars(pipe_cmds, '<');
	new_pipe = ft_strdup("");
	while (str[i])
	{
		if (i == 0 && *str[0] != '<')
		{
			tmp_free = new_pipe;
			new_pipe = ft_strjoin(str[i++], "");
			free(tmp_free);
		}
		else
		{
			if (i == 0 && *str[0] == '<')
				tmp_in = ft_strtrim(str[i++] + 1, " ");
			else
				tmp_in = ft_strtrim(str[i++], " ");
			ft_in_red_file(&new_pipe, &tmp_in, ft_check_in2(tmp_in));
		}
	}
	ft_free_d_p(str);
	return (new_pipe);
}

void	ft_out_red_file(char *tmp_out, char **new_pipe)
{
	char		*file;
	char		*tmp_free;
	int			j;
	int			i;

	tmp_free = tmp_out;
	tmp_out = ft_strtrim(tmp_out, " ");
	j = ft_check_out(&tmp_out);
	i = 0;
	while (tmp_out[i] == '\'' || tmp_out[i] == '\"')
		i++;
	free(tmp_free);
	file = ft_substr(tmp_out, i, j);
	ft_out_red_file2(file, tmp_out[0], 0, 0);
	tmp_free = *new_pipe;
	*new_pipe = ft_strjoin(*new_pipe, tmp_out + j + i);
	free(tmp_free);
	if (g_data.append == 1)
		free(tmp_out - 1);
	else
		free(tmp_out);
}

void	ft_check_redirections2(char **new_pipe, int *i, char *str)
{
	char	*tmp_free;
	char	*tmp_in;

	tmp_in = ft_check_in(str, NULL, NULL, 0);
	tmp_free = *new_pipe;
	*new_pipe = ft_strjoin(tmp_in, "");
	free(tmp_free);
	free(tmp_in);
	(*i)++;
}

char	*ft_check_redirections(char *pipe_cmds, int i, char *new_pipe)
{
	char	**str;
	char	*tmp_in;

	g_data.command->output_file = 1;
	str = ft_split_pars(pipe_cmds, '>');
	while (str[i])
	{
		g_data.append = 0;
		if (i == 0 && *str[0] != '>')
			ft_check_redirections2(&new_pipe, &i, str[i]);
		else
		{
			if (i == 0 && *str[0] == '>')
				tmp_in = ft_check_in(str[i++] + 1, NULL, NULL, 0);
			else
				tmp_in = ft_check_in(str[i++], NULL, NULL, 0);
			ft_out_red_file(tmp_in, &new_pipe);
		}
	}
	ft_free_d_p(str);
	return (new_pipe);
}
