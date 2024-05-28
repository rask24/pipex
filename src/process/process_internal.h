/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:34:07 by reasuke           #+#    #+#             */
/*   Updated: 2024/05/28 20:42:55 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_INTERNAL_H
# define PROCESS_INTERNAL_H

# define TMPFILE ".heredoc_tmpfile"

typedef enum e_file_mode
{
	MODE_INFILE,
	MODE_OUTFILE_APPEND,
	MODE_OUTFILE_OVERWRITE,
	MODE_HEREDOC,
	MODE_PIPE
}	t_file_mode;

typedef struct s_process
{
	t_file_mode	mode;
	const char	*file_path;
	const char	*cmd;
	int			*pipe_fd;
	int			*next_pipe_fd;
	char		**envp;
	const char	*delimiter;
}	t_process;

pid_t	exec_single_process(t_process *pr);

#endif
