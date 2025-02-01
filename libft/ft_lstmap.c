/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebaai <asebaai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:14:15 by asebaai           #+#    #+#             */
/*   Updated: 2025/01/28 17:34:08 by asebaai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*anewlist;

	anewlist = NULL;
	while (lst != NULL)
	{
		newlist = ft_lstnew((*f)(lst->content));
		if (newlist == NULL)
		{
			ft_lstclear(&anewlist, del);
			break ;
		}
		ft_lstadd_back(&anewlist, newlist);
		lst = lst->next;
	}
	return (anewlist);
}
