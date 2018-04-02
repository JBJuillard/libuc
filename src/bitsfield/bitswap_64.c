/*
** bitswap_64.c
**
** bitswap_64 function of Undefined-C library
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

uint64_t	bitswap_64(uint64_t qword)
{
	if (qword > UINT64_MAX)
	{
		errno = EINVAL;
		return (0);
	}
	errno = 0;
	qword = ((qword & 0xffffffff00000000) >> 32) | ((qword & 0x00000000ffffffff) << 32);
	qword = ((qword & 0xffff0000ffff0000) >> 16) | ((qword & 0x0000ffff0000ffff) << 16);
	qword = ((qword & 0xff00ff00ff00ff00) >> 8) | ((qword & 0x00ff00ff00ff00ff) << 8);
	qword = ((qword & 0xf0f0f0f0f0f0f0f0) >> 4) | ((qword & 0x0f0f0f0f0f0f0f0f) << 4);
	qword = ((qword & 0xcccccccccccccccc) >> 2) | ((qword & 0x3333333333333333) << 2);
	qword = ((qword & 0xaaaaaaaaaaaaaaaa) >> 1) | ((qword & 0x5555555555555555) << 1);
	return (qword);
}
