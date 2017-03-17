/*
** slst_nsrtk function for Undefined-C library
**
** Created: 12/28/2016 by Juillard Jean-Baptiste
** Updated: 03/15/2017 by Juillard Jean-Baptiste
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
#include <stdint.h>
#include "stdlst.h"

slst_t	*slst_nsrtk(slst_t **lst,
					slst_t *elm,
					const void *key,
					const size_t size,
					int (*fcmp)(const void *, const size_t,
								const void *, const size_t))
{
	register slst_t	*tmp;
	register slst_t	**addr;

	if (!lst || !elm || !elm->key || !elm->size || elm->size > SIZE_MAX
		|| elm->next || !key || !size || !fcmp)
	{
		errno = EINVAL;
		return ((slst_t *)(NULL));
	}
	errno = 0;
	tmp = *lst;
	addr = lst;
	while (tmp
			&& (*fcmp)(key, size,
						(const void *)(tmp->key), (const size_t)(tmp->size)))
	{
		addr = &(tmp->next);
		tmp = tmp->next;
	}
	if (!tmp)
	{
		errno = ERANGE;
		return ((slst_t *)(NULL));
	}
	elm->next = tmp;
	*addr = elm;
	return (elm);
}
