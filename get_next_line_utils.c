/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 09:32:31 by aassaf            #+#    #+#             */
/*   Updated: 2023/12/07 20:45:06 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	if (!lst)
		return (NULL);
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	return (tmp);
}

int	found_newline(t_list *lst)
{
	int		i;
	t_list	*tmp;

	if (lst == NULL)
		return (0);
	tmp = ft_lstlast(lst);
	i = 0;
	while (tmp->content[i])
	{
		if (tmp->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	create_line(char **line, t_list *lst)
{
	int	i;
	int	len;

	len = 0;
	while (lst)
	{
		i = 0;
		while (lst->content[i])
		{
			if (lst->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		lst = lst->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
}

void	free_all(t_list *lst)
{
	t_list	*tmp;
	t_list	*next;

	tmp = lst;
	while (tmp)
	{
		free(tmp->content);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}
