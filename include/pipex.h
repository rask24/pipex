/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:36:23 by reasuke           #+#    #+#             */
/*   Updated: 2024/05/29 00:31:51 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdbool.h>

typedef struct s_ctx
{
	int			**pipe_fds;
	char		**cmds;
	bool		is_here_doc;
	int			num_cmds;
	const char	*infile;
	const char	*outfile;
	const char	*delimiter;
}	t_ctx;

#endif
