/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 02:25:26 by reasuke           #+#    #+#             */
/*   Updated: 2024/06/09 19:57:41 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_INTERNAL_H
# define EXEC_INTERNAL_H

const char	*extract_path_from_env(char **envp);
const char	*resolve_command_path(const char *cmd_name, char **envp);

#endif
