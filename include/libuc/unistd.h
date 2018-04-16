/*
** unistd.h
**
** Header file for unistd subset of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/03/25 by Juillard Jean-Baptiste
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

#ifndef UNISTD_H
# define UNISTD_H					1


# include <sys/types.h>


/*
** File number of stdin: 0.
*/
# define STDIN_FILENO				0
/*
** File number of stdout: 1.
*/
# define STDOUT_FILENO				1
/*
** File number of stderr: 2.
*/
# define STDERR_FILENO				2


extern ssize_t write(int fd, const void *buf, size_t count);
extern ssize_t read(int fd, void *buf, size_t count);

#endif
