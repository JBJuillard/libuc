/*
** Units tests of slst_cmp function for Undefined-C library
**
** Created: 17/01/2017 by Juillard Jean-Baptiste
** Updated: 02/03/2017 by Juillard Jean-Baptiste
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
	int			lst1;
	int			ptr1;
	int			NULLptr1;
	int			lst2;
	int			ptr2;
	int			NULLptr2;
	void		*f;
	int			err;
	int			ret;
}				test_t;


int	ut_slst_cmp_interface(int N)
{
	slst_t			*lst1;
	slst_t			**lptr1;
	slst_t			*ptr1;
	slst_t			*lst2;
	slst_t			**lptr2;
	slst_t			*ptr2;
	int				ret;
	int				err;
	int				i;
	static test_t	ut_list[10] = {	{0,1,1,1,1,1,((void *)(&_ocmp)),EINVAL,0},
									{1,1,0,1,1,1,((void *)(&_ocmp)),EINVAL,0},
									{1,1,1,0,1,1,((void *)(&_ocmp)),EINVAL,0},
									{1,1,1,1,1,0,((void *)(&_ocmp)),EINVAL,0},
									{1,1,0,1,1,1,((void *)(&_ocmp)),EINVAL,0},
									{1,1,1,1,1,0,((void *)(&_ocmp)),EINVAL,0},
									{1,1,1,1,1,1,NULL,EINVAL,0},
									{1,0,1,1,1,1,((void *)(&_ocmp)),0,1},
									{1,1,1,1,0,1,((void *)(&_ocmp)),0,1},
									{1,1,1,1,1,1,((void *)(&_ocmp)),0,1}};

	i = 0;
	err = 0xFF;
	while (i < 10)
	{
		if ((lst1 = _gen_slst(0, N, 1)) == (slst_t *)(NULL)
			|| (lst2 = _gen_slst(0, (N - 1), 1)) == (slst_t *)(NULL))
		{
			if (lst1)
				slst_purge(&lst1, &_ofree);
			return (errno);
		}
		if ((ut_list[i]).lst1)
			lptr1 = &lst1;
		else
			lptr1 = (slst_t **)(NULL);
		if ((ut_list[i]).lst2)
			lptr2 = &lst2;
		else
			lptr2 = (slst_t **)(NULL);
		ptr1 = ((ut_list[i]).NULLptr1 ? (slst_t *)(NULL) : (slst_t *)(0xFFFFFFFF));
		ptr2 = ((ut_list[i]).NULLptr2 ? (slst_t *)(NULL) : (slst_t *)(0xFFFFFFFF));
		errno = 0;
		ret = slst_cmp(	lptr1,
					    ((ut_list[i]).ptr1 ? &ptr1 : (slst_t **)(NULL)),
						lptr2,
					    ((ut_list[i]).ptr2 ? &ptr2 : (slst_t **)(NULL)),
						(int (*)(const void *, const size_t, const void *, const size_t))((ut_list[i]).f));
		if (errno != (ut_list[i]).err
			|| (ret != (ut_list[i]).ret))
		{
			slst_purge(&lst1, &_ofree);
			slst_purge(&lst2, &_ofree);
			return (err);
		}
		slst_purge(&lst1, &_ofree);
		slst_purge(&lst2, &_ofree);
		i++;
		err--;
	}
	return (0);
}

int	ut_slst_cmp_memchk(int N)
{
	slst_t	*lst1;
	slst_t	*lst2;
	int		ret;

	errno = 0;
	if ((lst1 = _gen_slst(0, N, 1)) == (slst_t *)(NULL)
		|| (lst2 = _gen_slst(0, N, 1)) == (slst_t *)(NULL))
	{
		if (lst1)
			slst_purge(&lst1, &_ofree);
		return (errno);
	}
	if ((ret = slst_cmp(&lst1, (slst_t **)(NULL), &lst2, (slst_t **)(NULL), &_ocmp)) || errno)
	{
		slst_purge(&lst1, &_ofree);
		slst_purge(&lst2, &_ofree);
		if (errno)
			return (errno);
		return (0xFF);
	}
	slst_purge(&lst1, &_ofree);
	slst_purge(&lst2, &_ofree);
	return (0);
}

int	ut_slst_cmp_timeout(int N)
{
	return (ut_slst_cmp_memchk(N));
}
