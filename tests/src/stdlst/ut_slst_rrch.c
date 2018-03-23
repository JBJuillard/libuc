/*
** ut_slst_rrch.c
**
** Unit tests for slst_rrch function of Undefined-C library
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

#include <stdlib.h>			/* Dev: a modifier après implantation de malloc et de free */
#include <libuc/stdint.h>
#include <libuc/stdlst.h>
#include <libuc/errno.h>
#include "test.h"

typedef struct			test_s
{
	int					lst;
	int					key;
	unsigned long long	size;
	void				*f;
	int					err;
	int					returnNULLptr;
}						test_t;

int	ut_slst_rrch_interface(int N)
{
	slst_t			*lst;
	slst_t			**lptr;
	void			*key;
	slst_t			*ret;
	int				err;
	int				i;
	static test_t	ut_list[6] = {	{0,1,sizeof(long long),((void *)(&_ocmp)),EINVAL,1},
									{1,0,sizeof(long long),((void *)(&_ocmp)),EINVAL,1},
									{1,1,0,((void *)(&_ocmp)),EINVAL,1},
									{1,1,(SIZE_MAX + 1),((void *)(&_ocmp)),EINVAL,1},
									{1,1,sizeof(long long),NULL,EINVAL,1},
									{1,1,sizeof(long long),((void *)(&_ocmp)),0,0}};

	i = 0;
	err = 0xFF;
	while (i < 6)
	{
		if ((lst = _gen_slst(0, N, 1)) == (slst_t *)(NULL))
			return (errno);
		if ((ut_list[i]).lst)
			lptr = &lst;
		else
			lptr = (slst_t **)(NULL);
	    if ((ut_list[i]).key)
		{
			if ((key = malloc(sizeof(long long))) == NULL)
			{
				slst_purge(&lst, &_ofree);
				return (errno);
			}
			*((long long *)(key)) = N / 2;
		}
		else
			key = NULL;
		errno = 0;
		ret = slst_rrch(lptr, (const void *)(key), (const size_t)((ut_list[i]).size), (int (*)(const void *, const size_t, const void *, const size_t))((ut_list[i]).f));
		if (errno != (ut_list[i]).err
			|| (!ret && !(ut_list[i]).returnNULLptr)
			|| (ret && (ut_list[i]).returnNULLptr)
			|| (ret && *((long long *)(ret->key)) != *((long long *)(key))))
		{
			if (key)
				free(key);
			slst_purge(&lst, &_ofree);
			return (err);
		}
		if (key)
			free(key);
		slst_purge(&lst, &_ofree);
		i++;
		err--;
	}
	return (0);
}

int	ut_slst_rrch_memchk(int N)
{
	slst_t	*lst;
	slst_t	*tmp;
	void	*i;

	errno = 0;
	if ((lst = _gen_slst(0, N, 1)) == (slst_t *)(NULL)
		|| (i = malloc(sizeof(long long))) == NULL)
	{
		if (lst)
			slst_purge(&lst, &_ofree);
		return (errno);
	}
	*((long long *)(i)) = N / 2;
	if (!(tmp = slst_rrch(&lst, i, sizeof(long long), _ocmp)) || errno || *((long long *)(tmp->key)) != (long long)(N / 2))
	{
		slst_purge(&lst, &_ofree);
		free(i);
		if (errno)
			return (errno);
		return (0xFF);
	}
	slst_purge(&lst, &_ofree);
	free(i);
	return (0);
}

int	ut_slst_rrch_timeout(int N)
{
	return (ut_slst_rrch_memchk(N));
}
