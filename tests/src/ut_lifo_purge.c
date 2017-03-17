/*
** Units tests of lifo_purge function for Undefined-C library
**
** Created: 03/10/2017 by Juillard Jean-Baptiste
** Updated: 03/10/2017 by Juillard Jean-Baptiste
**
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU General Public License as
** published by the Free Software Foundation; either version 3, or
** (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
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

typedef struct	test_s
{
	int			stk;
	void		*f;
	int			err;
}				test_t;


int	ut_lifo_purge_interface(int N)
{
	lifo_t			*stk;
	lifo_t			**sptr;
	lifo_t			*elm;
	int				err;
	int				i;
	static test_t	ut_list[3] = {	{ 0, ((void *)(&_ofree)), EINVAL },
									{ 1, NULL, EINVAL },
									{ 1, ((void *)(&_ofree)), 0 }};

	i = 0;
	err = 0xFF;
	while (i < 3)
	{
		if ((stk = (lifo_t *)_gen_slst(1, N, 1)) == (lifo_t *)(NULL))
			return (errno);
		if ((ut_list[i]).stk)
			sptr = &stk;
		else
			sptr = (lifo_t **)(NULL);
		errno = 0;
		lifo_purge(sptr, (void (*)(void *, size_t))((ut_list[i]).f));
		if (errno != (ut_list[i]).err || (ut_list[i]).err == EINVAL)
		{
			while (stk)
			{
				elm = stk;
				stk = stk->next;
				if (elm->key)
					free(elm->key);
				free((void *)(elm));
			}
			if (errno != (ut_list[i]).err)
				return (err);
		}
		i++;
		err--;
	}
	return (0);
}

int	ut_lifo_purge_memchk(int N)
{
	lifo_t	*stk;

	if ((stk = (lifo_t*)_gen_slst(1, N, 1)) == (lifo_t *)(NULL))
		return (errno);
	errno = 0;
	lifo_purge(&stk, &_ofree);
	if (errno)
		return (errno);
	return (0);
}

int	ut_lifo_purge_timeout(int N)
{
	return (ut_lifo_purge_memchk(N));
}
