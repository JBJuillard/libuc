/*
** ut_slst_delelm function for Undefined-C library
**
** Created: 01/17/2017 by Juillard Jean-Baptiste
** Updated: 01/31/2017 by Juillard Jean-Baptiste
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


typedef struct	test_s
{
	int			elm;
	void		*f;
	int			err;
}				test_t;


int	ut_slst_delelm_interface(int N)
{
	slst_t			*elm;
	int				err;
	int				i;
	int				j;
	static test_t	ut_list[4] = {	{ 0, ((void *)(&_ofree)), EINVAL },
									{ 1, NULL, EINVAL },
									{ 1, ((void *)(&_ofree)), 0 },
									{ 1, ((void *)(&_ofree)), 0 }};

	i = 0;
	err = 0xFF;
	while (i < 4)
	{
		j = 0;
		while (j < N)
		{
			errno = 0;
			if ((ut_list[i]).elm)
			{
				if ((elm = slst_newelm()) == (slst_t *)(NULL)
					|| (elm->key = malloc(sizeof(int))) == NULL)
				{
					if (elm)
						free((void *)(elm));
					break ;
				}
				*((int *)(elm->key)) = j;
				elm->size = sizeof(int);
				elm->next = (slst_t *)(NULL);
			}
			else
				elm = (slst_t *)(NULL);
			slst_delelm(elm, (void (*)(void *, size_t))((ut_list[i]).f));
			if (errno != (ut_list[i]).err)
				return (err);
			if ((ut_list[i]).err == EINVAL)
			{
				if (errno != (ut_list[i]).err)
					free((void *)(elm));
			}
			j++;
		}
		i++;
		err--;
	}
	return (0);
}

int	ut_slst_delelm_memchk(int N)
{
	int		i;
	slst_t	*ptr;

	i = 0;
	errno = 0;
	while (i < N)
	{
		if ((ptr = (slst_t *)malloc(sizeof(slst_t))) == (slst_t *)(NULL)
			  || (ptr->key = malloc(sizeof(int))) == NULL)
		{
			if (ptr)
				free((void *)(ptr));
			return (errno);
		}
		*((int *)(ptr->key)) = i;
		ptr->size = sizeof(int);
		ptr->next = (slst_t *)(NULL);
		slst_delelm(ptr, &_ofree);
		if (errno)
		{
			if (ptr)
				free((void *)(ptr));
			return (errno);
		}
		i++;
	}
	return (0);
}

int	ut_slst_delelm_timeout(int N)
{
	return (ut_slst_delelm_memchk(N));
}
