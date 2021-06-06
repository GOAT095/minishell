/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 15:13:16 by hchorfi           #+#    #+#             */
/*   Updated: 2021/05/04 15:05:38 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_del_list(t_list **head, int position, t_list *curr, t_list *prev)
{
	curr = *head;
	prev = *head;
	if (*head == NULL)
		return (0);
	else if (position == 1)
	{
		*head = curr->next;
		free(curr->content);
		free(curr);
		curr = NULL;
	}
	else
	{
		while (position != 1)
		{
			prev = curr;
			curr = curr->next;
			position--;
		}
		prev->next = curr->next;
		free(curr->content);
		free(curr);
		curr = NULL;
	}
	return (0);
}

int	ft_chr_var(char *unset_var)
{
	t_list	*newlist;
	char	*old_var;
	int		i;

	newlist = g_data.env_var;
	i = 1;
	while (newlist)
	{
		old_var = ft_get_oldvar(newlist->content);
		if (ft_strcmp(old_var, unset_var) == 0)
		{
			ft_free_exist(old_var, newlist->content, '=');
			ft_del_list(&g_data.env_var, i, NULL, NULL);
			return (1);
		}
		ft_free_exist(old_var, newlist->content, '=');
		newlist = newlist->next;
		i++;
	}
	return (0);
}

int	ft_unset(t_command *command)
{
	int		i;
	char	*exp_var;

	i = 1;
	g_data.ret = 0;
	while (command->tokens[i])
	{
		exp_var = ft_get_export_var(command->tokens[i]);
		if (exp_var[0] != '#'
			&& !(ft_valid_export_var(
					command, exp_var, command->tokens[i], "unset")))
			ft_chr_var(command->tokens[i]);
		i++;
	}
	return (0);
}
