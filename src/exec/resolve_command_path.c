/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_command_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:33:16 by reasuke           #+#    #+#             */
/*   Updated: 2024/06/09 19:57:41 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "constants.h"
#include "libft.h"
#include "wrapper.h"

#include "exec_internal.h"

static const char	*_join_path_with_cmd_name(const char *path,
						const char *cmd_name)
{
	const char	*joined;
	const char	*tmp;

	tmp = ft_xstrjoin(path, "/");
	joined = ft_xstrjoin(tmp, cmd_name);
	free((char *)tmp);
	return (joined);
}

const char	*resolve_command_path(const char *cmd_name, char **envp)
{
	char		**paths;
	const char	*path_env;
	const char	*tmp_path;
	const char	*exec_path;
	int			i;

	path_env = extract_path_from_env(envp);
	if (!path_env)
		return (NULL);
	paths = ft_xsplit(path_env, ':');
	i = 0;
	while (paths[i])
	{
		tmp_path = _join_path_with_cmd_name(paths[i], cmd_name);
		if (access(tmp_path, X_OK) == SUCCESS)
		{
			exec_path = ft_xstrdup(tmp_path);
			ft_free_strs(paths);
			return (exec_path);
		}
		free((char *)tmp_path);
		i++;
	}
	ft_free_strs(paths);
	return (NULL);
}
