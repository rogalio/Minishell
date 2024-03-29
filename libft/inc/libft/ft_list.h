/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoursou <asoursou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 18:02:20 by asoursou          #+#    #+#             */
/*   Updated: 2020/10/02 13:23:20 by asoursou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIST_H
# define FT_LIST_H
# define FT_REQUIRE_TYPE_GENERIC
# define FT_REQUIRE_TYPE_SIZE_T
# include "private/ft_include.h"

typedef struct s_list	t_list;
struct	s_list
{
	void	*content;
	t_list	*next;
};

/*
** Returns the element at the given index if it exists.
** Returns NULL if the element does not exist.
*/
t_list	*ft_list_at(t_list *list, size_t index);

/*
** Free a singly linked list.
** The function pointer del can be NULL.
** Returns NULL.
*/
void	*ft_list_clear(t_list **list, t_gfunction del);

/*
** Copy all elements of the list in a new list.
** It does not makes a deep copy of the content.
** Returns the copy of the list, or NULL on error if the list was not empty.
*/
t_list	*ft_list_copy(t_list *list);

/*
** Extracts an element from a singly linked list which matches the reference
** content and returns a pointer to it.
** Comparison is done with a comparison fonction pointer.
*/
t_list	*ft_list_extract(t_list **list, const void *reference, t_gcompare cmp);

/*
** Apply a function to each content of a singly linked list matching the
** reference content. Comparison is done with a comparison fonction pointer.
*/
void	ft_list_foreach_if(t_list *l, const void *reference, t_gcompare cmp,
		t_gfunction function);

/*
** Apply a function to each content of a singly linked list.
*/
void	ft_list_foreach(t_list *l, t_gfunction function);

/*
** Insert an element in a sorted singly linked list.
** The inserted element may be NULL.
** Comparison is done with a comparison fonction pointer.
** Returns a pointer to the inserted element.
*/
t_list	*ft_list_insert(t_list **list, t_list *element, t_gcompare cmp);

/*
** Returns the last element if it exists.
*/
t_list	*ft_list_last(t_list *l);

/*
** Merge sublist to list at the given position.
** If the position is larger than the list size, sublist will be added at the
** end of list.
** The inserted element may be NULL.
** Returns a pointer to the new list.
*/
t_list	*ft_list_merge_at(t_list *list, t_list *sublist, size_t position);

/*
** Merge two lists.
** Returns a pointer at the beginning of the new list.
*/
t_list	*ft_list_merge(t_list *l1, t_list *l2);

/*
** Creates a new element with malloc.
** Returns NULL on error.
*/
t_list	*ft_list_new(void *content);

/*
** Destroy the first element from a singly linked list if it exists.
** Returns its content.
*/
void	*ft_list_pop(t_list **list);

/*
** Remove the first element of the list without deleting it in memory.
** Returns the element, or NULL if the list is empty.
*/
t_list	*ft_list_popl(t_list **list);

/*
** Display the contents of the singly linked list to given file descriptor.
** The print function is called to display the content of each item.
*/
void	ft_list_print_fd(t_list *list, t_gprint_fd print_fd, int fd);

/*
** Display the contents of the singly linked list on standard output.
** The print function is called to display the content of each item.
*/
void	ft_list_print(t_list *list, t_gprint print);

/*
** Add an element at the end of a singly linked list.
** The inserted element may be NULL.
** Returns a pointer to the inserted element.
*/
t_list	*ft_list_push_back(t_list **list, t_list *element);

/*
** Add an element at the beginning of a singly linked list.
** The inserted element may be NULL.
** Returns a pointer to the inserted element.
*/
t_list	*ft_list_push(t_list **list, t_list *element);

/*
** Removes every elements matching the reference content from a singly linked
** list. Comparison is done with a comparison fonction pointer.
** The function pointer del can be NULL.
*/
void	ft_list_remove_if(t_list **list, const void *reference, t_gcompare cmp,
		t_gfunction del);

/*
** Removes the first element matching the reference content from a singly linked
** list.
** Returns its content.
*/
void	*ft_list_remove_one(t_list **list, const void *reference);

/*
** Reverse the order of items in the singly linked list.
** Returns a pointer to the start of the singly linked list.
*/
t_list	*ft_list_rev(t_list *list);

/*
** Search an element from a singly linked list which matches the reference
** content and returns a pointer to it.
** Comparison is done with a comparison fonction pointer.
** Returns NULL if not found.
*/
t_list	*ft_list_search(t_list *list, const void *reference, t_gcompare cmp);

/*
** Returns the size of a singly linked list.
*/
size_t	ft_list_size(t_list *l);

/*
** Sort a singly linked list using the quick sort algorithm.
** Comparison is done with a comparison fonction pointer.
*/
void	ft_list_sort(t_list **list, t_gcompare cmp);

/*
** Allocates and returns a singly linked list of strings obtained by splitting s
** using all characters from set as delimiters.
** If the given set is empty, all spaces are delimiters by default.
** If insufficient memory is available or s is empty, NULL is returned.
*/
t_list	*ft_list_split(const char *s, const char *set);

/*
** Exchanges the contents of l1 with those of l2 if not NULL.
*/
void	ft_list_swap(t_list *l1, t_list *l2);

/*
** Allocates sufficient memory to store the content pointer of each of the
** elements of  the list in an array.
** Returns a NULL terminated array of pointers or NULL if insufficient memory
** is available.
*/
void	**ft_list_to_array(t_list *l);

#endif
