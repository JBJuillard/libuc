/*
** mfifo_push.c
**
** mfifo_push function of Undefined-C library
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

#include <libuc/stddef.h>
#include <libuc/errno.h>
#include <stdlib.h>			/* Dev: a modifier après implantaon de malloc */
#include <libuc/stdlst.h>

mfifo_t	*mfifo_push(mfifo_t **mque, void **kptr, size_t *sptr)
{
	register mfifo_t	*tmp;

	if (!mque || !kptr || !sptr)
	{
		errno = EINVAL;
		return ((mfifo_t *)(NULL));
	}
	errno = 0;
	if ((tmp = (mfifo_t *)malloc(sizeof(mfifo_t))) == (mfifo_t *)(NULL))
	{
		if (!errno)
			errno = ENOMEM;
		return ((mfifo_t *)(NULL));
	}
	tmp->kptr = kptr;
	tmp->sptr = sptr;
	if (*mque)
	{
		tmp->next = (*mque)->next;
		(*mque)->next = tmp;
	}
	else
		tmp->next = tmp;
	*mque = tmp;
	return (tmp);
}
