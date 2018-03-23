/*
** ut_slst_delk.c
**
** Unit tests for slst_delk function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2017/01/17 by Juillard Jean-Baptiste
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
#include <libuc/stdlst.h>
#include <libuc/errno.h>
#include "test.h"


typedef struct			test_s
{
	int					lst;
	int					key;
	unsigned long long	size;
	void				*fcmp;
	void				*fdel;
	int					err;
}						test_t;


int	ut_slst_delk_interface(int N)
{
	slst_t			*lst;
	slst_t			**lptr;
	void			*key;
	size_t			size;
	int				err;
	int				i;
	int				j;
	static test_t	ut_list[8] = {	{ 0, 1, sizeof(long long), ((void *)(&_ocmp)), ((void *)(&_ofree)), EINVAL },
									{ 1, 0, sizeof(long long), ((void *)(&_ocmp)), ((void *)(&_ofree)), EINVAL },
									{ 1, 1, 0, ((void *)(&_ocmp)), ((void *)(&_ofree)), EINVAL },
									{ 1, 1, (SIZE_MAX + 1), ((void *)(&_ocmp)), ((void *)(&_ofree)), EINVAL },
									{ 1, 1, sizeof(long long), NULL, ((void *)(&_ofree)), EINVAL },
									{ 1, 1, sizeof(long long), ((void *)(&_ocmp)), NULL, EINVAL },
									{ 1, 1, sizeof(long long), ((void *)(&_ocmp)), ((void *)(&_ofree)), 0 },
									{ 1, 1, sizeof(long long), ((void *)(&_ocmp)), ((void *)(&_ofree)), 0 }};

	i = 0;
	err = 0xFF;
	while (i < 8)
	{
		if ((lst = _gen_slst(1, N, 1)) == (slst_t *)(NULL))
			return (errno);
		if ((ut_list[i]).lst)
			lptr = &lst;
		else
			lptr = (slst_t **)(NULL);
		j = 0;
		while (lst && j++ < N)
		{
			errno = 0;
			if ((ut_list[i]).key)
				key = lst->key;
			else
				key = (slst_t *)(NULL);
			size = (ut_list[i]).size;
			slst_delk(lptr, key, size, (int (*)(const void *, const size_t, const void *, const size_t))((ut_list[i]).fcmp), (void (*)(void *, size_t))((ut_list[i]).fdel));
			if (errno != (ut_list[i]).err)
			{
				slst_purge(lptr, &_ofree);
				return (err);
			}
			else if ((ut_list[i]).err == EINVAL)
			{
				slst_purge(lptr, &_ofree);
				break ;
			}
		}
		i++;
		err--;
	}
	return (0);
}

int	ut_slst_delk_memchk(int N)
{
	slst_t	*lst;

	errno = 0;
	if ((lst = _gen_slst(1, N, 1)) == (slst_t *)(NULL))
		return (errno);
	while (lst && N-- >= 0)
	{
		slst_delk(&lst, lst->key, lst->size, &_ocmp, &_ofree);
		if (errno)
		{
			slst_purge(&lst, &_ofree);
			return (errno);
		}
	}
	return (0);
}

int	ut_slst_delk_timeout(int N)
{
	return (ut_slst_delk_memchk(N));
}
