/*
** sclst_put_back.c
**
** sclst_put_back function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2017/03/08 by Juillard Jean-Baptiste
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

#include <libuc/errno.h>
#include <libuc/stdint.h>
#include <libuc/stdlib.h>
#include <libuc/stdlst.h>

sclst_t	*sclst_put_back(sclst_t **lst, void *key, size_t size)
{
	if (!lst || !key || !size || size > SIZE_MAX)
	{
		errno = EINVAL;
		return ((sclst_t *)(NULL));
	}
	errno = 0;
	return (sclst_put(lst, key, size));
}
