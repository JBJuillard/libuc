/*
** ut_fifo_map.c
**
** Unit tests for fifo_map function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2017/03/10 by Juillard Jean-Baptiste
** Updated: 2018/03/22 by Juillard Jean-Baptiste
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

#include <libuc/stdlib.h>
#include <libuc/stdint.h>
#include <libuc/stdlst.h>
#include <libuc/errno.h>
#include "test.h"

typedef struct	test_s
{
	int			que;
	int			err;
	int			returnNULLptr;
}				test_t;


int	ut_fifo_map_interface(int N)
{
	fifo_t			*que;
	fifo_t			**qptr;
	mfifo_t			*mque;
	int				err;
	int				i;
	static test_t	ut_list[2] = {	{ 0, EINVAL, 1 },
									{ 1, 0, 0 }};

	i = 0;
	err = 0xFF;
	que = (fifo_t *)(NULL);
	while (i < 2)
	{
		if ((que = (fifo_t *)_gen_sclst(1, N, 1)) == (fifo_t *)(NULL))
			return (errno);
		if ((ut_list[i]).que)
			qptr = &que;
		else
			qptr = (lifo_t **)(NULL);
		errno = 0;
		mque = fifo_map(qptr);
		if (errno != (ut_list[i]).err
			||(!mque && !(ut_list[i]).returnNULLptr)
			||(mque && (ut_list[i]).returnNULLptr))
		{
			mfifo_purge(&mque);
			fifo_purge(&que, &_ofree);
			if (errno != (ut_list[i]).err)
				return (err);
		}
		mfifo_purge(&mque);
		fifo_purge(&que, &_ofree);
		i++;
		err--;
	}
	return (0);
}

int	ut_fifo_map_memchk(int N)
{
	fifo_t	*que;
	mfifo_t	*mque;

	que = (fifo_t *)(NULL);
	errno = 0;
	if ((que = (fifo_t *)_gen_sclst(1, N, 1)) == (fifo_t *)(NULL)
		|| (mque = fifo_map(&que)) == (mfifo_t *)(NULL))
	{
		fifo_purge(&que, &_ofree);
		return (errno);
	}
	mfifo_purge(&mque);
	fifo_purge(&que, &_ofree);
	if (errno)
		return (errno);
	return (0);
}

int	ut_fifo_map_timeout(int N)
{
	return (ut_fifo_map_memchk(N));
}
