/*
** Units tests mlifo_pop function for Undefined-C library
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
	int			mstk;
	int			err;
	int			returnNULLptr;
}				test_t;

int	ut_mlifo_pop_interface(int N)
{
	lifo_t			*stk;
	mlifo_t			*mstk;
	mlifo_t			**mptr;
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
		if ((stk = (lifo_t *)_gen_slst(1, N, 1)) == (lifo_t *)(NULL)
			|| (mstk = lifo_map(&stk)) == (mlifo_t *)(NULL))
		{
			if (stk)
				lifo_purge(&stk, &_ofree);
			return (errno);
		}
		lifo_purge(&stk, &_ofree);
		if ((ut_list[i]).mstk)
			mptr = &mstk;
		else
			mptr = (mlifo_t **)(NULL);
		j = 0;
		while (j < N)
		{
			errno = 0;
			ret = mlifo_pop(mptr);
			if (errno != (ut_list[i]).err
				|| (!ret && !((ut_list[i]).returnNULLptr))
				|| (ret && (ut_list[i]).returnNULLptr))
			{
				mlifo_purge(&mstk);
				return (err);
			}
			j++;
		}
		mlifo_purge(&mstk);
		i++;
		err--;
	}
	return (0);
}

int	ut_mlifo_pop_memchk(int N)
{
	lifo_t	*stk;
	mlifo_t	*mstk;

	if ((stk = (lifo_t *)_gen_slst(1, N, 1)) == (lifo_t *)(NULL)
		|| (mstk = lifo_map(&stk)) == (mlifo_t *)(NULL))
	{
		if (stk)
			lifo_purge(&stk, &_ofree);
		return (errno);
	}
	lifo_purge(&stk, &_ofree);
	while (mstk && N-- > 0)
	{
		if (!mlifo_pop(&mstk) || errno)
		{
			mlifo_purge(&mstk);
			if (errno)
				return (errno);
			return (0xFF);
		}
	}
	return (0);
}

int	ut_mlifo_pop_timeout(int N)
{
	return (ut_mlifo_pop_memchk(N));
}
