/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 09:32:31 by aassaf            #+#    #+#             */
/*   Updated: 2023/12/05 19:47:30 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *s)
{
	int	i;

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
void create_line(char **line, t_list *lst)
{
        int i;
        int len;

        len = 0;
        while(lst)
        {
                i = 0;
                while(lst->content[i])
                {
                        if(lst->content[i] == '\n')
                        {
                                len++;
                                break;
                        }
                        len++;
                        i++;
                }
                lst = lst->next;
        }
        *line = malloc(sizeof(char) * (len + 1));

}
void copy_line(t_list *lst, char **line)
{
        int i;
        int j;
        
        j = 0;
        if(!lst)
                return ;
        create_line(line, lst);
        if(*line == NULL)
                return ;
        while(lst)
        {
                i = 0;
                while(lst->content[i])
                {
                        if(lst->content[i] == '\n')
                        {
                                (*line)[j++] = lst->content[i];
                                break;
                        }
                        (*line)[j++] = lst->content[i++];
                }
                lst = lst->next;
        }
        (*line)[j] = '\0';
}

void free_all(t_list *lst)
{
        t_list *tmp;
        t_list *next;
        tmp = lst;
        while(tmp)
        {
                free(tmp->content);
                next = tmp->next;
                free(tmp);
                tmp = next;
        }
}

void clear_lst(t_list **lst)
{
        t_list *tmp;
        t_list *new_node;
        int i;
        int j;
        
        i = 0;
        j = 0;
        new_node = malloc(sizeof(t_list));
        if(!lst || !new_node)
                return ;
        new_node->next = NULL;
        tmp = ft_lstlast(*lst);
        while (tmp->content[i] && tmp->content[i] != '\n')
                i++;
        if(tmp->content && tmp->content[i] == '\n')
                i++;
        new_node->content = malloc(sizeof(char) * (ft_strlen(tmp->content) - i) + 1);
        if(new_node->content == NULL)
                return ;
        while(tmp->content[i])
                new_node->content[j++] = tmp->content[i++];
        new_node->content[j] = '\0';
        free_all(*lst);
        *lst = new_node;
}