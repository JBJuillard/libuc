/*
** ut_llabs.c
**
** Unit tests for llabs function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/03/23 by Juillard Jean-Baptiste
** Updated: 2018/04/04 by Juillard Jean-Baptiste
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
#include <libuc/stdlib.h>
#include <libuc/limits.h>

typedef struct		err_s
{
	long long int	n;
	long long int	ret;
	int				err;
}					err_t;

int	ut_llabs_interface(int N)
{
	int		i;
	int		error;
	err_t	tdat[2] = {	{LLONG_MIN, LLONG_MIN, ERANGE},
						{LLONG_MAX, LLONG_MAX, 0}};

	error = 0xFF;
	i = 0;
	N = N;
	while (i < 2)
	{
		if (llabs((tdat[i]).n) != (tdat[i]).ret
			|| errno != (tdat[i]).err)
			return (error);
		i++;
		error--;
	}
	return (0);
}

int	ut_llabs_validity(int N)
{
	unsigned long long int	i;

	i = 0;
	N = N;
	while (i <= LLONG_MAX)
		if (i && llabs(-i) != (long long )(i))
			return (1);
	if (llabs(0))
		return (1);
	i = 0;
	while (i <= LLONG_MAX)
		if (i && llabs(i) != (long long )(i))
			return (1);
	return (0);
}

int	ut_llabs_memchk(int N)
{
	unsigned int	i;

	i = 0;
	while (i < (unsigned int)(N))
		llabs(i++);
	return (0);
}

int	ut_llabs_timeout(int N)
{
	return (ut_llabs_memchk(N));
}
