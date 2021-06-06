/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 14:57:37 by hchorfi           #+#    #+#             */
/*   Updated: 2021/05/21 20:37:04 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init2(int *num_pipe)
{
	g_data.num_pipes = *num_pipe;
	g_data.fdd = 0;
	g_data.n_fork = 0;
	g_data.fd[0] = 0;
	g_data.fd[1] = 1;
}

void	ft_close_and_ret(int *j, t_list **pipe_list)
{
	ft_close_fd();
	while (g_data.n_fork > 0)
	{
		wait(&g_data.ret);
		if (WIFSIGNALED(g_data.ret))
			g_data.ret = WTERMSIG(g_data.ret) + 128;
		if (WIFEXITED(g_data.ret))
			g_data.ret = WEXITSTATUS(g_data.ret);
		g_data.n_fork--;
	}
	*pipe_list = (*pipe_list)->next;
	(*j)++;
}

void	init1(char **argv, t_list **newlist, t_list **pipe_list, int *j)
{
	int	argc;

	argc = 0;
	signal(SIGQUIT, sighandler);
	signal(SIGINT, sighandler);
	*j = ft_prompt(argc, argv);
	*newlist = g_data.cmds;
	*pipe_list = g_data.n_pipe_cmd;
}

int	check_input(t_list *newlist, int j)
{
	int i ;

	i = -1;
	while (newlist && (((t_command *)newlist->content)->block == j))
	{
		if (((t_command *)newlist->content)->check_pos > -1)
		{
			g_data.ret = 1;
			i = ((t_command *)newlist->content)->check_pos;
			//return (-1);
		}
		newlist = newlist->next;
		if (newlist && (((t_command *)newlist->content)->block == j))
		{
			((t_command *)newlist->content)->pipe_pos = ((t_command *)newlist->content)->pipe_pos - (i + 1);
			g_data.num_pipes = ((t_command *)newlist->content)->pipe_pos;
		}
	}
	return (i);
}

void	ft_parse2(int i, int j, char *pipe_cmd)
{
	char	*new_pipe;
	char	*tmp_free;
	int		k;

	g_data.command = malloc(sizeof * g_data.command);
	g_data.command->block = i;
	g_data.command->pipe_pos = j;
	g_data.command->check_pos = -1;
	new_pipe = ft_check_redirections(pipe_cmd, 0, ft_strdup(""));
	g_data.command->tokens = ft_split_pars(new_pipe, ' ');
	free(new_pipe);
	k = 0;
	while (g_data.command->tokens[k])
	{
		tmp_free = g_data.command->tokens[k];
		g_data.command->tokens[k] = ft_strtrim(g_data.command->tokens[k], " ");
		free(tmp_free);
		k++;
	}
	g_data.command->n_tokens = k;
	if (g_data.cmds == NULL)
		g_data.cmds = ft_lstnew(g_data.command);
	else
		ft_lstadd_back(&g_data.cmds, ft_lstnew(g_data.command));
}
