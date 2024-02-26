/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:29:05 by reasuke           #+#    #+#             */
/*   Updated: 2024/02/26 15:20:56 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "libft.h"

static const char	*_extract_path_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH", 4))
			return (ft_strchr(envp[i], '=') + 1);
		i++;
	}
	return (NULL);
}

static const char	*_join_path_with_cmd_name(const char *path,
						const char *cmd_name)
{
	const char	*joined;
	const char	*tmp;

	tmp = ft_strjoin(path, "/");
	joined = ft_strjoin(tmp, cmd_name);
	free((char *)tmp);
	return (joined);
}

static const char	*_resolve_command_path(const char *cmd_name,
						const char *path_env)
{
	char		**paths;
	const char	*tmp_path;
	const char	*exec_path;
	int			i;

	paths = ft_split(path_env, ':');
	i = 0;
	while (paths[i])
	{
		tmp_path = _join_path_with_cmd_name(paths[i], cmd_name);
		if (access(tmp_path, X_OK) == SUCCESS)
		{
			exec_path = ft_strdup(tmp_path);
			ft_free_strs(paths);
			return (exec_path);
		}
		free((char *)tmp_path);
		i++;
	}
	ft_free_strs(paths);
	return (NULL);
}

void	execute_command(const char *cmd, char **envp)
{
	char		**cmd_list;
	const char	*path_env;
	const char	*exec_path;

	cmd_list = ft_split(cmd, ' ');
	path_env = _extract_path_env(envp);
	exec_path = _resolve_command_path(cmd_list[0], path_env);
	execve(exec_path, cmd_list, envp);
}
