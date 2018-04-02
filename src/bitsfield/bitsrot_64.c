/*
** bistrot_64.c
**
** bitsrot_64 function of Undefined-C library
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

uint64_t	bitsrot_64(uint64_t qword, int pos)
{
	register uint64_t	qw;
	register int		p;

	if (qword > UINT64_MAX || pos < -64 || pos > 64)
	{
		errno = EINVAL;
		return (0);
	}
	errno = 0;
	qw ^= qw;
	if (!pos || pos == -64 || pos == 64)
		return (qword);
	p = ((pos < 0) ? (-pos) : (pos));
	if (pos < 0)
		qw = (qword >> p) | (qword << (64 - p));
	else
		qw = (qword >> (64 - p)) | (qword << p);
	return (qw);
}
