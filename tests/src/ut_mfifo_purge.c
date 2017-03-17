/*
** Units tests of mfifo_purge function for Undefined-C library
**
** Created: 03/11/2017 by Juillard Jean-Baptiste
** Updated: 03/11/2017 by Juillard Jean-Baptiste
**
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU General Public License as
** published by the Free Software Foundation; either version 3, or
** (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
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
#include <stdint.h>
#include "stdlst.h"
#include "test.h"

typedef struct	test_s
{
	int			mque;
	int			err;
}				test_t;

int	ut_mfifo_purge_interface(int N)
{
	fifo_t			*que;
	mfifo_t			*mque;
	mfifo_t			**qptr;
	int				err;
	int				i;
	static test_t	ut_list[2] = {	{ 0, EINVAL },
									{ 1, 0 }};

	i = 0;
	err = 0xFF;
	que = (fifo_t *)(NULL);
	while (i < 2)
	{
		if ((que = (fifo_t *)_gen_sclst(1, N, 1)) == (fifo_t *)(NULL)
			|| (mque = fifo_map(&que)) == (mfifo_t *)(NULL))
		{
			if (que)
				fifo_purge(&que, &_ofree);
			return (errno);
		}
		if ((ut_list[i]).mque)
			qptr = &mque;
		else
			qptr = (mfifo_t **)(NULL);
		errno = 0;
		mfifo_purge(qptr);
		if (errno != (ut_list[i]).err)
		{
			while (mque)
			{
				qptr = (mfifo_t **)(mque->next);
				if (mque->next == mque)  
					mque = (mfifo_t *)(NULL);
				else
					mque->next = ((mfifo_t *)(qptr))->next;
				free((void *)(qptr));
			}
			fifo_purge(&que, &_ofree);
			if (errno != (ut_list[i]).err)
				return (err);
		}
		if ((ut_list[i]).err == EINVAL)
			mfifo_purge(&mque);
		fifo_purge(&que, &_ofree);
		i++;
		err--;
	}
	return (0);
}

int	ut_mfifo_purge_memchk(int N)
{
	fifo_t	*que;
	mfifo_t	*mque;

	que = (fifo_t *)(NULL);
	if ((que = (fifo_t *)_gen_sclst(1, N, 1)) == (fifo_t *)(NULL)
		|| (mque = fifo_map(&que)) == (mfifo_t *)(NULL))
	{
		fifo_purge(&que, &_ofree);
		return (errno);
	}
	errno = 0;
	mfifo_purge(&mque);
	fifo_purge(&que, &_ofree);
	if (errno)
		return (errno);
	return (0);
}

int	ut_mfifo_purge_timeout(int N)
{
	return (ut_mfifo_purge_memchk(N));
}
