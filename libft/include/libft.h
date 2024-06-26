/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 19:04:55 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/19 22:34:41 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "color.h"
# include "ft_constant.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "matrix.h"
# include "pixel.h"
# include "unit_test.h"
# include "vector.h"
# include "vs_type.h"
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

/* char ----------------------------------------------------------------------*/
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					is_hexagit(char c);

/* error ---------------------------------------------------------------------*/
t_bool				error_msg(char *error_msg);
t_bool				error_perror(char *error_msg);

/* int -----------------------------------------------------------------------*/
int					ft_atoi(const char *nptr);
int					atoi_offset(char **str);
char				*ft_itoa(int n);
int					hexatoi_offset(char **str);
char				*si32_to_decstr_offset(char *str, int n);
t_si32				si32_min(t_si32 a, t_si32 b);
t_si32				si32_max(t_si32 a, t_si32 b);
long long			ft_atol(const char *str);
int					len_num(long long num);
int					len_str_num(char *str);

/* lst -----------------------------------------------------------------------*/
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
t_bool				ft_lstadd_back_new(t_list **list, t_char_m *str);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
void				display_lst(t_list *lst);

/* mem -----------------------------------------------------------------------*/
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);

/* put -----------------------------------------------------------------------*/
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

/* str -----------------------------------------------------------------------*/
char				**ft_split(char const *s, char c);
void				ft_split_free(char **split);
size_t				count_words(char const *str, char c);
char				*ft_strchr(const char *s, int c);
int					ft_strchr_i(char *s, int c);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strdup(const char *s);
char				*ft_strdup_free(char *s);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoin_free_s1(char const *s1, char const *s2);
char				*ft_strjoin_free_s2(char const *s1, char const *s2);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *s);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strndup(const char *src, int size);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
int					ft_strstr(const char *big, const char *little);
char				*ft_strrchr(const char *s, int c);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*strcpy_offset(char *dst, const char *src);
void				strlist_print_fd(t_list *strlist, int fd);
void				strtab_print(char **tabstr);
void				strtab_print_fd(char **tabstr, int fd);
void				strtab_free(char **strtab);
int					ft_strtab_size(char **strtab);

/* tabsi32 -------------------------------------------------------------------*/
typedef struct s_tabsi32
{
	int				*elem;
	int				size;
}					t_tabsi32;

t_tabsi32			tabsi32_init(int *tab, int size);
void				tabsi32_print(t_tabsi32 d, char *before, char *sep,
						char *after);

t_si32				ft_abs(t_si32 a);

#endif
