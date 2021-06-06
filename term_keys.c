/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 13:30:46 by hchorfi           #+#    #+#             */
/*   Updated: 2021/05/21 12:28:35 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_new_line(void)
{
	write(1, "\n", 1);
	g_data.press = 0;
	if (*(g_data.line) != 0)
	{
		ft_add_line_to_his();
		g_data.term_list = ft_lstlast(g_data.history);
	}
	if (*(g_data.line) != 0)
	{
		if (!ft_check_syntax(g_data.line))
		{
			ft_parse(g_data.line, 0, 0);
			ft_stock_ret();
		}
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &g_data.orig_term);
}

void	down_key(void)
{
	char	*tmp_free;

	if (g_data.term_list && g_data.term_list->next)
	{
		write(1, "\r", 1);
		ft_putstrs_fd("\033[0;32m", "minishell 👽 > ", "\033[0m", NULL);
		write(1, tgetstr("ce", NULL), strlen(tgetstr("ce", NULL)));
		g_data.term_list = g_data.term_list->next;
		tmp_free = g_data.line;
		g_data.line = ft_strdup(g_data.term_list->content);
		free(tmp_free);
		ft_putstr_fd(g_data.line, 1);
	}
}

void	up_key(void)
{
	char	*tmp_free;

	if (!g_data.press)
	{
		g_data.press = 1;
		tmp_free = ft_lstlast(g_data.history)->content;
		ft_lstlast(g_data.history)->content = ft_strdup(g_data.line);
		free(tmp_free);
	}
	if (g_data.term_list && g_data.term_list->prev)
	{
		write(1, "\r", 1);
		ft_putstrs_fd("\033[0;32m", "minishell 👽 > ", "\033[0m", NULL);
		write(1, tgetstr("ce", NULL), strlen(tgetstr("ce", NULL)));
		g_data.term_list = g_data.term_list->prev;
		tmp_free = g_data.line;
		g_data.line = ft_strdup(g_data.term_list->content);
		free(tmp_free);
		ft_putstr_fd(g_data.line, 1);
	}	
}

void	delete_end(int *col)
{
	g_data.press = 0;
	if (ft_strlen(g_data.line) > 0)
	{
		if (*col > tgetnum("co"))
			*col = *col % tgetnum("co");
		if (*col > 0)
			(*col)--;
		if (*col == 0)
		{
			write(1, tgetstr("le", NULL), ft_strlen(tgetstr("le", NULL)));
			write(1, tgetstr("ce", NULL), ft_strlen(tgetstr("ce", NULL)));
			write(1, tgetstr("up", NULL), ft_strlen(tgetstr("up", NULL)));
			while (*col < tgetnum("co"))
			{
				write(1, tgetstr("nd", NULL), ft_strlen(tgetstr("nd", NULL)));
				(*col)++;
			}
		}
		else
		{
			write(1, tgetstr("le", NULL), ft_strlen(tgetstr("le", NULL)));
			write(1, tgetstr("ce", NULL), ft_strlen(tgetstr("ce", NULL)));
		}
		g_data.line[ft_strlen(g_data.line) - 1] = '\0';
	}
}

void	ft_ctrld(void)
{
	if (g_data.line && ft_strlen(g_data.line) == 0)
	{
		ft_putstr_fd("exit\n", 2);
		exit(g_data.ret);
	}
}
