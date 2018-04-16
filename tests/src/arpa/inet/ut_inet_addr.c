/*
** ut_inet_addr.c
**
** Unit tests for inet_addr function of Undefined-C library
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
#include <libuc/netinet/in.h>
#include <libuc/byteswap.h>

typedef struct		test_s
{
	const char		*str;
	uint32_t		ret;
	char			in[4];
	int				err;
}					test_t;

int	ut_inet_addr_interface(int N)
{
	int				err;
	int				i;
	int				j;
	test_t			tdat[3] = {	{(char *)(NULL), INADDR_NONE, {0xff,0xff,0xff,0xff}, EINVAL},
								{"1024.0.0.1", INADDR_NONE, {0xff,0xff,0xff,0xff}, 0},
								{"-1.255.255.255", INADDR_NONE, {0xff,0xff,0xff,0xff}, 0} };
	union
	{
		uint32_t	netlong;
		char		byte[4];
	}				ret;

	i ^= i;
	N = N;
	err = 0xff;
	while (i < 3)
	{
		errno = 0;
		if ((ret.netlong = (uint32_t)inet_addr((tdat[i]).str)) != (tdat[i]).ret
			|| errno != (tdat[i]).err)
			return (err);
		j ^= j;
		while (j < 4)
		{
			if ((tdat[i]).in[j] != ret.byte[j])
				return (err);
			j++;
		}
		err--;
		i++;
	}
	return (0);
}

int	ut_inet_addr_validity(int N)
{
	int				err;
	int				i;
	int				j;
	test_t			tdat[4] = {	{"0.0.0.0", 0, {0x00,0x00,0x00,0x00}, 0},
								{"127.0.0.1", htonl(0x7f000001), {0x7f,0x00,0x00,0x01}, 0},
								{"255.255.255.255", htonl(0xffffffff), {0xff,0xff,0xff,0xff}, 0},
								{"192.168.0.1", htonl(0xc0a80001), {0xc0,0xa8,0x00,0x01}, 0} };
	union
	{
		uint32_t	netlong;
		char		byte[4];
	}				ret;

	i ^= i;
	N = N;
	err = 0xff;
	while (i < 4)
	{
		errno = 0;
		if ((ret.netlong = (uint32_t)inet_addr((tdat[i]).str)) != (tdat[i]).ret
			|| errno != (tdat[i]).err)
			return (err);
		j ^= j;
		while (j < 4)
		{
			if ((tdat[i]).in[j] != ret.byte[j])
				return (err);
			j++;
		}
		err--;
		i++;
	}
	return (0);
}

int	ut_inet_addr_memchk(int N)
{
	uint32_t	i;
	union
	{
		struct in_addr	in;
		uint32_t		nl;
	}					addr;

	i ^= i;
	while (i < (uint32_t)(N))
	{
		addr.nl = htonl(i++);
		inet_addr(inet_ntoa(addr.in));
	}
	return (0);
}

int	ut_inet_addr_timeout(int N)
{
	return(ut_inet_addr_memchk(N));
}
