/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 13:36:32 by hchorfi           #+#    #+#             */
/*   Updated: 2021/05/03 13:37:48 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_up_down(int c, int *col)
{
	if (c == DOWN_ARROW)
	{
		down_key();
		if (ft_strlen(g_data.line))
			*col = ft_strlen(g_data.line) + 16;
		else
			*col = 16;
	}
	else if (c == UP_ARROW)
	{
		up_key();
		if (ft_strlen(g_data.line))
			*col = ft_strlen(g_data.line) + 16;
		else
			*col = 16;
	}
}

void	ft_add_line_to_his(void)
{
	t_list	*prev;
	t_list	*tail;
	t_list	*newlist;

	if (ft_lstsize(g_data.history) == 1)
	{
		ft_lstadd_front(&g_data.history, ft_lstnew(ft_strdup(g_data.line)));
		g_data.history->prev = NULL;
		ft_lstlast(g_data.history)->prev = g_data.history;
	}
	else if (ft_lstsize(g_data.history) > 1)
	{
		tail = ft_lstlast(g_data.history);
		prev = ft_lstlast(g_data.history)->prev;
		newlist = ft_lstnew(ft_strdup(g_data.line));
		newlist->next = prev->next;
		prev->next = newlist;
		newlist->prev = prev;
		newlist->next->prev = newlist;
	}
}
