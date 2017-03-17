/*
** Units tests lifo_pop function for Undefined-C library
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

typedef struct			test_s
{
	int					stk;
	int					err;
	int					returnNULLptr;
}						test_t;

int	ut_lifo_pop_interface(int N)
{
	lifo_t			*stk;
	lifo_t			**sptr;
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
		if ((stk = (lifo_t *)_gen_slst(1, N, 1)) == (lifo_t *)(NULL))
			return (errno);
		if ((ut_list[i]).stk)
			sptr = &stk;
		else
			sptr = (lifo_t **)(NULL);
		j = 0;
		while (j < N)
		{
			errno = 0;
			ret = lifo_pop(sptr);
			if (errno != (ut_list[i]).err
				|| (!ret && !((ut_list[i]).returnNULLptr))
				|| (ret && (ut_list[i]).returnNULLptr))
			{
				if (ret)
				{
					free(ret);
					lifo_purge(&stk, &_ofree);
					return (err);
			    }
			}
			if (ret)
				free(ret);
			j++;
			lifo_purge(&stk, &_ofree);
		}
		i++;
		err--;
	}
	return (0);
}

int	ut_lifo_pop_memchk(int N)
{
	lifo_t	*stk;
	void	*k;

	if ((stk = (lifo_t *)_gen_slst(1, N, 1)) == (lifo_t *)(NULL))
		return (errno);
	while (stk && N-- > 0)
	{
		if (!(k = lifo_pop(&stk)) || errno)
		{
			if (k)
				free(k);
			lifo_purge(&stk, &_ofree);
			if (errno)
				return (errno);
			return (0xFF);
		}
		free(k);
	}
	return (0);
}

int	ut_lifo_pop_timeout(int N)
{
	return (ut_lifo_pop_memchk(N));
}
