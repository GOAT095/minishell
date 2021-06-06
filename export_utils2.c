#include "minishell.h"

void	ft_free_exist(char *str_free, char *str, char c)
{
	if (ft_strchr(str, c))
		free (str_free);
}

char	*ft_get_oldvar(char *content)
{
	char	*tmp_str;
	int		len;
	int		tmp_len;
	char	*old_var;

	tmp_str = ft_strchr(content, '=');
	if (tmp_str)
	{
		tmp_len = ft_strlen(tmp_str);
		len = ft_strlen(content);
		old_var = ft_substr(content, 0, len - tmp_len);
	}
	else
		old_var = content;
	return (old_var);
}

int	can_change(char *content, char *token, char *old_var, char *export_var)
{
	if (ft_strchr(content, '=') && !ft_strchr(token, '='))
	{
		ft_free_exist(old_var, content, '=');
		ft_free_exist(export_var, token, '+');
		return (1);
	}
	return (0);
}

void	ft_change(int j, char *token, char *old_var, t_list *newlist)
{
	char	*tmp_str;
	char	*tmp_free;

	while (j >= 0)
	{
		newlist = newlist->next;
		j--;
	}
	tmp_str = ft_strchr(token, '+');
	if (tmp_str != 0)
	{
		ft_free_exist(old_var, newlist->content, '=');
		tmp_free = newlist->content;
		newlist->content = ft_strjoin(newlist->content, tmp_str + 2);
		free(tmp_free);
	}
	else
	{
		ft_free_exist(old_var, newlist->content, '=');
		tmp_free = newlist->content;
		newlist->content = ft_strdup(token);
		free(tmp_free);
	}
}

int	ft_export_error(char *str, char *token)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstrs_fd(str, ": `", token, "': not a valid identifier\n");
	return (g_data.ret = 1);
}
