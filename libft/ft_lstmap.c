/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 21:24:33 by mel-bouh          #+#    #+#             */
/*   Updated: 2023/11/11 20:13:16 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*new;
	void	*tmp;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	newlist = NULL;
	while (lst)
	{
		tmp = f(lst->content);
		new = ft_lstnew(tmp);
		if (new == NULL)
		{
			del(tmp);
			ft_lstclear(&newlist, del);
			return (newlist);
		}
		ft_lstadd_back(&newlist, new);
		lst = lst->next;
	}
	return (newlist);
}
