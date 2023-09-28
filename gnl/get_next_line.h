/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 23:51:53 by mporras-          #+#    #+#             */
/*   Updated: 2022/01/31 00:23:49 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

char	*get_next_line(int fd);
int		ft_strlen(char *s);
char	*ft_substr(char *s, int start, int len, int *nl_len);
char	*ft_strdup(char *src, int len);
char	*ft_strjoin(char *s1, char *s2, int bytes, int *nl_len);
void	*ft_memcpy(char *dest, char *src, int n);
char	*ft_line_proccess(char **buffer, int bytes, int *nl_len);
char	*ft_buffer_reader(int fd, char **buffer, char *reader, int *nl_len);
char	*ft_delete_line_from_buffer(char **buffer, int *nl_len);
int		ft_get_endline(char *str);

#endif
