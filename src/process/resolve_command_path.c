/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_command_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:33:16 by reasuke           #+#    #+#             */
/*   Updated: 2024/02/26 15:40:26 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "process.h"

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

const char	*resolve_command_path(const char *cmd_name, char **envp)
{
	char		**paths;
	const char	*tmp_path;
	const char	*exec_path;
	int			i;

	paths = ft_split(_extract_path_env(envp), ':');
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
