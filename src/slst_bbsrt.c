/*
** slst_bubblesrt function for Undefined-C library
**
** Created: 12/28/2016 by Juillard Jean-Baptiste
** Updated: 03/08/2017 by Juillard Jean-Baptiste
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

#include	<errno.h>
#include	<stdlib.h>
#include	"stdlst.h"

slst_t	*slst_bubblesrt(slst_t **lst,
						int (*fcmp)(const void *, const size_t,
									const void *, const size_t))
{
	register slst_t	*ptr;
	register slst_t	**addr;
	register size_t	len;
	register size_t	cnt;
	register int	mod;

	if (!lst || !fcmp)
	{
		errno = EINVAL;
		return ((slst_t *)(NULL));
	}
	errno = 0;
	if ((len = slst_length(lst)) > 1)
	{
		mod = 1;
		while (--len && mod)
		{
			mod = 0;
			ptr = *lst;
			addr = lst;
			cnt = len;
			while (cnt--)
			{
				if ((*fcmp)((const void *)(ptr->key), (const size_t)(ptr->size),
							(const void *)((ptr->next)->key),
							(const size_t)((ptr->next)->size)) > 0)
				{
					*addr = ptr->next;
					ptr->next = (*addr)->next;
					(*addr)->next = ptr;
					ptr = *addr;
					mod = 1;
				}
				addr = &(ptr->next);
				ptr = ptr->next;
			}
		}
	}
	return (*lst);
}
