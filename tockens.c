/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tockens.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 14:35:03 by hchorfi           #+#    #+#             */
/*   Updated: 2021/05/06 14:35:05 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_new_tokens(t_command *command, int len, int k, char **tmp_double2)
{
	char	**tmp_double;
	char	**new_tokens;
	char	*tmp_free;
	int		count;

	new_tokens = malloc(sizeof(char *) * (len + 1));
	len = 0;
	while (command->tokens[k])
	{
		count = 0;
		tmp_double = ft_split_pars(command->tokens[k], ' ');
		while (tmp_double[count])
		{
			tmp_free = ft_strtrim(tmp_double[count], " ");
			new_tokens[len + count] = ft_strdup(tmp_free);
			free(tmp_free);
			count++;
		}
		len += count;
		ft_free_d_p(tmp_double);
		k++;
	}
	new_tokens[len] = NULL;
	command->tokens = new_tokens;
	ft_free_d_p(tmp_double2);
}

void	ft_prepare_tokens(t_command *command, int k, int len)
{
	char	*tmp_free;
	char	**tmp_double;
	int		count;

	while (command->tokens[k])
	{
		count = 0;
		tmp_free = command->tokens[k];
		command->tokens[k] = get_other_variables(command->tokens[k]);
		free(tmp_free);
		tmp_double = ft_split_pars(command->tokens[k], ' ');
		while (tmp_double[count])
			count++;
		len += count;
		ft_free_d_p(tmp_double);
		tmp_free = command->tokens[k];
		command->tokens[k] = remove_all_quotes(command->tokens[k]);
		free(tmp_free);
		k++;
	}
	if (len > k)
		ft_new_tokens(command, len, 0, command->tokens);
}
