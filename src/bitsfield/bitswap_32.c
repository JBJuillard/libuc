/*
** bitswap_32.c
**
** bitswap_32 function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/03/31 by Juillard Jean-Baptiste
** Updated: 2018/03/31 by Juillard Jean-Baptiste
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

uint32_t	bitswap_32(uint32_t dword)
{
	if (dword > UINT32_MAX)
	{
		errno = EINVAL;
		return (0);
	}
	errno = 0;
	dword = ((dword & 0xffff0000) >> 16) | ((dword & 0x0000ffff) << 16);
	dword = ((dword & 0xff00ff00) >> 8) | ((dword & 0x00ff00ff) << 8);
	dword = ((dword & 0xf0f0f0f0) >> 4) | ((dword & 0x0f0f0f0f) << 4);
	dword = ((dword & 0xcccccccc) >> 2) | ((dword & 0x33333333) << 2);
	dword = ((dword & 0xaaaaaaaa) >> 1) | ((dword & 0x55555555) << 1);
	return (dword);
}
