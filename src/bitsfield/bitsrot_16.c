/*
** bistrot_16.c
**
** bitsrot_16 function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/04/01 by Juillard Jean-Baptiste
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

uint16_t	bitsrot_16(uint16_t word, int pos)
{
	register uint16_t	w;
	register int		p;

	if (/*word > UINT16_MAX ||*/ pos < -16 || pos > 16)
	{
		errno = EINVAL;
		return (0);
	}
	errno = 0;
	w ^= w;
	if (!pos || pos == -16 || pos == 16)
		return (word);
	p = ((pos < 0) ? (-pos) : (pos));
	if (pos < 0)
		w = (word >> p) | (word << (16 - p));
	else
		w = (word >> (16 - p)) | (word << p);
	return (w);
}
