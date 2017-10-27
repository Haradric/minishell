/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 16:52:12 by mbraslav          #+#    #+#             */
/*   Updated: 2017/04/10 16:52:13 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		minishell(char ***env)
{
	char	***cmds;
	int		exit;
	int		i;

	ft_putstr_fd(get_env_var("PROMPT", *env), 1);
	cmds = get_input(*env);
	i = 0;
	exit = 0;
	while (cmds[i])
	{
		if (!cmds[i][0] || !ft_strcmp(cmds[i][0], ""))
			;
		else if (!ft_strcmp(cmds[i][0], "exit"))
			exit = (!cmds[i][1]) ? 1 : -1;
		else
			run_command(cmds[i], env);
		free_str_array(cmds[i]);
		if (exit)
			break ;
		i++;
	}
	i = 0;
	free(cmds);
	return (exit);
}

int		main(int argc, char **argv, char **environ)
{
	char	**env;
	int		exit;

	if (argc == 2 && argv[0] != NULL)
	{
		write(2, "usage: ./minishell\n", 19);
		return (1);
	}
	else
	{
		env = get_env(environ);
		exit = 0;
		while (!exit)
			exit = minishell(&env);
		free_str_array(env);
		return ((exit == 1) ? 0 : 1);
	}
}
