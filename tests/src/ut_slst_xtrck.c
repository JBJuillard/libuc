/*
** ut_slst_xtrck function for Undefined-C library
**
** Created: 17/01/2017 by Juillard Jean-Baptiste
** Updated: 02/03/2017 by Juillard Jean-Baptiste
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
	void				*f;
	int					err;
	int					returnNULLptr;
}						test_t;


int	ut_slst_xtrck_interface(int N)
{
	slst_t			*lst;
	slst_t			**lptr;
	void			*key;
	slst_t			*ret;
	int				err;
	int				i;
	int				j;
	/*
	**									lst	key	size				f					err		returnNULLptr
	*/
	static test_t	ut_list[6] = {	{	0,	1,	sizeof(long long),	((void *)(&_ocmp)),	EINVAL,	1 },
									{	1,	0,	sizeof(long long),	((void *)(&_ocmp)), EINVAL,	1 },
									{	1,	1,	0,					((void *)(&_ocmp)), EINVAL,	1 },
									{	1,	1,	(SIZE_MAX + 1),		((void *)(&_ocmp)), EINVAL,	1 },
									{	1,	1,	sizeof(long long),	NULL,				EINVAL,	1 },
									{	1,	1,	sizeof(long long),	((void *)(&_ocmp)), 0,		0 }};

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
		j = 0;
		while (j < N)
		{
			if ((ut_list[i]).key)
				key = lst->key;
			else
				key = NULL;
			errno = 0;
			ret = slst_xtrck(lptr, key, (ut_list[i]).size, (int (*)(const void *, const size_t, const void *, const size_t))((ut_list[i]).f));
			if (errno != (ut_list[i]).err
				|| (!ret && !(ut_list[i]).returnNULLptr)
				|| (ret && (ut_list[i]).returnNULLptr))
			{
				if (ret)
				{
					free(ret->key);
					free((void *)(ret));
				}
				slst_purge(&lst, &_ofree);
				return (err);
			}
			if (ret)
			{
				free(ret->key);
				free((void *)(ret));
			}
			j++;
		}
		slst_purge(&lst, &_ofree);
		i++;
		err--;
	}
	return (0);
}

int	ut_slst_xtrck_memchk(int N)
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
	while (lst && N >= 0)
	{
		*((long long *)(i)) = N--;
		if (!(tmp = slst_xtrck(&lst, i, sizeof(long long), _ocmp)) || errno)
		{
			slst_purge(&lst, &_ofree);
			free(i);
			if (tmp)
			{
				free(tmp->key);
				free(tmp);
			}
			if (errno)
				return (errno);
			return (0xFF);
		}
		free(tmp->key);
		free(tmp);
	}
	free(i);
	return (0);
}

int	ut_slst_xtrck_timeout(int N)
{
	return (ut_slst_xtrck_memchk(N));
}
