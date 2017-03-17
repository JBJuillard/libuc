/*
** sclst_head function for Undefined-C library
**
** Created: 03/08/2017 by Juillard Jean-Baptiste
** Updated: 03/16/2017 by Juillard Jean-Baptiste
**
** This file is a part free software; you can redistribute it and/or
** modify it under the terms of the GNU General Public License as
** published by the Free Software Foundation; either version 3, or
** (at your option) any later version.
** 
** There is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with this program; see the file LICENSE.  If not, write to
** the Free Software Foundation, Inc., 51 Franklin Street, Fifth
** Floor, Boston, MA 02110-1301, USA.
*/


#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include "stdlst.h"


msclst_t	*sclst_head(sclst_t **lst, size_t n)
{
	register sclst_t	*ptr;
	register size_t		i;
	auto msclst_t		*head;
	register msclst_t	*tmp;

	errno = 0;
	if (!lst || !n || n > SIZE_MAX)
	{
		errno = EINVAL;
		return ((msclst_t *)(NULL));
	}
	else if (!*lst)
		return ((msclst_t *)(NULL));
	ptr = (*lst)->next;
	i = 1;
	head = (msclst_t *)(NULL);
	while (i <= n)
	{
		if ((tmp = (msclst_t *)malloc(sizeof(msclst_t))) == (msclst_t *)(NULL))
		{
			msclst_purge(&head);
			return ((msclst_t *)(NULL));
		}
		tmp->kptr = (ptr) ? &(ptr->key) : (void **)(NULL);
		tmp->sptr = (ptr) ? &(ptr->size) : (size_t *)(NULL);
		if (head)
		{
			tmp->next = head->next;
			head->next = tmp;
		}
		else
			tmp->next = tmp;
		head = tmp;
		if (ptr == *lst)
			ptr = (sclst_t*)(NULL);
		else
			ptr = ptr->next;
		i++;
	}
	return (head);
}
