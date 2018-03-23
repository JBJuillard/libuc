/*
** ut_slst_keysdup.c
**
** Unit tests for slst_keysdup function of Undefined-C library
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

#include <stdlib.h>			/* Dev: amodifier après implantation de free */
#include <libuc/stdint.h>
#include <libuc/limits.h>
#include <libuc/stdlst.h>
#include <libuc/errno.h>
#include "test.h"

typedef struct	test_s
{
	int			lst;
	void		*sz;
	int			err;
	int			retNULLptr;
}				test_t;


int	ut_slst_keysdup_interface(int N)
{
	slst_t			*lst;
	slst_t			**lptr;
	size_t			sz;
	void			*ret;
	int				err;
	int				i;
	static test_t	ut_list[3] = {	{0,((void *)(1)),EINVAL,1},
									{1,NULL,0,0},
									{1,((void *)(1)),0,0}};

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
		if ((ut_list[i]).sz)
			(ut_list[i]).sz = (void *)(&sz);
		ret = slst_keysdup(lptr, (size_t *)((ut_list[i]).sz));
		if (errno != (ut_list[i]).err
			|| (!ret && !(ut_list[i]).retNULLptr)
			|| (ret && (ut_list[i]).retNULLptr))
		{
			if (ret)
				free(ret);
			slst_purge(&lst, &_ofree);
			return (err);
		}
		if (ret)
			free(ret);
		slst_purge(&lst, &_ofree);
		i++;
		err--;
	}
	return (0);
}

int	ut_slst_keysdup_memchk(int N)
{
	slst_t	*lst;
	void	*ret;

	errno = 0;
	if ((lst = _gen_slst(1, N, 1)) == (slst_t *)(NULL))
		return (errno);
	if ((ret = slst_keysdup(&lst, (size_t *)(NULL))) == (sclst_t *)(NULL) || errno)
	{
		if (ret)
			free(ret);
		slst_purge(&lst, &_ofree);
		if (errno)
			return (errno);
		return (0xFF);
	}
	free(ret);
	slst_purge(&lst, &_ofree);
	return (0);
}

int	ut_slst_keysdup_timeout(int N)
{
	return (ut_slst_keysdup_memchk(N));
}
