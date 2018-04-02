/*
** main.c
**
** main function for unit tests of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2017/01/28 by Juillard Jean-Baptiste
** Updated: 2018/03/26 by Juillard Jean-Baptiste
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

#include <libuc/stdlib.h>
#include <libuc/errno.h>
#include <libuc/limits.h>

#include "test.h"

int	main(int ac, char **av)
{
	int	test;
	int	N;

	errno = 0;
	if (ac == 3)
	{
		test = 0;
		N = 0;
		if ((test = get_int(av[1])) <= 0 || test > 3
			|| errno == EOVERFLOW || errno == EINVAL
			|| (N = get_int(av[2])) <= 0 || N > INT_MAX
			|| errno == EOVERFLOW || errno == EINVAL)
			return (-2);
		errno = 0;
		if (test == 1)
			return (INTERFACE_FUNCTION(N));
		else if (test == 2)
			return (MEMCHK_FUNCTION(N));
		else
			return (TIMEOUT_FUNCTION(N));
	}
	else
		return (-1);
	return (0);
}
