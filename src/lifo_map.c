/*
** lifo_map function for Undefined-C library
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

mlifo_t	*lifo_map(lifo_t **stk)
{
	register lifo_t		*ptr;
	auto mlifo_t		*map;
	register mlifo_t	*tmp;
	register int		err;

	errno = 0;
	if (!stk)
	{
		errno = EINVAL;
		return ((mlifo_t *)(NULL));
	}
	else if (!*stk)
		return ((mlifo_t *)(NULL));
	ptr = *stk;
	map = (mlifo_t*)(NULL);
	while (ptr)
	{
		if ((tmp = (mlifo_t *)malloc(sizeof(mlifo_t))) == (mlifo_t *)(NULL))
		{
			if (!errno)
				errno = ENOMEM;
			err = errno;
			mlifo_purge(&map);
			errno = err;
			return ((mlifo_t *)(NULL));
		}
		tmp->kptr = &(ptr->key);
		tmp->sptr = &(ptr->size);
		if (map)
		{
			tmp->next = map->next;
			map->next = tmp;
		}
		else
			tmp->next = tmp;
		map = tmp;
		ptr = ptr->next;
	}
	if (!map)
		return ((mlifo_t *)(NULL));
	tmp = map;
	map = map->next;
	tmp->next = (mlifo_t *)(NULL);
	return (map);
}