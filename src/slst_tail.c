/*
** slst_tail function for Undefined-C library
**
** Created: 02/08/2016 by Juillard Jean-Baptiste
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

#include <stddef.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include "stdlst.h"

mslst_t	*slst_tail(slst_t **lst, size_t n)
{
	register slst_t		*ptr;
	register size_t		i;
	register mslst_t	*tail;
	auto mslst_t		*tmp;
	register int		err;

	errno = 0;
	tail = (mslst_t *)(NULL);
	if (!lst || !n || n > SIZE_MAX)
	{
		errno = EINVAL;
		return ((mslst_t *)(NULL));
	}
	else if (!*lst)
		return ((mslst_t *)(NULL));
	ptr = *lst;
	if ((i = slst_len(lst)) == 0 && errno)
		return ((mslst_t *)(NULL));
	else if (i > n)
	{
		i -= n;
		while (i)
		{
			ptr = ptr->next;
			i--;
		}
	}
	while (n)
	{
		if ((tmp = (mslst_t *)malloc(sizeof(mslst_t))) == (mslst_t *)(NULL))
		{
			if (!errno)
				errno = ENOMEM;
			if (tail)
			{
				tmp = tail->next;
				tail->next = (mslst_t *)(NULL);
				err = errno;
				mslst_purge(&tmp);
				errno = err;
			}
			return (mslst_t *)(NULL);
		}
		tmp->kptr = ((ptr) ? &(ptr->key) : (void **)(NULL));
		tmp->sptr = ((ptr) ? &(ptr->size) : (size_t *)(NULL));
		if (tail)
		{
			tmp->next = tail->next;
			tail->next = tmp;
		}
		else
			tmp->next = tmp;
		tail = tmp;
		if (ptr)
			ptr = ptr->next;
		n--;
	}
	tmp = tail->next;
	tail->next = (mslst_t *)(NULL);
	return (tmp);
}
