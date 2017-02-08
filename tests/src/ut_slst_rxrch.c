/*
** Units tests of slst_rxrch function for Undefined-C library
**
** Created: 17/01/2017 by Juillard Jean-Baptiste
** Updated: 02/05/2017 by Juillard Jean-Baptiste
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
#include "stdlst.h"
#include "test.h"

typedef struct			test_s
{
	int					lst;
	int					key;
	unsigned long long	size;
	int					match;
	void				*f;
	int					err;
	size_t				ret;
}						test_t;


int	ut_slst_rxrch_interface(int N)
{
	slst_t			*lst;
	slst_t			**lptr;
	void			*key;
	mslst_t			*mlst;
	mslst_t			**mptr;
	size_t			ret;
	int				err;
	int				i;
	static test_t	ut_list[7] = {	{0,1,sizeof(long long),1,((void *)(&_ocmp)),EINVAL,0},
									{1,0,sizeof(long long),1,((void *)(&_ocmp)),EINVAL,0},
									{1,1,0,1,((void *)(&_ocmp)),EINVAL,0},
									{1,1,(SIZE_MAX + 1),1,((void *)(&_ocmp)),EINVAL,0},
									{1,1,sizeof(long long),1,NULL,EINVAL,0},
									{1,1,sizeof(long long),0,((void *)(&_ocmp)),EINVAL,0},
									{1,1,sizeof(long long),1,((void *)(&_ocmp)),0,1}};

	i = 0;
	err = 0xFF;
	while (i < 7)
	{
		if ((lst = _gen_slst(0, N, 1)) == (slst_t *)(NULL))
			return (errno);
		mlst = (mslst_t *)(NULL);
		if ((ut_list[i]).lst)
			lptr = &lst;
		else
			lptr = (slst_t **)(NULL);
		if ((ut_list[i]).match)
			mptr = &mlst;
		else
			mptr = (mslst_t **)(NULL);
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
		ret = slst_rxrch(lptr, (const void *)(key), (const size_t)((ut_list[i]).size), mptr, (int (*)(const void *, const size_t, const void *, const size_t))((ut_list[i]).f));
		if (errno != (ut_list[i]).err
			|| (!ret && (ut_list[i]).ret)
			|| (ret && !(ut_list[i]).ret))
		{
			if (key)
				free(key);
			mslst_purge(&mlst);
			slst_purge(&lst, &_ofree);
			return (err);
		}
		if (key)
			free(key);
		mslst_purge(&mlst);
		slst_purge(&lst, &_ofree);
		i++;
		err--;
	}
	return (0);
}

int	ut_slst_rxrch_memchk(int N)
{
	slst_t	*lst;
	mslst_t	*match;
	size_t	s;
	void	*i;

	errno = 0;
	if ((lst = _gen_slst(0, N, 1)) == (slst_t *)(NULL)
		|| (i = malloc(sizeof(long long))) == NULL)
	{
		if (lst)
			slst_purge(&lst, &_ofree);
		return (errno);
	}
	*((long long *)(i)) = N;
	match = (mslst_t*)(NULL);
	if (!(s = slst_rxrch(&lst, i, sizeof(long long), &match, _ocmp)) || errno)
	{
		mslst_purge(&match);
		slst_purge(&lst, &_ofree);
		free(i);
		if (errno)
			return (errno);
		return (0xFF);
	}
	mslst_purge(&match);
	slst_purge(&lst, &_ofree);
	free(i);
	return (0);
}

int	ut_slst_rxrch_timeout(int N)
{
	return (ut_slst_rxrch_memchk(N));
}
