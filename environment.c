/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:55:40 by mbraslav          #+#    #+#             */
/*   Updated: 2017/04/26 15:55:41 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_env(char **environ)
{
	char	**dup;
	int		i;

	i = 0;
	while (environ[i])
		i++;
	dup = (char **)malloc(sizeof(char *) * (i + 1));
	dup[i] = 0;
	i = 0;
	while (environ[i])
	{
		dup[i] = ft_strdup(environ[i]);
		i++;
	}
	minishell_setenv("SHELL", "minishell", &dup);
	minishell_setenv("PROMPT", "$> ", &dup);
	return (dup);
}

char	*get_env_var(const char *var, char **env)
{
	size_t	len;
	int		i;

	if (var == NULL)
		return (NULL);
	len = ft_strlen(var);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, len))
			break ;
		i++;
	}
	if (env[i] == 0)
		return (NULL);
	else
		return (env[i] + len + 1);
}

void	print_env(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		ft_printf("%s\n", env[i++]);
}

void	add_env_var(const char *var, const char *value, char ***env)
{
	char	**new_env;
	char	*new_var;
	size_t	len;
	int		i;

	len = ft_strlen(var) + ft_strlen(value) + 1;
	new_var = ft_strnew(len);
	ft_strcat(ft_strcat(ft_strcpy(new_var, var), "="), value);
	i = 0;
	while ((*env)[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 2));
	new_env[i] = 0;
	new_env[i + 1] = 0;
	i = 0;
	while ((*env)[i])
	{
		new_env[i] = (*env)[i];
		i++;
	}
	new_env[i] = new_var;
	free(*env);
	*env = new_env;
}
