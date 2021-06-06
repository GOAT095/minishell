/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 14:33:12 by hchorfi           #+#    #+#             */
/*   Updated: 2021/05/06 14:33:14 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_builtin(t_command *command)
{
	if (!command->tokens[0])
		return (0);
	else if (!ft_strncmp(command->tokens[0], "export", 7))
		return (1);
	else if (!ft_strncmp(command->tokens[0], "env", 4))
		return (1);
	else if (!ft_strncmp(command->tokens[0], "unset", 6))
		return (1);
	else if (!ft_strncmp(command->tokens[0], "pwd", 4))
		return (1);
	else if (!ft_strncmp(command->tokens[0], "cd", 3))
		return (1);
	else if (!ft_strncmp(command->tokens[0], "echo", 5))
		return (1);
	else if (!ft_strncmp(command->tokens[0], "exit", 5))
		return (1);
	else
		return (0);
}

int	ft_exec_builtin(t_command *command)
{
	if (!ft_strncmp(command->tokens[0], "export", 7))
		ft_export(command);
	else if (!ft_strncmp(command->tokens[0], "env", 4))
		ft_env(command);
	else if (!ft_strncmp(command->tokens[0], "unset", 6))
		return (ft_unset(command));
	else if (!ft_strncmp(command->tokens[0], "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(command->tokens[0], "cd", 3))
		ft_cd(command);
	else if (!ft_strncmp(command->tokens[0], "echo", 5))
		return (ft_echo(command, 1, 0));
	else if (!ft_strncmp(command->tokens[0], "exit", 5))
		ft_exit(command, 0);
	return (0);
}

void	ft_builtin(t_command *command)
{
	int	std_out;
	int	std_in;

	std_out = dup(1);
	std_in = dup(0);
	if (command->input_file > 0)
	{
		dup2(command->input_file, 0);
		close(command->input_file);
	}
	else
		dup2(g_data.fdd, 0);
	if (command->pipe_pos != g_data.num_pipes && g_data.num_pipes > 0)
		dup2(g_data.fd[1], 1);
	if (command->output_file != 1)
	{
		dup2(command->output_file, 1);
		close(command->output_file);
	}
	ft_exec_builtin(command);
	dup2(std_out, 1);
	dup2(std_in, 0);
	close(std_out);
	close(std_in);
}
