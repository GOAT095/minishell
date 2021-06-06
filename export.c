/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:35:17 by hchorfi           #+#    #+#             */
/*   Updated: 2021/05/04 22:43:44 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exist_var(char *export_var, char *token, int j, t_list *newlist)
{
	char	*old_var;
	int		tmp_len;

	if (ft_strchr(token, '+'))
	{
		tmp_len = ft_strlen(export_var);
		export_var = ft_substr(export_var, 0, tmp_len - 1);
	}
	while (newlist)
	{
		old_var = ft_get_oldvar(newlist->content);
		if (!(ft_strcmp(old_var, export_var)))
		{
			if (can_change(newlist->content, token, old_var, export_var) == 1)
				return (1);
			ft_change(j - 1, token, old_var, g_data.env_var);
			ft_free_exist(export_var, token, '+');
			return (1);
		}
		ft_free_exist(old_var, newlist->content, '=');
		newlist = newlist->next;
		j++;
	}
	ft_free_exist(export_var, token, '+');
	return (0);
}

void	ft_print_export(t_list *newlist)
{
	char	*str_chr;
	char	*tmp_str;

	ft_sort_export();
	while (newlist)
	{
		tmp_str = newlist->content;
		if ((tmp_str[0] == '_' && tmp_str[1] == '=') || tmp_str[0] == '?')
		{
			newlist = newlist->next;
			continue ;
		}
		ft_putstr_fd("declare -x ", 1);
		str_chr = ft_strchr(newlist->content, '=');
		if (str_chr)
			ft_print_export2(newlist->content, str_chr, NULL);
		else
		{
			ft_putstr_fd(newlist->content, 1);
			ft_putstr_fd("\n", 1);
		}
		newlist = newlist->next;
	}
}

void	ft_add_to_ex_list(char *token)
{
	char	*tmp_free;
	char	*tmp_str;

	tmp_str = ft_strchr(token, '+');
	if (tmp_str != 0)
	{
		tmp_free = ft_substr(token, 0, ft_strlen(token) - ft_strlen(tmp_str));
		ft_lstadd_back(&g_data.env_var, ft_lstnew(
				ft_strjoin(tmp_free, tmp_str + 1)));
		free(tmp_free);
	}
	else
		ft_lstadd_back(&g_data.env_var, ft_lstnew(ft_strdup(token)));
}

int	ft_export(t_command *cmd)
{
	int		i;
	char	*exp_var;

	i = 1;
	g_data.ret = 0;
	if (cmd->n_tokens == 1
		|| (cmd->n_tokens == 2 && cmd->tokens[1][0] == '#'))
		ft_print_export(g_data.env_var);
	else
	{
		while (cmd->tokens[i])
		{
			exp_var = ft_get_export_var(cmd->tokens[i]);
			if (exp_var[0] != '#'
				&& !(ft_valid_export_var(
						cmd, exp_var, cmd->tokens[i], "export"))
				&& !ft_exist_var(exp_var, cmd->tokens[i], 0, g_data.env_var))
				ft_add_to_ex_list(cmd->tokens[i]);
			if (ft_strchr(cmd->tokens[i], '='))
				free(exp_var);
			i++;
		}
	}
	return (0);
}
