/*
** ut_mfifo_push.c
**
** Unit tests for mfifo_push function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2017/03/16 by Juillard Jean-Baptiste
** Updated: 2018/03/13 by Juillard Jean-Baptiste
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
#include <libuc/errno.h>
#include <libuc/stdint.h>
#include <libuc/stdlst.h>
#include "test.h"

typedef struct	test_s
{
	int			mque;
	int			key;
	int			size;
	int			err;
	int			returnNULLptr;
}				test_t;

int	ut_mfifo_push_interface(int N)
{
	mfifo_t			*mque;
	mfifo_t			**mptr;
	void			**k;
	size_t			*z;
	mfifo_t			*ret;
	int				i;
	int				j;
	int				err;
	static test_t	ut_list[4] = {	{ 0, 1, 1, EINVAL, 1 },
									{ 1, 0, 1, 0, 0 },
									{ 1, 1, 0, 0, 0 },
									{ 1, 1, 0, 0, 0 }	};

	i = 0;
	err = 0xFF;
	while (i < 4)
	{
		mque = (mfifo_t *)(NULL);
		if ((ut_list[i]).mque)
			mptr = &mque;
		else
			mptr = (mfifo_t **)(NULL);
		j = 0;
		while (j < N)
		{
			k = (void **)(NULL);
			if ((ut_list[i]).key)
				k = (void **)(0x7fffff);
			z = (size_t *)(NULL);
			if ((ut_list[i]).size)
				z = (size_t *)(0x7fffff);
			errno = 0;
			ret = mfifo_push(mptr, k, z);
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

int	ut_mfifo_push_memchk(int N)
{
	mfifo_t	*mque;
	mfifo_t	*ret;
	int		i;

	i = 0;
	mque = (mfifo_t *)(NULL);
	while (i < N)
	{
		errno = 0;
		if ((ret = mfifo_push(&mque, (void **)(0x7ffffff), (size_t *)(0x7ffffff))) == (mlifo_t *)(NULL) || errno)
		{
			mfifo_purge(&mque);
			if (!errno)
				errno = 0xff;
			return (errno);
		}
		i++;
	}
	mfifo_purge(&mque);
	return (0);
}

int	ut_mfifo_push_timeout(int N)
{
	return (ut_mfifo_push_memchk(N));
}
