/*
** Units tests of fifo_purge function for Undefined-C library
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
	int			que;
	void		*f;
	int			err;
}				test_t;


int	ut_fifo_purge_interface(int N)
{
	fifo_t			*que;
	fifo_t			**qptr;
	fifo_t			*elm;
	int				err;
	int				i;
	static test_t	ut_list[3] = {	{ 0, ((void *)(&_ofree)), EINVAL },
									{ 1, NULL, EINVAL },
									{ 1, ((void *)(&_ofree)), 0 }};

	i = 0;
	err = 0xFF;
	while (i < 3)
	{
		if ((que = (fifo_t *)_gen_sclst(1, N, 1)) == (fifo_t *)(NULL))
			return (errno);
		if ((ut_list[i]).que)
			qptr = &que;
		else
			qptr = (fifo_t **)(NULL);
		errno = 0;
		fifo_purge(qptr, (void (*)(void *, size_t))((ut_list[i]).f));
		if (errno != (ut_list[i]).err || (ut_list[i]).err == EINVAL)
		{
			while (que)
			{
				elm = que->next;
				if (que == elm)
					que = (fifo_t*)(NULL);
				else
					que->next = elm->next;
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

int	ut_fifo_purge_memchk(int N)
{
	fifo_t	*que;

	if ((que = (fifo_t*)_gen_sclst(1, N, 1)) == (fifo_t *)(NULL))
		return (errno);
	errno = 0;
	fifo_purge(&que, &_ofree);
	if (errno)
		return (errno);
	return (0);
}

int	ut_fifo_purge_timeout(int N)
{
	return (ut_fifo_purge_memchk(N));
}
