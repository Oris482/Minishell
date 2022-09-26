/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaesjeon <jaesjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:14:20 by minsuki2          #+#    #+#             */
/*   Updated: 2022/09/26 20:50:46 by jaesjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_H
# define FT_STRING_H

# include <unistd.h>
# include <limits.h>
# include <stdlib.h>

# ifndef OPEN_MAX
#  define OPEN_MAX       255
# endif
# define BUFFER_SIZE	1

# define FRONT			1
# define BACK			2

// origin_str_utils.c
size_t			ft_strlen(const char *s);
char			*ft_strchr(const char *s, int c);
size_t			ft_strlcat(char *dst, char const *src, size_t dstsize);
size_t			ft_strlcpy(char *dst, char const *src, size_t dstsize);

// origin_str_utils2.c
void			*ft_memset(void *b, int c, size_t len);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_itoa(int num);
char			*ft_strdup(const char *s1);

// custom_str_utils.c
size_t			ft_strcnt(const char *s, const char c);
char			*ft_strsjoin(char const *s1, char const *s2, char const *s3);
char			*ft_strjoin_self(char **str, char *add);
char			*ft_strchr_null(const char *s, int c);
char			*ft_strrchr_right_away(const char *s, int c, char *const end);

// custom_str_utils2.c
int				ft_strcmp_ignore_capital(const char *ref, const char *target);
char			*ft_strcpy(const char *start, const char *end);
char			*ft_chr_to_str(char c);
char			*ft_strjoin_self_add_free(char **str, char *add);
char			*ft_chrjoin_myself(char **str, char c, int pos);

// get_next_line
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_substr(char const *s, unsigned int start, size_t len);
int				ft_isinnl(int fd, char **disk);

int				initialize(int fd, char **disk);
char			*make_line(int fd, char **disk, ssize_t len);
char			*get_next_line(int fd);
#endif
