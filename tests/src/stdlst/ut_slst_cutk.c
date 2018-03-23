/*
** ut_slst_cutk.c
**
** Unit tests for slst_cutk function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2017/02/23 by Juillard Jean-Baptiste
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

#include <libuc/stdlib.h>
#include <libuc/stdint.h>
#include <libuc/limits.h>
#include <libuc/stdlst.h>
#include <libuc/errno.h>
#include "test.h"

typedef struct			test_s
{
	int					lst;
	int					key;
	unsigned long long	n;
	void				*f;
	int					err;
	int					returnNULLptr;
}						test_t;


int	ut_slst_cutk_interface(int N)
{
	slst_t			*lst;
	slst_t			**lptr;
	void			*k;
	long long		ll;
	slst_t			*ret;
	int				err;
	int				i;
	static test_t	ut_list[6] = {	{0,1,sizeof(long long),(void *)(&_ocmp),EINVAL,1},
									{1,0,sizeof(long long),(void *)(&_ocmp),EINVAL,1},
									{1,1,0,(void *)(&_ocmp),EINVAL,1},
									{1,1,(SIZE_MAX + 1),(void *)(&_ocmp),EINVAL,1},
									{1,1,sizeof(long long),NULL,EINVAL,1},
									{1,1,sizeof(long long),(void *)(&_ocmp),0,0}};

	err = 0xFF;
	i = 0;
	ll = N / 2;
	while (i < 6)
	{
		if ((lst = _gen_slst(1, N, 1)) == (slst_t *)(NULL))
			return (errno);
		lptr = (((ut_list[i]).lst) ? (&lst) : (slst_t **)(NULL));
		k = (((ut_list[i]).key) ? (&ll) : (NULL));
		errno = 0;
		ret = slst_cutk(lptr,
						k,
						(size_t)((ut_list[i]).n),
						(int (*)(const void *, const size_t,
								 const void *, const size_t))((ut_list[i]).f));
		if (errno != (ut_list[i]).err
			|| (!ret && !(ut_list[i]).returnNULLptr)
			|| (ret && (ut_list[i]).returnNULLptr))
		{
			slst_purge(&lst, &_ofree);
			if (ret)
				slst_purge(&ret, &_ofree);
			return (err);
		}
		slst_purge(&lst, &_ofree);
		if (ret)
			slst_purge(&ret, &_ofree);
		i++;
		err--;
	}
	return (0);
}

int	ut_slst_cutk_memchk(int N)
{
	slst_t		*lst;
	slst_t		*ret;
	long long	k;

	errno = 0;
	k = (long long)(N / 2);
	if ((lst = _gen_slst(1, N, 1)) == (slst_t *)(NULL))
		return (errno);
	if ((ret = slst_cutk(&lst, (const void *)(&k), sizeof(long long), &_ocmp)) == (slst_t *)(NULL) || errno)
	{
		slst_purge(&lst, &_ofree);
		if (ret)
			slst_purge(&ret, &_ofree);
		return (errno);
	}
	slst_purge(&lst, &_ofree);
	slst_purge(&ret, &_ofree);
	return (0);
}

int	ut_slst_cutk_timeout(int N)
{
	return (ut_slst_cutk_memchk(N));
}
