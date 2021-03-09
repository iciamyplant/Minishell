/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 19:21:20 by yviavant          #+#    #+#             */
/*   Updated: 2019/11/28 15:20:41 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*list_start;

	if (!lst || !f)
		return (NULL);
	new = ft_lstnew(f(lst->content));
	list_start = new;
	while (lst->next)
	{
		lst = lst->next;
		if (!(new->next = ft_lstnew(f(lst->content))))
		{
			ft_lstdelone(new->next, del);
			return (NULL);
		}
		new = new->next;
	}
	return (list_start);
}
