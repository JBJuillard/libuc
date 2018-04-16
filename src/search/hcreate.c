/*
** hcreate.c
**
** hcreate, hsearch and hdestroy functions of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/04/06 by Juillard Jean-Baptiste
** Updated: 2018/04/14 by Juillard Jean-Baptiste
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

#include <libuc/search.h>
#include <libuc/errno.h>
#include <stdlib.h>
#include <libuc/string.h>

static ENTRY	*tbl = (ENTRY *)(NULL);
static size_t	stbl = 0;

int		hcreate(size_t nel)
{
	if (!nel)
	{
		errno = EINVAL;
		return (0);
	}
	else if (tbl || stbl)
	{
		errno = EEXIST;
		return (0);
	}
	errno = 0;
	if ((tbl = (ENTRY *)calloc(nel, sizeof(ENTRY))) == (ENTRY *)(NULL))
	{
		if (!errno)
			errno = ENOMEM;
		return (0);
	}
	return (1);
}

ENTRY	*hsearch(ENTRY item, ACTION act)
{
	register size_t	i;
	register size_t	s;
	register ENTRY	*t;
	register void	*k;

	if (!(item.key)
		|| (act != ENTER && act != FIND))
	{
		errno = EINVAL;
		return ((ENTRY *)(NULL));
	}
	errno = 0;
	i ^= i;
	t = tbl;
	s = stbl;
	k = item.key;
	while (i < s && *((char *)((t[i]).key)))
	{
		if (!strcmp(k, (t[i]).key))
			return (&(t[i]));
		++i;
	}
	if (act == FIND)
	{
		errno = ESRCH;
		return ((ENTRY *)(NULL));
	}
	else if (i >= s)
	{
		errno = ENOMEM;
		return ((ENTRY *)(NULL));
	}
	memcpy((void *)(&(t[i])), (void *)(&item), sizeof(ENTRY));
	return (&(t[i]));
}

void	hdestroy(void)
{
	errno = 0;
	free((void *)(tbl));
	tbl = (ENTRY *)(NULL);
	stbl = 0;
	return ;
}
