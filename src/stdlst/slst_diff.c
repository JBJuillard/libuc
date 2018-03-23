/*
** slst_diff.c
**
** slst_diff function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2016/12/28 by Juillard Jean-Baptiste
** Updated: 2018/03/14 by Juillard Jean-Baptiste
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

#include <libuc/stddef.h>
#include <libuc/errno.h>
#include <stdlib.h>			/* Dev: a modifier après implantation de malloc et de free */
#include <libuc/stdint.h>
#include <libuc/stdlst.h>

size_t	slst_diff(slst_t **lst1,
					mslst_t **diff1,
					slst_t **lst2,
					mslst_t **diff2,
					int (*fcmp)(const void *, const size_t,
								const void *, const size_t))
{
	register slst_t		*tmp1;
	register slst_t		*tmp2;
	register mslst_t	**d1;
	register mslst_t	**d2;
	register size_t		ret;
	register int		err;

	if (!lst1 || !diff1 || *diff1 || !lst2 || !diff2 || *diff2 || !fcmp)
	{
		errno = EINVAL;
		return (0);
	}
	errno = 0;
	tmp1 = *lst1;
	tmp2 = *lst2;
	d1 = diff1;
	d2 = diff2;
	ret = 0;
	while ((tmp1 || tmp2) && !errno)
	{
		if ((tmp1 && tmp2
				&& (*fcmp)(	(const void *)(tmp1->key),
							(const size_t)(tmp1->size),
							(const void *)(tmp2->key),
							(const size_t)(tmp2->size))
				&& !errno)
			|| (!tmp1 && tmp2)
			|| (tmp1 && !tmp2))
		{
			if ((*diff1 = (mslst_t *)malloc(sizeof(mslst_t)))
					== (mslst_t *)(NULL)
				|| (*diff2 = (mslst_t *)malloc(sizeof(mslst_t)))
					== (mslst_t *)(NULL))
			{
				if (!errno)
					errno = ENOMEM;
				err = errno;
				if (*diff1)
					free((void *)(diff1));
				mslst_purge(d1);
				mslst_purge(d2);
				errno = err;
				return (0);
			}
			(*diff1)->kptr = ((tmp1) ? &(tmp1->key) : (void **)(NULL));
			(*diff1)->sptr = ((tmp1) ? &(tmp1->size) : (size_t *)(NULL));
			(*diff1)->next = (mslst_t *)(NULL);
			diff1 = &((*diff1)->next);
			(*diff2)->kptr = ((tmp2) ? &(tmp2->key) : (void **)(NULL));
			(*diff2)->sptr = ((tmp2) ? &(tmp2->size) : (size_t *)(NULL));
			(*diff2)->next = (mslst_t *)(NULL);
			diff2 = &((*diff2)->next);
			if (ret == SIZE_MAX)
			{
			    err = EOVERFLOW;
				mslst_purge(d1);
				mslst_purge(d2);
				errno = err;
				return (0);
			}
			ret++;
		}
		if (tmp1)
			tmp1 = tmp1->next;
		if (tmp2)
			tmp2 = tmp2->next;
		
	}
	return (ret);
}
