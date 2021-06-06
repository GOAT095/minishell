/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anassif <anassif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 17:34:22 by anassif           #+#    #+#             */
/*   Updated: 2021/02/16 17:34:22 by anassif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_n(char *args)
{
	int	i;

	i = 0;
	if (args[0] == '-' && args[1] != 'n')
		return (0);
	if (args[0] == '-')
		i++;
	else
		return (0);
	while (args[i])
	{
		if (args[i] == 'n')
			i++;
		else if (args[i] != '\0')
			return (0);
	}
	return (1);
}

int	ft_echo(t_command *command, int i, int n)
{
	if (!command->tokens[1])
	{
		write(1, "\n", 1);
		return (0);
	}
	while (command->tokens[i])
	{
		if (!(check_n(command->tokens[i])))
			break ;
		n = 1;
		i++;
	}
	while (command->tokens[i])
	{
		ft_putstr_fd(command->tokens[i], 1);
		if (command->tokens[i + 1] && command->tokens[i][0] != '\0')
			ft_putchar_fd(' ', 1);
		if (!command->tokens[i + 1] && n == 0)
			ft_putchar_fd('\n', 1);
		i++;
	}
	return (g_data.ret = 0);
}