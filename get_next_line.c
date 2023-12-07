/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 09:32:36 by aassaf            #+#    #+#             */
/*   Updated: 2023/12/07 20:42:57 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	clear_lst(t_list **lst)
{
	t_list	*tmp;
	t_list	*new_node;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_node = malloc(sizeof(t_list));
	if (!lst || !new_node)
		return ;
	new_node->next = NULL;
	tmp = ft_lstlast(*lst);
	while (tmp->content[i] && tmp->content[i] != '\n')
		i++;
	if (tmp->content && tmp->content[i] == '\n')
		i++;
	new_node->content = malloc(sizeof(char) * (ft_strlen(tmp->content) - i)
			+ 1);
	if (new_node->content == NULL)
		return ;
	while (tmp->content[i])
		new_node->content[j++] = tmp->content[i++];
	new_node->content[j] = '\0';
	free_all(*lst);
	*lst = new_node;
}

void	copy_line(t_list *lst, char **line)
{
	int	i;
	int	j;

	j = 0;
	if (lst == NULL)
		return ;
	create_line(line, lst);
	if (*line == NULL)
		return ;
	while (lst)
	{
		i = 0;
		while (lst->content[i])
		{
			if (lst->content[i] == '\n')
			{
				(*line)[j++] = lst->content[i];
				break ;
			}
			(*line)[j++] = lst->content[i++];
		}
		lst = lst->next;
	}
	(*line)[j] = '\0';
}
void	add_to_lst(t_list **lst, char *buff, int nb_read)
{
	int		i;
	t_list	*tmp;
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	new_node->next = NULL;
	new_node->content = malloc(sizeof(char) * (nb_read + 1));
	if (new_node->content == NULL)
		return ;
	i = 0;
	while (buff[i] && i < nb_read)
	{
		new_node->content[i] = buff[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (*lst == NULL)
	{
		*lst = new_node;
		return ;
	}
	tmp = ft_lstlast(*lst);
	tmp->next = new_node;
}

void	read_and_store(int fd, t_list **lst)
{
	int		nb_read;
	char	*buff;

	nb_read = 1;
	while (!found_newline(*lst) && nb_read != 0)
	{
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buff == NULL)
			return ;
		nb_read = (int)read(fd, buff, BUFFER_SIZE);
		if ((*lst == NULL && nb_read == 0) || nb_read == -1)
		{
			free(buff);
			return ;
		}
		buff[nb_read] = '\0';
		add_to_lst(lst, buff, nb_read);
		free(buff);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*lst;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	if (read(fd, &line, 0) < 0)
	{
		free_all(lst);
		lst = NULL;
		return (NULL);
	}
	line = NULL;
	read_and_store(fd, &lst);
	if (lst == NULL)
		return (NULL);
	copy_line(lst, &line);
	clear_lst(&lst);
	if (line[0] == '\0')
	{
		free_all(lst);
		lst = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test2.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s\n", line);
		free(line);
	}
}
