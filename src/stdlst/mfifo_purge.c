/*
** mfifo_purge.c
**
** mfifo_purge function of Undefined-C library
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

#include <stdlib.h>			/* Dev: a modifier après implantation de free */
#include <libuc/errno.h>
#include <libuc/stdlst.h>

void	mfifo_purge(mfifo_t **mque)
{
	register mfifo_t	*tmp;
	register mfifo_t	*mq;

	if (!mque)
	{
		errno = EINVAL;
		return ;
	}
	errno = 0;
	mq = *mque;
	*mque = (mfifo_t *)(NULL);
	while (mq)
	{
		tmp = mq->next;
		if (tmp == mq)
			mq = (mfifo_t *)(NULL);
		else
			mq->next = tmp->next;
		tmp->kptr = (void **)(NULL);
		tmp->sptr = (size_t *)(NULL);
		tmp->next = (mfifo_t *)(NULL);
		free((void *)(tmp));
	}
}
