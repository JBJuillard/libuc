/*
** slst2fifo function for Undefined-C library
**
** Created: 12/28/2016 by Juillard Jean-Baptiste
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

fifo_t	*slst2fifo(slst_t **lst)
{
	register fifo_t	*que;

	errno = 0;
	if (!lst)
	{
		errno = EINVAL;
		return ((fifo_t *)(NULL));
	}
	else if (!*lst)
		return ((fifo_t *)(NULL));
	que = (fifo_t *)(*lst);
	while (que->next)
		que = que->next;
	que->next = (fifo_t *)(*lst);
	*lst = (slst_t *)(NULL);
	return (que);
}
