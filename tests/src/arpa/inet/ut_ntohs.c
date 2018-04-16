/*
** ut_ntohs.c
**
** Unit tests for ntohs function of Undefined-C library
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

#include <libuc/arpa/inet.h>
#include <libuc/stdint.h>
#include <libuc/errno.h>

#define NTOHS_INPUT0					0x1234
#define NTOHS_INPUT1					0xfedc
#define NTOHS_INPUT2					0x1248
#define NTOHS_INPUT3					0xc3a5
#define NTOHS_OUTPUT0					0x12, 0x34
#define NTOHS_OUTPUT1					0xfe, 0xdc
#define NTOHS_OUTPUT2					0x12, 0x48
#define NTOHS_OUTPUT3					0xc3, 0xa5

typedef struct		test_s
{
	uint16_t		ns;
	char			ret[2];
	int				err;
}					test_t;

int	ut_ntohs_interface(int N)
{
	int				i;
	int				j;
	int				err;
	union
	{
		uint16_t	n;
		char		b[2];
	}				r;
	test_t			tdat[4] = { {NTOHS_INPUT0, {NTOHS_OUTPUT0}, 0},
								{NTOHS_INPUT1, {NTOHS_OUTPUT1}, 0},
								{NTOHS_INPUT2, {NTOHS_OUTPUT2}, 0},
								{NTOHS_INPUT3, {NTOHS_OUTPUT3}, 0} };

	errno = 0;
	err = 0xff;
	i ^= i;
	N = N;
	while (i < 4)
	{
		r.n = ntohs((tdat[i]).ns);
		if (errno)
			return (err);
		j ^= j;
		while (j < 2)
		{
			if (r.b[j] != (tdat[i]).ret[j])
				return (err);
			++j;
		}
		++i;
		--err;
	}
	return (0);
}

int	ut_ntohs_validity(int N)
{
	return (ut_ntohs_interface(N));
}

int	ut_ntohs_memchk(int N)
{
	uint16_t	i;

	i ^= i;
	while (i < (uint16_t)(N))
		ntohs(i++);
	return (0);
}

int	ut_ntohs_timeout(int N)
{
	return (ut_ntohs_memchk(N));
}
