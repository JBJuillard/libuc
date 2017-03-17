/*
** lifo_purge function for Undefined-C library
**
** Created: 12/28/2016 by Juillard Jean-Baptiste
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

#include <stdlib.h>
#include <errno.h>
#include "stdlst.h"

void	lifo_purge(lifo_t **stk, void (*fdel)(void *, size_t))
{
	register lifo_t	*tmp;

	if (!stk || !fdel)
	{
		errno = EINVAL;
		return ;
	}
	errno = 0;
	while (*stk)
	{
		tmp = *stk;
		(*fdel)(tmp->key, tmp->size);
		if (errno)
			return ;
		*stk = tmp->next;
		tmp->key = NULL;
		tmp->size = 0;
		tmp->next = (lifo_t *)(NULL);
		free((void *)(tmp));
	}
}
