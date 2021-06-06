/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 17:51:27 by hchorfi           #+#    #+#             */
/*   Updated: 2021/05/21 15:10:46 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_change_oldpwd(char *val)
{
	char	*tmp;
	t_list	*newlist;
	char	*tmp_free;

	newlist = g_data.env_var;
	while (newlist)
	{
		tmp = ft_substr(newlist->content, 0, 7);
		if (!ft_strncmp(tmp, "OLDPWD=", 8))
		{	
			tmp_free = newlist->content;
			newlist->content = ft_strjoin("OLDPWD=", val);
			free(tmp_free);
			free(tmp);
			return (0);
		}
		else
			newlist = newlist->next;
		free(tmp);
	}
	ft_lstadd_back(&g_data.env_var, ft_lstnew(ft_strjoin("OLDPWD=", val)));
	return (0);
}

int	ft_change_pwd(char *val)
{
	char	*tmp;
	t_list	*newlist;
	char	*tmp_free;

	newlist = g_data.env_var;
	while (newlist)
	{
		tmp = ft_substr(newlist->content, 0, 4);
		if (!ft_strncmp(tmp, "PWD=", 5))
		{
			tmp_free = newlist->content;
			newlist->content = ft_strjoin("PWD=", val);
			free(tmp_free);
			free(tmp);
			return (0);
		}
		else
			newlist = newlist->next;
		free(tmp);
	}
	ft_lstadd_back(&g_data.env_var, ft_lstnew(ft_strjoin("PWD=", val)));
	return (0);
}

char	*ft_get_home(void)
{
	char	*tmp;
	char	*home;
	t_list	*newlist;

	newlist = g_data.env_var;
	while (newlist)
	{
		tmp = ft_substr(newlist->content, 0, 5);
		if (!ft_strncmp(tmp, "HOME=", 6))
		{
			free(tmp);
			return ((char *)newlist->content + 5);
		}
		else
			newlist = newlist->next;
		free(tmp);
	}
	return (NULL);
}

int	cd_error(int error, char *str)
{
	if (error == 1)
	{
		ft_putstrs_er(
			"minishell: ", str, ": No such file or directory\n", NULL);
		return (g_data.ret = 1);
	}
	else if (error == 2)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (g_data.ret = 1);
	}
	return (0);
}

int	ft_cd(t_command *command)
{
	char	pwd[PATH_MAX];
	char	oldpwd[PATH_MAX];
	char	*val;

	if (!getcwd(oldpwd, PATH_MAX))
		ft_putstrs_er(strerror(errno), "\n", NULL, NULL);
	val = command->tokens[1];
	if (!val)
	{
		val = ft_get_home();
		if (!val)
			return (cd_error(2, NULL));
		if (*val == 0)
			return (g_data.ret = 0);
	}
	if (!chdir(val))
	{
		if (!getcwd(pwd, PATH_MAX))
			ft_putstrs_er(strerror(errno), "\n", NULL, NULL);
		ft_change_pwd(pwd);
		ft_change_oldpwd(oldpwd);
		return (g_data.ret = 0);
	}
	else
		return (cd_error(1, val));
}
