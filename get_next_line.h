/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 09:32:39 by aassaf            #+#    #+#             */
/*   Updated: 2023/12/07 15:50:58 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

char				*get_next_line(int fd);
t_list				*ft_lstlast(t_list *lst);
void				read_and_store(int fd, t_list **lst);
void				add_to_lst(t_list **lst, char *buff, int nb_read);
int					found_newline(t_list *lst);
void				create_line(char **line, t_list *lst);
size_t				ft_strlen(const char *s);
void				copy_line(t_list *lst, char **line);
void				free_all(t_list *lst);
void				clear_lst(t_list **lst);
#endif
