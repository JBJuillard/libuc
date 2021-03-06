/*
** fifo_map.c
**
** fifo_map function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2017/03/09 by Juillard Jean-Baptiste
** Updated: 2018/03/21 by Juillard Jean-Baptiste
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
	while (1)
	{
		if ((tmp = (mfifo_t *)malloc(sizeof(mfifo_t))) == (mfifo_t *)(NULL))
		{
			mfifo_purge(&map);
			errno = ENOMEM;
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
			break ;
		ptr = ptr->next;
	}
	return (map);
}
