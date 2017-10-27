/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 13:34:08 by mbraslav          #+#    #+#             */
/*   Updated: 2017/04/11 13:34:17 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <sys/stat.h>

# include "libft/libft.h"

# define BUFF_SIZE 1024

char	***get_input(char **env);
char	*read_input(void);
void	check_input(char **input);

void	run_command(char **argv, char ***env);
void	run_builtin(int argc, char **argv, char ***env);
void	run_prg(char **argv, char **env);
int		execute(char *path, char **argv, char **env);

void	builtin_cd(int argc, char **argv, char ***env);
void	builtin_echo(int argc, char **argv);
void	builtin_env(int argc, char **argv, char **env);
void	builtin_setenv(int argc, char **argv, char ***env);
void	builtin_unsetenv(int argc, char **argv, char ***env);

void	minishell_setenv(const char *var, const char *value, char ***env);
void	minishell_unsetenv(const char *var, char ***env);

char	**get_env(char **environ);
char	*get_env_var(const char *var, char **env);
void	print_env(char **env);
void	add_env_var(const char *var, const char *value, char ***env);

void	error(const char *error_msg, const char *str);
void	free_str_array(char **arr);
int		is_dir(const char *path);
size_t	arg_count(const char *str, char *delims);
size_t	arg_len(const char *str, char *delims);

#endif
