/*
** sclst_newelm function for Undefined-C library
**
** Created: 03/08/2017 by Juillard Jean-Baptiste
** Updated: 2018/03/12 by Juillard Jean-Baptiste
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
#include <stdlib.h>			/* Dev: a modifier après implantation de malloc */
#include <libuc/stdlst.h>

sclst_t	*sclst_newelm(void)
{
	register sclst_t	*ptr;

	ptr = (sclst_t *)(NULL);
	errno = 0;
	if ((ptr = (sclst_t *)malloc(sizeof(sclst_t))) == (sclst_t *)(NULL))
	{
		if (!errno)
			errno = ENOMEM;
		return ((sclst_t *)(NULL));
	}
	ptr->key = NULL;
	ptr->size = 0;
	ptr->next = (sclst_t *)(NULL);
	return (ptr);
}
