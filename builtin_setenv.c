/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:53:45 by mbraslav          #+#    #+#             */
/*   Updated: 2017/04/26 15:53:46 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_setenv(const char *var, const char *value, char ***env)
{
	char	*new;
	size_t	len;
	int		i;

	if (get_env_var(var, *env) == NULL)
		add_env_var(var, value, env);
	else
	{
		i = 0;
		len = ft_strlen(var);
		while (ft_strncmp((*env)[i], var, len))
			i++;
		new = ft_strnew(len + ft_strlen(value) + 1);
		ft_strcat(ft_strcat(ft_strcpy(new, var), "="), value);
		free((*env)[i]);
		(*env)[i] = new;
	}
}

void	builtin_setenv(int argc, char **argv, char ***env)
{
	if (argc == 2)
		minishell_setenv(argv[1], "", env);
	else if (argc == 3)
		minishell_setenv(argv[1], argv[2], env);
	else
		write(2, "usage: setenv var [value]\n", 26);
}
