/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 15:15:16 by mbraslav          #+#    #+#             */
/*   Updated: 2017/04/28 15:15:17 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*read_input(void)
{
	char	*input;
	char	buff[BUFF_SIZE];
	char	c;
	char	*tmp;
	size_t	i;

	input = ft_strnew(0);
	i = 0;
	buff[0] = 0;
	while (!ft_strchr(buff, '\n'))
	{
		ft_memset(buff, 0, BUFF_SIZE);
		i = 0;
		c = 0;
		while (i < BUFF_SIZE - 2 && c != '\n')
		{
			read(0, &c, 1);
			buff[i] = c;
			i++;
		}
		tmp = input;
		input = ft_strjoin(input, buff);
		free(tmp);
	}
	return (input);
}

static void	env_replace(char **str, char **env)
{
	char	*var;
	char	*value;
	char	*end;
	char	*tmp;

	while ((var = ft_strchr(*str, '$')) != NULL)
	{
		*var++ = 0;
		end = var;
		while (ft_isalpha(*end))
			end++;
		if (end == var)
		{
			ft_strcat(*str, end);
			break ;
		}
		var = ft_strsub(var, 0, end - var);
		value = ft_strdup(get_env_var(var, env) ? get_env_var(var, env) : "");
		tmp = *str;
		*str = ft_strnew(ft_strlen(*str) + ft_strlen(value) + ft_strlen(end));
		ft_strcat(ft_strcat(ft_strcpy(*str, tmp), value), end);
		free(var);
		free(value);
		free(tmp);
	}
}

static char	**split_command(const char *cmd)
{
	char	**argv;
	size_t	argc;
	size_t	len;
	char	*s;
	int		i;

	argc = arg_count(cmd, " \t");
	argv = (char **)malloc(sizeof(char *) * argc + 1);
	argv[argc] = 0;
	s = (char *)cmd;
	i = 0;
	while (i < (int)argc)
	{
		while (ft_isspace(*s))
			s++;
		len = arg_len(s, " \t");
		argv[i] = ft_strsub(s, ((*s == '\'' && *(s + len - 1) == '\'') || \
(*s == '"' && *(s + len - 1) == '"')) ? 1 : 0, ((*s == '\'' && *(s + len - \
1) == '\'') || (*s == '"' && *(s + len - 1) == '"')) ? len - 2 : len);
		s = s + len + 1;
		while (ft_isspace(argv[i][--len]))
			argv[i][len] = 0;
		i++;
	}
	return (argv);
}

static char	***split_input(const char *input)
{
	char	***cmd;
	size_t	cmd_num;
	char	*s;
	char	*command;
	int		i;

	cmd_num = arg_count(input, ";");
	cmd = (char ***)malloc(sizeof(char **) * cmd_num + 1);
	cmd[cmd_num] = 0;
	s = (char *)input;
	i = 0;
	while (i < (int)cmd_num)
	{
		while (ft_isspace(*s))
			s++;
		command = ft_strsub(s, 0, arg_len(s, ";"));
		cmd[i] = split_command(command);
		free(command);
		s = s + arg_len(s, ";") + 1;
		i++;
	}
	return (cmd);
}

char		***get_input(char **env)
{
	char	***cmds;
	char	*input;

	input = read_input();
	check_input(&input);
	if (ft_strchr(input, '$'))
		env_replace(&input, env);
	input[ft_strlen(input) - 1] = 0;
	cmds = split_input(input);
	free(input);
	return (cmds);
}
