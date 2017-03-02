/*
** Units tests of slst_cpy function for Undefined-C library
**
** Created: 02/23/2017 by Juillard Jean-Baptiste
** Updated: 02/23/2017 by Juillard Jean-Baptiste
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

#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include "stdlst.h"
#include "test.h"

typedef struct	test_s
{
	int			lst;
	void		*fcpy;
	int			err;
	int			retNULLptr;
}				test_t;


int	ut_slst_cpy_interface(int N)
{
	slst_t			*lst;
	slst_t			**lptr;
	slst_t			*ret;
	int				err;
	int				i;
	static test_t	ut_list[3] = {	{0,((void *)(&_ocpy)),EINVAL,1},
									{1,NULL,EINVAL,1},
									{1,((void *)(&_ocpy)),0,0}};

	i = 0;
	err = 0xFF;
	while (i < 3)
	{
		if ((lst = _gen_slst(1, N, 1)) == (slst_t *)(NULL))
			return (errno);
		if ((ut_list[i]).lst)
			lptr = &lst;
		else
			lptr = (slst_t **)(NULL);
		errno = 0;
		ret = slst_cpy(lptr, (void *(*)(const void *, size_t))((ut_list[i]).fcpy));
		if (errno != (ut_list[i]).err
			|| (!ret && !(ut_list[i]).retNULLptr)
			|| (ret && (ut_list[i]).retNULLptr))
		{
			if (ret)
				slst_purge(&ret, &_ofree);
			slst_purge(&lst, &_ofree);
			return (err);
		}
		if (ret)
			slst_purge(&ret, &_ofree);
		slst_purge(&lst, &_ofree);
		i++;
		err--;
	}
	return (0);
}

int	ut_slst_cpy_memchk(int N)
{
	slst_t	*lst;
	slst_t	*ret;

	errno = 0;
	if ((lst = _gen_slst(1, N, 1)) == (slst_t *)(NULL))
		return (errno);
	if ((ret = slst_cpy(&lst, (void *(*)(const void *, size_t))(&_ocpy))) == (sclst_t *)(NULL) || errno)
	{
		if (ret)
			slst_purge(&ret, &_ofree);
		slst_purge(&lst, &_ofree);
		if (errno)
			return (errno);
		return (0xFF);
	}
	slst_purge(&ret, &_ofree);
	slst_purge(&lst, &_ofree);
	return (0);
}

int	ut_slst_cpy_timeout(int N)
{
	return (ut_slst_cpy_memchk(N));
}
