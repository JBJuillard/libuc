/*
** ut_fifo_pop.c
**
** Unit tests for fifo_pop function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2017/03/10 by Juillard Jean-Baptiste
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

#include <stdlib.h>			/* Dev: a modifier après implantation de free */
#include <libuc/stdint.h>
#include <libuc/stdlst.h>
#include <libuc/errno.h>
#include "test.h"

typedef struct	test_s
{
	int			que;
	int			err;
	int			returnNULLptr;
}				test_t;

int	ut_fifo_pop_interface(int N)
{
	fifo_t			*que;
	fifo_t			**qptr;
	void			*ret;
	int				i;
	int				j;
	int				err;
	static test_t	ut_list[2] = {	{ 0, EINVAL, 1 },
									{ 1, 0, 0 }	};

	i = 0;
	err = 0xFF;
	while (i < 2)
	{
		if ((que = (fifo_t *)_gen_sclst(1, N, 1)) == (fifo_t *)(NULL))
			return (errno);
		if ((ut_list[i]).que)
			qptr = &que;
		else
			qptr = (fifo_t **)(NULL);
		j = 0;
		while (j < N)
		{
			errno = 0;
			ret = fifo_pop(qptr);
			if (errno != (ut_list[i]).err
				|| (!ret && !((ut_list[i]).returnNULLptr))
				|| (ret && (ut_list[i]).returnNULLptr))
			{
				if (ret)
				{
					free(ret);
					fifo_purge(&que, &_ofree);
					return (err);
			    }
			}
			if (ret)
				free(ret);
			j++;
			fifo_purge(&que, &_ofree);
		}
		i++;
		err--;
	}
	return (0);
}

int	ut_fifo_pop_memchk(int N)
{
	fifo_t	*que;
	void	*k;

	if ((que = (fifo_t *)_gen_sclst(1, N, 1)) == (fifo_t *)(NULL))
		return (errno);
	while (que && N-- > 0)
	{
		if (!(k = fifo_pop(&que)) || errno)
		{
			if (k)
				free(k);
			fifo_purge(&que, &_ofree);
			if (errno)
				return (errno);
			return (0xFF);
		}
		free(k);
	}
	return (0);
}

int	ut_fifo_pop_timeout(int N)
{
	return (ut_fifo_pop_memchk(N));
}
