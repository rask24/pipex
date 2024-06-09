/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 15:08:32 by reasuke           #+#    #+#             */
/*   Updated: 2024/06/09 02:22:40 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# define PROG_NAME "pipex"

# define CHILD 0

# define SUCCESS 0
# define FAILURE -1

# define INVALID_ARGUMENTS_MSG "Invalid number of arguments\n"

# define USG_HDR "Usage:"
# define USG_F_0 "  For file input and output:"
# define USG_F_1 "    ./pipex file1 cmd1 cmd2 ... file2"
# define USG_F_2 "      - file1: the input file"
# define USG_F_3 "      - cmd1, cmd2, ...: the commands to execute"
# define USG_F_4 "      - file2: the output file"
# define USG_F_5 "  Example:"
# define USG_F_6 "    ./pipex infile \"ls -l\" \"wc -l\" outfile\n"
# define USG_H_0 "  For here document input:"
# define USG_H_1 "    ./pipex here_doc LIMITER cmd1 cmd2 ... file"
# define USG_H_2 "      - LIMITER: the delimiter string for here document"
# define USG_H_3 "      - cmd1, cmd2, ...: the commands to execute"
# define USG_H_4 "      - file: the output file"
# define USG_H_5 "  Example:"
# define USG_H_6 "    ./pipex here_doc EOF \"cat\" \"grep something\" outfile"

# define UNMATCHED_SINGLE_QUOTE_MSG "unmatched quotation '"
# define UNMATCHED_DOUBLE_QUOTE_MSG "unmatched quotation \""

# define NOT_FOUND_MSG ": command not found\n"

# define INVALID_ARGUMENTS 1
# define FUNCTION_FAIL     2
# define NOT_EXECUTABLE    126
# define NOT_FOUND         127

#endif
