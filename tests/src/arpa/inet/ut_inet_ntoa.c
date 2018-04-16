/*
** ut_inet_ntoa.c
**
** Unit tests for inet_ntoa function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/04/14 by Juillard Jean-Baptiste
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

#include <libuc/errno.h>
#include <libuc/arpa/inet.h>
#include <libuc/byteswap.h>
#include <libuc/stdint.h>
#include <libuc/string.h>
#include "test.h"

typedef struct		test_s
{
	struct in_addr	addr;
	char			*str;
	int				err;
}					test_t;

int	ut_inet_ntoa_interface(int N)
{
	return (ut_inet_ntoa_validity(N));
}

int	ut_inet_ntoa_validity(int N)
{
	int				err;
	int				i;
	test_t			tdat[4] = {	{{htonl(0x00000000)}, "0.0.0.0", 0},
								{{htonl(0x7f000001)}, "127.0.0.1", 0},
								{{htonl(0xffffffff)}, "255.255.255.255", 0},
								{{htonl(0xc0a80001)}, "192.168.0.1", 0} };
	char			*ret;

	i ^= i;
	N = N;
	err = 0xff;
	while (i < 4)
	{
		errno = 0;
		if (!(ret = inet_ntoa((tdat[i]).addr))
			|| errno != (tdat[i]).err
			|| strcmp((tdat[i]).str, ret))
			return (err);
		err--;
		i++;
	}
	return (0);
}

int	ut_inet_ntoa_memchk(int N)
{
	uint32_t			i;
	union
	{
		uint32_t		nl;
		struct in_addr	in;
	}					addr;

	i ^= i;
	while (i < (uint32_t)(N))
	{
		addr.nl = htonl(i++);
		inet_ntoa(addr.in);
	}
	return (0);
}

int	ut_inet_ntoa_timeout(int N)
{
	return(ut_inet_ntoa_memchk(N));
}
