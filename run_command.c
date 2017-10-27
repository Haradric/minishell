/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:56:31 by mbraslav          #+#    #+#             */
/*   Updated: 2017/04/26 15:56:33 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_command(char **argv, char ***env)
{
	int		argc;

	argc = 0;
	while (argv[argc])
		argc++;
	if (!ft_strcmp(argv[0], "cd") || !ft_strcmp(argv[0], "echo") || \
		!ft_strcmp(argv[0], "env") || !ft_strcmp(argv[0], "setenv") || \
		!ft_strcmp(argv[0], "unsetenv"))
		run_builtin(argc, argv, env);
	else if (!access(argv[0], F_OK))
	{
		if (!access(argv[0], X_OK) && !is_dir(argv[0]))
			execute(argv[0], argv, *env);
		else
			error("minishell: permission denied: ", argv[0]);
	}
	else
		run_prg(argv, *env);
}

void	run_builtin(int argc, char **argv, char ***env)
{
	if (!ft_strcmp(argv[0], "cd"))
		builtin_cd(argc, argv, env);
	else if (!ft_strcmp(argv[0], "echo"))
		builtin_echo(argc, argv);
	else if (!ft_strcmp(argv[0], "env"))
		builtin_env(argc, argv, *env);
	else if (!ft_strcmp(argv[0], "setenv"))
		builtin_setenv(argc, argv, env);
	else if (!ft_strcmp(argv[0], "unsetenv"))
		builtin_unsetenv(argc, argv, env);
}

void	run_prg(char **argv, char **env)
{
	char	**path_list;
	char	path[1024];
	int		i;
	int		exec_status;

	i = 0;
	path_list = ft_strsplit(get_env_var("PATH", env), ':');
	while (path_list && path_list[i])
	{
		ft_memset(path, 0, 1024);
		ft_strcat(ft_strcat(ft_strcat(path, path_list[i]), "/"), argv[0]);
		if (!access(path, F_OK & X_OK))
		{
			exec_status = execute(path, &argv[0], env);
			if (exec_status == -1 || exec_status == -2)
				error("minishell: an error occured", "");
			free_str_array(path_list);
			return ;
		}
		i++;
	}
	if (path_list)
		free_str_array(path_list);
	error("minishell: command not found: ", argv[0]);
}

int		execute(char *path, char **argv, char **env)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		return ((execve(path, argv, env) == -1) ? -2 : 0);
	return (1);
}
