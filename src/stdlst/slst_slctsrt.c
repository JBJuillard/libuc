/*
** slst_slctsrt function for Undefined-C library
**
** Created: 03/09/2017 by Juillard Jean-Baptiste
** Updated: 03/09/2017 by Juillard Jean-Baptiste
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

slst_t	*slst_slctsrt(slst_t **lst, int (*fcmp)(const void *, const size_t,
												const void *, const size_t))
{
	register slst_t	**addr;
	register slst_t	**ptr;
	register slst_t	**smaller;
	register slst_t	*tmp;

	if (!lst || ! fcmp)
	{
		errno = EINVAL;
		return ((slst_t *)(NULL));
	}
	else if (!*lst)
		return ((slst_t *)(NULL));
	addr = lst;
	while (*addr)
	{
		smaller = addr;
		ptr = &((*addr)->next);
		while (*ptr)
		{
			if ((*fcmp)((const void *)((*smaller)->key),
						(const size_t)((*smaller)->size),
						(const void *)((*ptr)->key),
						(const size_t)((*ptr)->size)) > 0)
				smaller = ptr;
			ptr = &((*ptr)->next);
		}
		if (*smaller != *addr)
		{
			tmp = (*addr)->next;
			(*addr)->next = (*smaller)->next;
			(*smaller)->next = tmp;
			tmp = *addr;
			*addr = *smaller;
			*smaller = tmp;
		}
		addr = &((*addr)->next);
	}
	return (*lst);
}
