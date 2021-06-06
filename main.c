/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 22:39:14 by devza             #+#    #+#             */
/*   Updated: 2021/05/22 10:51:50 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parse(char *line, int j, int i)
{
	char	**cmds;
	char	**pipe_cmds;
	int		*npipe;

	cmds = ft_split_pars(line, ';');
	while (cmds[i])
	{
		pipe_cmds = ft_split_pars(cmds[i], '|');
		j = 0;
		while (pipe_cmds[j])
		{
			ft_parse2(i, j, pipe_cmds[j]);
			j++;
		}
		ft_free_d_p(pipe_cmds);
		npipe = malloc(sizeof(int));
		*npipe = j - 1;
		if (g_data.n_pipe_cmd == NULL)
			g_data.n_pipe_cmd = ft_lstnew(npipe);
		else
			ft_lstadd_back(&g_data.n_pipe_cmd, ft_lstnew(npipe));
		i++;
	}
	ft_free_d_p(cmds);
}

int	ft_prompt(int argc, char **argv)
{
	if (argc >= 2)
	{
		g_data.line = argv[2];
		if (!ft_check_syntax(g_data.line))
			ft_parse(g_data.line, 0, 0);
	}
	else
	{
		ft_putstrs_fd("\033[0;32m", "minishell 👽 > ", "\033[0m", NULL);
		get_line();
	}
	if (argc < 2)
		free(g_data.line);
	return (0);
}

void	sighandler(int dummy)
{
	if (dummy == SIGINT)
	{
		g_data.line[0] = '\0';
		*(char *)(ft_lstlast(g_data.history)->content) = '\0';
		if (g_data.n_fork == 0)
			ft_putstrs_fd("\n", "\033[0;32m", "minishell 👽 > ", "\033[0m");
		else
			ft_putstr_fd("\n", 1);
		g_data.ret = 1;
	}
	else if (dummy == SIGQUIT)
	{
		if (g_data.n_fork > 0)
			ft_putstr_fd("Quit: 3\n", 1);
	}
}

void	ft_exec(t_command *command)
{
	int	*tmp;
	//ft_putstr_fd(command->tokens[0], 1);
	ft_prepare_tokens(command, 0, 0);
	if (command->pipe_pos != g_data.num_pipes && g_data.num_pipes > 0)
	{
		//ft_putstr_fd("pipe\n", 1);
		//ft_putnbr_fd(command->pipe_pos, 1);
		pipe(g_data.fd);
	}
	if (ft_check_builtin(command))
		ft_builtin(command);
	else if (command->tokens[0] != NULL && command->tokens[0][0] != '\0')
		ft_bin(command);
	if (g_data.num_pipes > 0)
	{
		close(g_data.fd[1]);
		g_data.fdd = g_data.fd[0];
		tmp = malloc(sizeof(int));
		*tmp = g_data.fdd;
		ft_lstadd_back(&g_data.fd_close, ft_lstnew(tmp));
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_list		*newlist;
	t_list		*pipe_list;
	t_command	*command;
	int			j;

	ft_stock_envp(envp);
	while (1)
	{
		init1(argv, &newlist, &pipe_list, &j);
		while (pipe_list)
		{
			init2(pipe_list->content);
			while (newlist && (((t_command *)newlist->content)->block == j))
			{
				command = (t_command *)newlist->content;
				//ft_putstr_fd(((t_command *)newlist->content)->tokens[0], 1);
				//ft_putnbr_fd(command->check_pos, 1);
				//ft_putstr_fd("\n", 1);
				int k;
				if ((k = check_input(newlist, j)) > -1)
				{
					//ft_putstr_fd("ok\n", 1);
					int i = 0;
					while (i <= k)
					{
						newlist = newlist->next;
						i++;
					}
					//((t_command *)newlist->content)->pipe_pos = 
				}
				else
				{
					//ft_putstr_fd(((t_command *)newlist->content)->tokens[0], 1);
					//ft_putnbr_fd(command->pipe_pos, 1);
					ft_exec(command);
					newlist = newlist->next;
				}
				
				//if (check_input(g_data.cmds, j) != -1)
			}
			ft_close_and_ret(&j, &pipe_list);
			ft_stock_ret();
		}
		ft_free_list();
	}
	return (0);
}
