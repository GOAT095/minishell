/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:05:25 by hchorfi           #+#    #+#             */
/*   Updated: 2021/05/21 21:30:45 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_check2(char **tokens, struct stat ps)
{
	char	**envp;

	envp = ft_get_envp();
	if (ps.st_mode & S_IFDIR)
	{
		if (tokens[0][0] != '.' && tokens[0][0] != '/'
			&& tokens[0][ft_strlen(tokens[0]) - 1] != '/')
		{
			ft_exec_error(1, tokens[0]);
		}
		else
			ft_exec_error(2, tokens[0]);
	}
	if (tokens[0][0] == '.' || tokens[0][0] == '/')
	{
		execve(tokens[0], tokens, envp);
		if (errno == 13)
			ft_exec_error(3, tokens[0]);
		exit (0);
	}
}

void	ft_exec_check1(char **token, struct stat path_stat)
{
	if (!ft_strncmp(token[0], "..", 3))
	{
		ft_exec_error(1, token[0]);
	}
	if (!ft_strncmp(token[0], ".", 2))
	{
		ft_putstr_fd("minishell: .: filename argument required\n", 2);
		ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
		exit(2);
	}
	ft_exec_check2(token, path_stat);
}

void	ft_exec_bin2(char **bins, char *path, struct stat ps, char **token)
{
	char	*file;
	int		i;
	char	**envp;

	envp = ft_get_envp();
	i = 0;
	while (bins[i])
	{
		path = ft_strjoin(bins[i], "/");
		file = ft_strjoin(path, token[0]);
		if (!stat(file, &ps))
		{
			execve(file, token, envp);
			ft_putstr_fd("minishell: ", 2);
			ft_putstrs_er(token[0], ": ", strerror(errno), "\n");
			exit(126);
		}
		i++;
	}
}

int	ft_exec_bin(t_command *command)
{
	char		**bins;
	char		*path;
	struct stat	path_stat;

	if (!stat(command->tokens[0], &path_stat))
		ft_exec_check1(command->tokens, path_stat);
	//else
	//{
		if (command->tokens[0][0] == '/' || (ft_strlen(command->tokens[0]) > 2
			&& command->tokens[0][0] == '.' && command->tokens[0][1] == '/'))
			ft_exec_error(4, command->tokens[0]);
		path = ft_get_path();
		if (!path)
			ft_exec_error(4, command->tokens[0]);
		bins = ft_split(path, ':', 0);
		if (!path || *path == '\0' || !bins)
			ft_exec_error(4, command->tokens[0]);
		ft_exec_bin2(bins, path, path_stat, command->tokens);
	//}
	return (0);
}

void	ft_bin(t_command *command)
{
	int	std_out;
	int	std_in;

	g_data.n_fork++;
	if (!fork())
	{
		std_out = dup(1);
		std_in = dup(0);
		ft_dup_in_out(0, command->input_file, command->output_file);
		if (g_data.num_pipes > 0)
		{
			if (command->pipe_pos != g_data.num_pipes)
				dup2(g_data.fd[1], 1);
			close(g_data.fd[0]);
			close(g_data.fd[1]);
		}
		ft_dup_in_out(1, command->input_file, command->output_file);
		ft_exec_bin(command);
		dup2(std_out, 1);
		dup2(std_in, 0);
		close(std_out);
		close(std_in);
		ft_exec_error(1, command->tokens[0]);
		exit(g_data.ret = 127);
	}
}
