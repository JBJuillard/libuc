/*
** Units tests of slst_rdiff function for Undefined-C library
**
** Created: 17/01/2017 by Juillard Jean-Baptiste
** Updated: 02/03/2017 by Juillard Jean-Baptiste
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
	int					lst1;
	int					diff1;
	int					NULLdiff1;
	int					lst2;
	int					diff2;
	int					NULLdiff2;
	void				*f;
	int					err;
	unsigned long long	ret;
}						test_t;

int	ut_slst_rdiff_interface(int N)
{
	slst_t				*lst1;
	slst_t				**lptr1;
	mslst_t				*diff1;
	slst_t				*lst2;
	slst_t				**lptr2;
	mslst_t				*diff2;
	unsigned long long	ret;
	int					err;
	int					i;
	static test_t		ut_list[10] = {	{0,1,1,1,1,1,((void *)(&_ocmp)),EINVAL,0},
										{1,1,0,1,1,1,((void *)(&_ocmp)),EINVAL,0},
										{1,1,1,0,1,1,((void *)(&_ocmp)),EINVAL,0},
										{1,1,1,1,1,0,((void *)(&_ocmp)),EINVAL,0},
										{1,1,0,1,1,1,((void *)(&_ocmp)),EINVAL,0},
										{1,1,1,1,1,0,((void *)(&_ocmp)),EINVAL,0},
										{1,1,1,1,1,1,NULL,EINVAL,0},
										{1,0,1,1,1,1,((void *)(&_ocmp)),EINVAL,0},
										{1,1,1,1,0,1,((void *)(&_ocmp)),EINVAL,0},
										{1,1,1,1,1,1,((void *)(&_ocmp)),0,0}};

	i = 0;
	err = 0xFF;
	(ut_list[9]).ret = (unsigned long long)(N) + 1ULL;
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
		diff1 = ((ut_list[i]).NULLdiff1 ? (mslst_t *)(NULL) : (mslst_t *)(0xFFFFFFFF));
		diff2 = ((ut_list[i]).NULLdiff2 ? (mslst_t *)(NULL) : (mslst_t *)(0xFFFFFFFF));
		errno = 0;
		ret = slst_rdiff(lptr1,
					    ((ut_list[i]).diff1 ? &diff1 : (mslst_t **)(NULL)),
						lptr2,
					    ((ut_list[i]).diff2 ? &diff2 : (mslst_t **)(NULL)),
						(int (*)(const void *, const size_t, const void *, const size_t))((ut_list[i]).f));
		if (errno != (ut_list[i]).err
			|| (ret != (ut_list[i]).ret))
		{
			if ((ut_list[i]).NULLdiff1)
				mslst_purge(&diff1);
			if ((ut_list[i]).NULLdiff2)
				mslst_purge(&diff2);
			slst_purge(&lst1, &_ofree);
			slst_purge(&lst2, &_ofree);
			return (err);
		}
		if ((ut_list[i]).NULLdiff1)
			mslst_purge(&diff1);
		if ((ut_list[i]).NULLdiff2)
			mslst_purge(&diff2);
		slst_purge(&lst1, &_ofree);
		slst_purge(&lst2, &_ofree);
		i++;
		err--;
	}
	return (0);
}

int	ut_slst_rdiff_memchk(int N)
{
	slst_t	*lst1;
	mslst_t	*mlst1;
	slst_t	*lst2;
	mslst_t	*mlst2;
	size_t	ret;

	errno = 0;
	if ((lst1 = _gen_slst(0, N, 1)) == (slst_t *)(NULL)
		|| (lst2 = _gen_slst(0, (N - 1), 1)) == (slst_t *)(NULL))
	{
		if (lst1)
			slst_purge(&lst1, &_ofree);
		return (errno);
	}
	mlst1 = (mslst_t *)(NULL);
	mlst2 = (mslst_t *)(NULL);
	if ((ret = slst_rdiff(&lst1, &mlst1, &lst2, &mlst2, &_ocmp)) != (unsigned long long)(N + 1) || errno)
	{
		mslst_purge(&mlst1);
		mslst_purge(&mlst2);
		slst_purge(&lst1, &_ofree);
		slst_purge(&lst2, &_ofree);
		if (errno)
			return (errno);
		return (0xFF);
	}
	mslst_purge(&mlst1);
	mslst_purge(&mlst2);
	slst_purge(&lst1, &_ofree);
	slst_purge(&lst2, &_ofree);
	return (0);
}

int	ut_slst_rdiff_timeout(int N)
{
	return (ut_slst_rdiff_memchk(N));
}
