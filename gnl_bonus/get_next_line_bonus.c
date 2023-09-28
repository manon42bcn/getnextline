/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 23:51:31 by mporras-          #+#    #+#             */
/*   Updated: 2022/02/07 00:44:47 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/**
 * @brief Retrieves the next line from a file descriptor.
 *
 * This function reads the next line from a given file descriptor. If the
 * buffer contains a previously read portion of the file, it processes that
 * first before reading more from the file.
 *
 * @param fd File descriptor to read from.
 * @return Pointer to the next line or NULL on error or end of file.
 */
char	*get_next_line(int fd)
{	
	static char	*buffer[256];
	char		*rst;
	char		*reader;
	int			nl_len[2];

	if (fd < 0 || fd > 257 || BUFFER_SIZE < 1)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = NULL;
	nl_len[0] = ft_get_endline(buffer[fd]);
	nl_len[1] = ft_strlen(buffer[fd]);
	if (nl_len[0] == 0)
	{
		reader = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (reader == NULL)
			return (NULL);
		rst = ft_buffer_reader(fd, &buffer[fd], reader, &nl_len[0]);
		free (reader);
	}
	else
		rst = ft_line_proccess(&buffer[fd], 0, &nl_len[0]);
	return (rst);
}

/**
 * @brief Processes the current buffer to extract a line.
 *
 * Depending on the state of the buffer and the given newline length,
 * this function retrieves a full line from the buffer and adjusts the
 * buffer accordingly.
 *
 * @param buffer Pointer to the buffer.
 * @param bytes Number of bytes read in the current read operation.
 * @param nl_len An array containing the position of newline and the length.
 * @return The extracted line or NULL if there's an error.
 */
char	*ft_line_proccess(char **buffer, int bytes, int *nl_len)
{
	char	*rst;

	if (!*buffer)
		return (NULL);
	if (nl_len[0] == 0 && bytes == 0)
	{
		rst = ft_strdup(*buffer, nl_len[1]);
		*buffer = ft_delete_line_from_buffer(buffer, &nl_len[0]);
	}
	else
	{
		rst = ft_substr(*buffer, 0, nl_len[0], &nl_len[0]);
		*buffer = ft_delete_line_from_buffer(buffer, &nl_len[0]);
	}
	return (rst);
}

/**
 * @brief Reads content from file descriptor and updates buffer.
 *
 * Reads from the file descriptor into the buffer until a newline is
 * found or until there's an error or end of file. Processes the buffer
 * to extract a line when necessary.
 *
 * @param fd File descriptor to read from.
 * @param buffer Pointer to the buffer.
 * @param reader Temporary reader for the current read operation.
 * @param nl_len An array containing the position of newline and the length.
 * @return The extracted line or NULL if there's an error.
 */
char	*ft_buffer_reader(int fd, char **buffer, char *reader, int *nl_len)
{
	int	bytes;
	int	nl_reader;

	bytes = 0;
	while (nl_len[0] == 0)
	{
		bytes = read(fd, reader, BUFFER_SIZE);
		if (bytes <= 0)
			break ;
		reader[bytes] = '\0';
		nl_len[1] += bytes;
		nl_reader = ft_get_endline(reader);
		if (!*buffer)
			*buffer = ft_strdup(reader, bytes);
		else
			*buffer = ft_strjoin(*buffer, reader, bytes, &nl_len[0]);
		if (*buffer == NULL)
			break ;
		if (nl_reader > 0)
			nl_len[0] = (nl_len[1] - bytes) + nl_reader;
	}
	if (bytes < 0 || !*buffer)
		return (NULL);
	return (ft_line_proccess(buffer, bytes, &nl_len[0]));
}

/**
 * @brief Deletes a line from the buffer.
 *
 * If the buffer only contains the current line, it's freed. If it contains
 * more, the function returns a new buffer without the line.
 *
 * @param buffer Pointer to the buffer.
 * @param nl_len An array containing the position of newline and the length.
 * @return The updated buffer after removing the line or NULL.
 */
char	*ft_delete_line_from_buffer(char **buffer, int *nl_len)
{
	char	*rst;

	if (nl_len[0] == nl_len[1] || (nl_len[0] == 0 && nl_len[1] > 0))
	{
		free(*buffer);
		return (NULL);
	}
	rst = ft_substr(*buffer, nl_len[0], nl_len[1] - nl_len[0], &nl_len[0]);
	free(*buffer);
	return (rst);
}

/**
 * @brief Finds the position of the newline character in a string.
 *
 * Iterates over the string to find the first occurrence of the newline
 * character. Returns its position or 0 if not present.
 *
 * @param str The string to check.
 * @return Position of newline or 0 if not found.
 */
int	ft_get_endline(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}
