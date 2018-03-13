/*
** ut_msclst_purge.c
**
** Unit tests for msclst_purge function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2017/01/29 by Juillard Jean-Baptiste
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

#include <stdlib.h>			/* Dev: a modifier après implantation de free */
#include <libuc/stdint.h>
#include <libuc/stdlst.h>
#include "test.h"

typedef struct	test_s
{
	int			mlst;
	int			err;
}				test_t;

int	ut_msclst_purge_interface(int N)
{
	sclst_t			*lst;
	msclst_t		*mlst;
	msclst_t		**mptr;
	int				err;
	int				i;
	static test_t	ut_list[2] = {	{ 0, EINVAL },
									{ 1, 0 }};

	i = 0;
	err = 0xFF;
	lst = (sclst_t *)(NULL);
	while (i < 2)
	{
		if ((lst = _gen_sclst(1, N, 1)) == (sclst_t *)(NULL)
			|| (mlst = sclst_map(&lst)) == (msclst_t *)(NULL))
		{
			if (lst)
				sclst_purge(&lst, &_ofree);
			return (errno);
		}
		if ((ut_list[i]).mlst)
			mptr = &mlst;
		else
			mptr = (msclst_t **)(NULL);
		errno = 0;
		msclst_purge(mptr);
		if (errno != (ut_list[i]).err)
		{
			while (mlst)
			{
				mptr = (msclst_t **)(mlst->next);
				if (mlst->next == mlst)  
					mlst = (msclst_t *)(NULL);
				else
					mlst->next = ((msclst_t *)(mptr))->next;
				free((void *)(mptr));
			}
			sclst_purge(&lst, &_ofree);
			if (errno != (ut_list[i]).err)
				return (err);
		}
		if ((ut_list[i]).err == EINVAL)
			msclst_purge(&mlst);
		sclst_purge(&lst, &_ofree);
		i++;
		err--;
	}
	return (0);
}

int	ut_msclst_purge_memchk(int N)
{
	sclst_t		*lst;
	msclst_t	*mlst;

	lst = (sclst_t *)(NULL);
	if ((lst = _gen_sclst(1, N, 1)) == (sclst_t *)(NULL)
		|| (mlst = sclst_map(&lst)) == (msclst_t *)(NULL))
	{
		if (lst)
			sclst_purge(&lst, &_ofree);
		return (errno);
	}
	errno = 0;
	msclst_purge(&mlst);
	sclst_purge(&lst, &_ofree);
	if (errno)
		return (errno);
	return (0);
}

int	ut_msclst_purge_timeout(int N)
{
	return (ut_msclst_purge_memchk(N));
}
