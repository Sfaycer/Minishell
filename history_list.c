#include "parser.h"

t_history_list	*ft_hlstnew(char *str)
{
	t_history_list	*new_list;

	new_list = malloc(1 * sizeof(t_history_list));
	if (!new_list)
		malloc_error();
	new_list->str = str;
	new_list->next = NULL;
	new_list->prev = NULL;
	return (new_list);
}

t_history_list	*ft_hlstlast(t_history_list *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

t_history_list	*ft_hlstfirst(t_history_list *lst)
{
	while (lst)
	{
		if (lst->prev == NULL)
			return (lst);
		lst = lst->prev;
	}
	return (lst);
}

void	ft_l_hlstadd_front(t_history_list **lst, t_history_list *new)
{
	t_history_list	*tmp;

	if (!lst || !new)
		return ;
	tmp = *lst;
	if (!(tmp))
		*lst = new;
	else
	{
		new->next = *lst;
		new->prev = tmp->prev;
		tmp->prev = new;
		*lst = new;
	}
}

void	ft_hlstadd_back(t_history_list **lst, t_history_list *new)
{
	t_history_list	*temp;

	if (!lst || !new)
		return ;
	temp = *lst;
	if (!temp)
		*lst = new;
	else
	{
		while (temp->next)
			temp = temp->next;
	//	temp = ft_hlstlast(*lst);
		temp->next = new;
		new->prev = temp;
	}
}
