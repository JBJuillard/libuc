/*
** Units tests mfifo_pop function for Undefined-C library
**
** Created: 03/16/2017 by Juillard Jean-Baptiste
** Updated: 03/16/2017 by Juillard Jean-Baptiste
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
	int			returnNULLptr;
}				test_t;

int	ut_mfifo_pop_interface(int N)
{
	fifo_t			*que;
	mfifo_t			*mque;
	mfifo_t			**mptr;
	void			**ret;
	int				i;
	int				j;
	int				err;
	static test_t	ut_list[2] = {	{ 0, EINVAL, 1 },
									{ 1, 0, 0 }	};

	i = 0;
	err = 0xFF;
	while (i < 2)
	{
		if ((que = (fifo_t *)_gen_sclst(1, N, 1)) == (fifo_t *)(NULL)
			|| (mque = fifo_map(&que)) == (mfifo_t *)(NULL))
		{
			if (que)
				fifo_purge(&que, &_ofree);
			return (errno);
		}
		fifo_purge(&que, &_ofree);
		if ((ut_list[i]).mque)
			mptr = &mque;
		else
			mptr = (mfifo_t **)(NULL);
		j = 0;
		while (j < N)
		{
			errno = 0;
			ret = mfifo_pop(mptr);
			if (errno != (ut_list[i]).err
				|| (!ret && !((ut_list[i]).returnNULLptr))
				|| (ret && (ut_list[i]).returnNULLptr))
			{
				mfifo_purge(&mque);
				return (err);
			}
			j++;
		}
		mfifo_purge(&mque);
		i++;
		err--;
	}
	return (0);
}

int	ut_mfifo_pop_memchk(int N)
{
	fifo_t	*que;
	mfifo_t	*mque;

	if ((que = (fifo_t *)_gen_sclst(1, N, 1)) == (fifo_t *)(NULL)
		|| (mque = fifo_map(&que)) == (mfifo_t *)(NULL))
	{
		if (que)
			fifo_purge(&que, &_ofree);
		return (errno);
	}
	fifo_purge(&que, &_ofree);
	while (mque && N-- > 0)
	{
		if (!mfifo_pop(&mque) || errno)
		{
			mfifo_purge(&mque);
			if (errno)
				return (errno);
			return (0xFF);
		}
	}
	return (0);
}

int	ut_mfifo_pop_timeout(int N)
{
	return (ut_mfifo_pop_memchk(N));
}
