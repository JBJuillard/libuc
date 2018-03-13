/*
** fifo_map function for Undefined-C library
**
** Created: 03/09/2017 by Juillard Jean-Baptiste
** Updated: 2018/03/12 by Juillard Jean-Baptiste
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

#include <libuc/errno.h>
#include <stdlib.h>			/* Dev: a modifier après implantation de malloc */
#include <libuc/stdlst.h>

mfifo_t	*fifo_map(fifo_t **que)
{
	register fifo_t		*ptr;
	auto mfifo_t		*map;
	register mfifo_t	*tmp;
	register int		err;

	errno = 0;
	if (!que)
	{
		errno = EINVAL;
		return ((mfifo_t *)(NULL));
	}
	else if (!*que)
		return ((mfifo_t *)(NULL));
	ptr = (*que)->next;
	map = (mfifo_t*)(NULL);
	while (ptr)
	{
		if ((tmp = (mfifo_t *)malloc(sizeof(mfifo_t))) == (mfifo_t *)(NULL))
		{
			if (!errno)
				errno = ENOMEM;
			err = errno;
			mfifo_purge(&map);
			errno = err;
			return ((mfifo_t *)(NULL));
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
		if (ptr == *que)
			ptr = (fifo_t *)(NULL);
		else
			ptr = ptr->next;
	}
	return (map);
}
