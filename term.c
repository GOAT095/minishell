/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 13:38:11 by hchorfi           #+#    #+#             */
/*   Updated: 2021/05/03 13:38:12 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_term(void)
{
	tcgetattr(STDIN_FILENO, &g_data.orig_term);
	tcgetattr(STDIN_FILENO, &g_data.term);
	g_data.term.c_lflag &= ~ICANON;
	g_data.term.c_lflag &= ~ECHO;
	g_data.term.c_cc[VMIN] = 1;
	g_data.term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &g_data.term);
	tgetent(NULL, "xterm");
}

void	ft_get_char(int c, int *col)
{
	char	*tmp_free;
	char	*charater;

	g_data.press = 0;
	if (c != '\n' && ft_isprint(c))
	{
		write(0, &c, 1);
		if (*col == tgetnum("co"))
		{	
			write(1, tgetstr("do", NULL), ft_strlen(tgetstr("do", NULL)));
			*col = 1;
		}
		else
			(*col)++;
		charater = malloc(sizeof(char) * 2);
		charater[0] = (char)c;
		charater[1] = '\0';
		tmp_free = g_data.line;
		g_data.line = ft_strjoin(g_data.line, charater);
		free(tmp_free);
		free(charater);
	}
}

void	ft_init_get_line(int *col)
{
	g_data.line = ft_strdup("");
	g_data.term_list = ft_lstlast(g_data.history);
	g_data.press = 0;
	if (!ft_lstsize(g_data.history))
	{
		g_data.history = ft_lstnew(ft_strdup(""));
		g_data.history->prev = NULL;
	}
	*col = 16;
	ft_init_term();
}

int	get_line(void)
{
	int	c;
	int	col;

	c = 0;
	ft_init_get_line(&col);
	while (read(0, &c, sizeof(c)) > 0)
	{
		if (c == DOWN_ARROW || c == UP_ARROW)
			ft_up_down(c, &col);
		else if (c == BACKSPACE)
			delete_end(&col);
		else if (c == CTRLD)
			ft_ctrld();
		else if (c == NEW_LINE)
		{
			ft_new_line();
			break ;
		}
		else
			ft_get_char(c, &col);
		c = 0;
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &g_data.orig_term);
	return (0);
}
