/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 18:55:47 by hchorfi           #+#    #+#             */
/*   Updated: 2021/05/21 14:20:55 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_just_numbers(char *str)
{
	int		i;
	int		flag;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] != '\0')
	{
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\r'
			|| str[i] == '\f')
			i++;
		if (str[i] != '\0' && !ft_isdigit(str[i]))
			return (0);
		if (str[i] != '\0' && str[i + 1] == '\r')
			return (0);
		if (str[i] != '\0')
			i++;
	}
	return (1);
}

int	ft_exit_error(int error, char *str)
{
	ft_putstr_fd("exit\n", 2);
	if (error == 0)
		exit (g_data.ret);
	else if (error == 1)
	{
		ft_putstrs_er("minishell: exit: ", str, NULL, NULL);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(g_data.ret = 255);
	}
	else if (error == 2)
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	else if (error == 3)
		exit(ft_atoi(str));
	return (0);
}

int	ft_exit(t_command *command, int i)
{
	if (command->n_tokens > 1)
	{
		i = 1;
		if (command->n_tokens > 2)
		{
			if (!ft_just_numbers(command->tokens[1]))
				ft_exit_error(1, command->tokens[1]);
			ft_exit_error(2, NULL);
		}
		else
		{
			if (!ft_strcmp(command->tokens[1], "-1"))
				exit(g_data.ret = 255);
			if (ft_atoi(command->tokens[1]) == -1
				&& !ft_strcmp(command->tokens[1], "-1"))
				ft_exit_error(1, command->tokens[1]);
			ft_exit_error(3, command->tokens[1]);
		}
	}
	else
		ft_exit_error(0, NULL);
	return (0);
}
