#include "minishell.h"

void	ft_print_export2(char *content, char *str_chr, char *var)
{
	int		i;
	char	*str;
	int		len;
	int		chr_len;

	i = 0;
	len = ft_strlen(content);
	chr_len = ft_strlen(str_chr);
	str = content + len - chr_len + 1;
	var = ft_substr(content, 0, len - chr_len + 1);
	ft_putstrs_fd(var, "\"", NULL, NULL);
	while (str[i] != '\0')
	{
		if (str[i] == '\\' || str[i] == '$')
			write(1, "\\", 1);
		write(1, &str[i], 1);
		i++;
	}
	ft_putstr_fd("\"\n", 1);
	free(var);
}

int	ft_valid_export_var(
	t_command *command, char *export_var, char *token, char *str)
{
	if (!ft_strcmp(str, "unset") && ft_strchr(token, '='))
		return (ft_export_error(str, token));
	if (export_var[0] == '_'
		|| (export_var[0] == '#' && command->n_tokens == 2))
		return (0);
	if (export_var[0] == '\0' || ft_isdigit(export_var[0]) || token[0] == '='
		|| (export_var[0] != '#' && ft_strchr_set(
				export_var, "$&|;-+=~!@^%{} []:?.#/,\'\\\"", token)))
	{
		return (ft_export_error(str, token));
	}
	return (0);
}

char	*ft_get_export_var(char *exp_token)
{
	char	*exp_var;
	char	*tmp_str;
	int		tmp_len;
	int		len;

	tmp_str = ft_strchr(exp_token, '=');
	if (tmp_str)
	{
		tmp_len = ft_strlen(tmp_str);
		len = ft_strlen(exp_token);
		exp_var = ft_substr(exp_token, 0, len - tmp_len);
	}
	else
		exp_var = exp_token;
	return (exp_var);
}

int	ft_sort_exp_cmp(char *i_content, char *j_content)
{
	char	*i_data;
	char	*j_data;

	i_data = ft_get_export_var(i_content);
	j_data = ft_get_export_var(j_content);
	if (ft_strcmp(i_data, j_data) > 0)
	{
		if (ft_strchr(i_content, '='))
			free(i_data);
		if (ft_strchr(j_content, '='))
			free(j_data);
		return (1);
	}
	if (ft_strchr(i_content, '='))
		free(i_data);
	if (ft_strchr(j_content, '='))
		free(j_data);
	return (0);
}

void	ft_sort_export(void)
{
	t_list	*i;
	t_list	*j;
	char	*tmp_data;

	i = g_data.env_var;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (ft_sort_exp_cmp(i->content, j->content) == 1)
			{
				tmp_data = i->content;
				i->content = j->content;
				j->content = tmp_data;
			}
			j = j->next;
		}
		i = i->next;
	}
}
