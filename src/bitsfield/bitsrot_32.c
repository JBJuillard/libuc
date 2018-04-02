/*
** bistrot_32.c
**
** bitsrot_32 function of Undefined-C library
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

uint32_t	bitsrot_32(uint32_t dword, int pos)
{
	register uint32_t	dw;
	register int		p;

	if (dword > UINT32_MAX || pos < -32 || pos > 32)
	{
		errno = EINVAL;
		return (0);
	}
	errno = 0;
	dw ^= dw;
	if (!pos || pos == -32 || pos == 32)
		return (dword);
	p = ((pos < 0) ? (-pos) : (pos));
	if (pos < 0)
		dw = (dword >> p) | (dword << (32 - p));
	else
		dw = (dword >> (32 - p)) | (dword << p);
	return (dw);
}
