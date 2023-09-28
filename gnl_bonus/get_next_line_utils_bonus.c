/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 23:54:08 by mporras-          #+#    #+#             */
/*   Updated: 2022/02/07 00:43:10 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief Compute the length of a string.
 *
 * @param s Input string.
 * @return Length of the string.
 */
int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

/**
 * @brief Creates a substring of a given string.
 *
 * Generates a substring of the original string starting from 'start'
 * and of 'len' length. The idea of using this adaptation of ft_substr
 * is use nl_len, to avoid a new iteration over the string.
 *
 * @param s Input string.
 * @param start Starting index of the substring.
 * @param len Length of the substring.
 * @param nl_len An array containing position of newline and the length.
 * @return New substring or NULL if there's an error.
 */
char	*ft_substr(char *s, int start, int len, int *nl_len)
{
	char	*rst;

	if (!s)
		return (NULL);
	if (len > (nl_len[1] - start))
		len = nl_len[1] - start;
	if (start > nl_len[1])
		len = 0;
	rst = (char *)malloc(sizeof(char) * (len + 1));
	if (rst == NULL)
		return (NULL);
	rst[len] = '\0';
	ft_memcpy(rst, &s[start], len);
	return (rst);
}

/**
 * @brief Duplicates a string up to a certain length.
 *
 * Allocates memory and duplicates 'len' characters from the source string.
 * This versions use len, to avoid a new iteration over the string.
 *
 * @param src Source string.
 * @param len Length of characters to duplicate.
 * @return The duplicated string or NULL if there's an error.
 */
char	*ft_strdup(char *src, int len)
{
	char	*dst;

	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (dst == NULL)
		return (NULL);
	dst[len] = '\0';
	while (len-- > 0)
		dst[len] = src[len];
	return (dst);
}

/**
 * @brief Joins two strings.
 *
 * Concatenates s1 and s2 into a new string. Frees the memory occupied by s1.
 * Use len as parameter avoid new iterations over the strings.
 *
 * @param s1 First string.
 * @param s2 Second string.
 * @param bytes Number of bytes read in current read operation.
 * @param nl_len An array containing position of newline and the length.
 * @return New concatenated string or NULL if there's an error.
 */
char	*ft_strjoin(char *s1, char *s2, int bytes, int *nl_len)
{
	char	*rst;

	if (!s1 || !s2)
		return (NULL);
	rst = (char *)malloc(sizeof(char) * (nl_len[1] + 1));
	if (rst == NULL)
		return (NULL);
	rst[nl_len[1]] = '\0';
	ft_memcpy(rst, s1, nl_len[1] - bytes);
	ft_memcpy(&rst[nl_len[1] - bytes], s2, bytes);
	free(s1);
	return (rst);
}

/**
 * @brief Copies 'n' bytes from 'src' to 'dest'.
 *
 * Performs a memory copy for 'n' bytes. If both dest and src are NULL,
 * returns NULL.
 *
 * @param dest Destination memory address.
 * @param src Source memory address.
 * @param n Number of bytes to copy.
 * @return Pointer to the destination memory address.
 */
void	*ft_memcpy(char *dest, char *src, int n)
{
	int	i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}
