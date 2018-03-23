/*
** slst_qckrsrt.c
**
** slst_qckrsrt function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2017/03/08 by Juillard Jean-Baptiste
** Updated: 2018/03/14 by Juillard Jean-Baptiste
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
#include <stdlib.h>
#include "stdlst.h"

slst_t	*slst_qckrsrt(slst_t **lst, int (*fcmp)(const void *, const size_t,
												const void *, const size_t))
{
	register slst_t	*ptr;
	register slst_t	**addr;
	auto slst_t		*lst2;
	register slst_t	**addr2;
	register slst_t	*pivot;

	errno = 0;
	if (!lst || !fcmp)
	{
		errno = EINVAL;
		return ((slst_t *)(NULL));
	}
	else if (!*lst)
		return ((slst_t *)(NULL));
	pivot = *lst;
	*lst = (slst_t *)(NULL);
	lst2 = (slst_t *)(NULL);
	ptr = pivot->next;
	pivot->next = (slst_t *)(NULL);
	addr = lst;
	addr2 = &lst2;
	while (ptr)
	{
		if ((*fcmp)((const void *)(pivot->key), (const size_t)(pivot->size),
					(const void *)(ptr->key), (const size_t)(ptr->size)) < 0)
		{
			*addr = ptr;
			addr = &(ptr->next);
		}
		else
		{
			*addr2 = ptr;
			addr2 = &(ptr->next);
		}
		ptr = ptr->next;
	}
	*addr = pivot;
	*addr2 = (slst_t *)(NULL);
	slst_qcksrt(lst, fcmp);
	slst_qcksrt(&lst2, fcmp);
	return (slst_cat(lst, &lst2));
}
