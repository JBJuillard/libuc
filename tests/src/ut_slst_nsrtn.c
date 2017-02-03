/*
** Units tests of slst_nsrtn function for Undefined-C library
**
** Created: 01/17/2017 by Juillard Jean-Baptiste
** Updated: 02/01/2017 by Juillard Jean-Baptiste
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
#include <errno.h>
#include <stdint.h>
#include "stdlst.h"
#include "test.h"

typedef struct			test_s
{
	int					lst;
	int					elm;
	unsigned long long	n;
	int					key;
	int					size;
	int					next;
	int					err;
	int					returnNULLptr;
}						test_t;

int	ut_slst_nsrtn_interface(int N)
{
	slst_t			*lst;
	slst_t			**lptr;
	slst_t			*elm;
	slst_t			*ret;
	int				err;
	int				i;
	int				j;
	static test_t	ut_list[9] = {	{0,1,1,1,sizeof(long long),0,EINVAL,1},
									{1,0,1,1,sizeof(long long),0,EINVAL,1},
									{1,1,0,1,sizeof(long long),0,EINVAL,1},
									{1,1,(SIZE_MAX + 1),1,sizeof(long long),0,EINVAL,1},
									{1,1,1,0,sizeof(long long),0,EINVAL,1},
									{1,1,1,1,0,0,EINVAL,1},
									{1,1,1,1,(SIZE_MAX + 1),0,EINVAL,1},
									{1,1,1,1,sizeof(long long),1,EINVAL,1},
									{1,1,1,1,sizeof(long long),0,0,0}};

	i = 0;
	err = 0xFF;
	while (i < 9)
	{
		lst = (slst_t *)(NULL);
		if ((ut_list[i]).lst)
			lptr = &lst;
		else
			lptr = (slst_t **)(NULL);
		j = 0;
		while (j < N)
		{
			errno = 0;
		  	if ((ut_list[i]).elm)
			{
				if ((elm = (slst_t *)malloc(sizeof(slst_t))) == (slst_t *)(NULL))
				{
					slst_purge(&lst, &_ofree);
					return (errno);
				}
			}
			else
				elm = (slst_t *)(NULL);
		  	if (elm && (ut_list[i]).key)
			{
				if ((elm->key = malloc(sizeof(long long))) == NULL)
				{
					free((void *)(elm));
					slst_purge(&lst, &_ofree);
					return (errno);
				}
				*((long long *)(elm->key)) = (long long)(j);
			}
			else if (elm)
				elm->key = NULL;
			if (elm && (ut_list[i]).size)
				elm->size = sizeof(long long);
			else if (elm)
				elm->size = 0;
			if (elm && (ut_list[i]).next)
				elm->next = (slst_t *)(0xFFFFFFFF);
			else if (elm)
				elm->next = (slst_t *)(NULL);
			ret = slst_nsrtn(lptr, elm, (ut_list[i]).n);
			if (errno != (ut_list[i]).err
				|| (!ret && !((ut_list[i]).returnNULLptr))
				|| (ret && (ut_list[i]).returnNULLptr))
			{
				if (elm)
					free((void *)(elm));
				slst_purge(&lst, &_ofree);
				return (err);
			}
			if (elm && (ut_list[i]).err ==  EINVAL)
			{
				if (elm->key)
					free(elm->key);
				free((void *)(elm));
			}
			j++;
		}
		slst_purge(&lst, &_ofree);
		i++;
		err--;
	}
	return (0);
}

int	ut_slst_nsrtn_memchk(int N)
{
	slst_t	*lst;
	slst_t	*tmp;
	int		i;
	int		err;

	i = 0;
	lst = (slst_t *)(NULL);
	while (i < N)
	{
		if ((tmp = (slst_t *)malloc(sizeof(slst_t))) == (slst_t *)(NULL)
			|| (tmp->key = malloc(sizeof(int))) == NULL)
		{
			if (tmp)
				free((void *)(tmp));
			slst_purge(&lst, &_ofree);
			errno = ENOMEM;
			break ;
		}
		*((int *)(tmp->key)) = i;
		tmp->size = sizeof(int);
		tmp->next = (slst_t *)(NULL);
		errno = 0;
		if (slst_nsrtn(&lst, tmp, 1) == (slst_t *)(NULL) || errno)
		{
			free((void *)(tmp));
			err = errno;
			slst_purge(&lst, &_ofree);
			errno = err;
			return (errno);
		}
		i++;
	}
	slst_purge(&lst, &_ofree);
	return (0);
}

int	ut_slst_nsrtn_timeout(int N)
{
	return (ut_slst_nsrtn_memchk(N));
}
