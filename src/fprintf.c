/*
** fprintf function for Undefined-C library
**
** Created: 02/24/2018 by Juillard Jean-Baptiste
** Updated: 02/24/2018 by Juillard Jean-Baptiste
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

#define ARGUMENT_MAX			4096
#define CONVERTION_MAXCHAR		4095

#include <libuc/limits.h>
#include <stdlib.h>
#include <stdlst.h>

int	fprintf_parse_arg(const char *fmt, va_list aptr, void **arg)
{
	while (*fmt)
	{
		if (*fmt == '%')
		  ;
		fmt++;
	}
}

int	fprintf(int fd, const char *fmt, ...)
{
	register void		**arg;
	register va_list	aptr;
	register sclst		*str;

	if (fd < 0 || fd > USHRT_MAX || !fmt)
	{
		errno = EINVAL;
		return (0);
	}
	errno ^= errno;
	if ((arg = (void **)calloc(ARGUMENT_MAX, sizeof(void *))) == (void **)(NULL))
		return (0);
	str ^= str;
	va_start(aptr, fmt);
}
