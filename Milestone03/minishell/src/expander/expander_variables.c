/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_variables.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 18:18:22 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/14 12:41:58 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_value(t_exec *env, char *var_name)
{
	int		i;
	char	*equals;

	if (!env || !var_name)
		return (NULL);
	if (env->local_vars)
	{
		i = find_env_var(env->local_vars, var_name);
		if (i != -1)
		{
			equals = ft_strchr(env->local_vars[i], '=');
			if (equals)
				return (ft_strdup(equals + 1));
		}
	}
	if (!env->envp)
		return (NULL);
	i = find_env_var(env->envp, var_name);
	if (i == -1)
		return (NULL);
	equals = ft_strchr(env->envp[i], '=');
	if (!equals)
		return (NULL);
	return (ft_strdup(equals + 1));
}

static char	*extract_var_name(char *str, int *i)
{
	int		start;
	char	*var_name;

	start = ++(*i);
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var_name = ft_substr(str, start, *i - start);
	return (var_name);
}

static char	*expand_var(char *str, int *i, t_exec *env)
{
	char	*var_name;
	char	*var_value;

	if (str[*i + 1] == '?')
	{
		(*i) += 2;
		return (ft_itoa(env->last_exit));
	}
	if (!str[*i + 1] || (!ft_isalnum(str[*i + 1]) && str[*i + 1] != '_'))
	{
		(*i)++;
		return (ft_strdup("$"));
	}
	var_name = extract_var_name(str, i);
	if (!var_name)
		return (NULL);
	var_value = get_env_value(env, var_name);
	free(var_name);
	if (!var_value)
		return (ft_strdup(""));
	return (var_value);
}

char	*append_dollar_expansion(char *str, t_exec *env, int *i, char *new_str)
{
	char	*expanded;
	char	*temp;

	expanded = expand_var(str, i, env);
	if (!expanded)
		return (NULL);
	temp = ft_strjoin(new_str, expanded);
	free(new_str);
	free(expanded);
	if (!temp)
		return (NULL);
	return (temp);
}

char	*expander_variables(char *str, t_exec *env)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = ft_strdup("");
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$')
			new_str = append_dollar_expansion(str, env, &i, new_str);
		else
			new_str = append_char_to_str(new_str, str[i++]);
		if (!new_str)
			return (NULL);
	}
	return (new_str);
}
