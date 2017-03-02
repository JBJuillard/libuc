/*
** Units tests of slst_tail function for Undefined-C library
**
** Created: 02/08/2017 by Juillard Jean-Baptiste
** Updated: 02/10/2017 by Juillard Jean-Baptiste
**
** This file is a part free software; you can redistribute it and/or
** modify it under the terms of the GNU General Public License as
** published by the Freer Software Foundation; either version 3, or
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

#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include "stdlst.h"
#include "test.h"

typedef struct			test_s
{
	int					lst;
	unsigned long long	n;
	int					err;
	int					returnNULLptr;
}						test_t;

int	ut_slst_tail_interface(int N)
{
	slst_t			*lst;
	slst_t			**lptr;
	mslst_t			*ret;
	int				err;
	int				i;
	static test_t	ut_list[4] = {	{0,10,EINVAL,1},
									{1,0,EINVAL,1},
									{0,(SIZE_MAX + 1),EINVAL,1},
									{1,10,0,0}};

	i = 0;
	err = 0xFF;
	while (i < 4)
	{
		if ((lst = _gen_slst(1, N, 1)) == (slst_t *)(NULL))
			return (errno);
		if ((ut_list[i]).lst)
			lptr = &lst;
		else
			lptr = (slst_t **)(NULL);
		errno = 0;
		ret = slst_tail(lptr, (ut_list[i]).n);
		if (errno != (ut_list[i]).err
			|| (!ret && !(ut_list[i]).returnNULLptr)
			|| (ret && (ut_list[i]).returnNULLptr))
		{
			if (ret)
				mslst_purge(&ret);
			slst_purge(&lst, &_ofree);
			return (err);
		}
		if (ret)
			mslst_purge(&ret);
		slst_purge(&lst, &_ofree);
		i++;
		err--;
	}
	return (0);
}

int	ut_slst_tail_memchk(int N)
{
	slst_t	*lst;
	mslst_t	*ret;

	errno = 0;
	if ((lst = _gen_slst(1, N, 1)) == (slst_t *)(NULL))
		return (errno);
	if (!(ret = slst_tail(&lst, 10)) || errno)
	{
		mslst_purge(&ret);
		slst_purge(&lst, &_ofree);
		if (errno)
			return (errno);
		return (0xFF);
	}
	mslst_purge(&ret);
	slst_purge(&lst, &_ofree);
	return (0);
}

int	ut_slst_tail_timeout(int N)
{
	return (ut_slst_tail_memchk(N));
}
