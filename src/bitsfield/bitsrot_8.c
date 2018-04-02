/*
** bistrot_8.c
**
** bitsrot_8 function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/03/31 by Juillard Jean-Baptiste
** Updated: 2018/04/02 by Juillard Jean-Baptiste
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

#include <libuc/stdint.h>
#include <libuc/errno.h>

uint8_t	bitsrot_8(uint8_t byte, int pos)
{
	register uint8_t	b;
	register int		p;

	if (/*byte > UINT8_MAX ||*/ pos < -8 || pos > 8)
	{
		errno = EINVAL;
		return (0);
	}
	errno = 0;
	b ^= b;
	if (!pos || pos == 8 || pos == -8)
		return (byte);
	p = ((pos < 0) ? (-pos) : (pos));
	if (pos < 0)
		b = (byte >> p) | (byte << (8 - p));
	else
		b = (byte >> (8 - p)) | (byte << p);
	return (b);
}
