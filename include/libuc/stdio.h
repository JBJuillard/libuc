/*
** stdio.h
**
** Header file for stdio subset of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/02/19 by Juillard Jean-Baptiste
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

#ifndef STDIO_H
# define STDIO_H				1


/* size_t */
# include <libuc/stddef.h>
/* off_t, ssize_t */
# include <sys/types.h>
/* va_list*/
# include <stdarg.h>

# define EOF					((int)(-1))

# define STDIN					0
# define STDOUT					1
# define STDERR					2
# define stdin					STDIN
# define stdout					STDOUT
# define stderr					STDERR

//int   fprintf(FILE * restrict stream, const char * restrict format, ...);


#endif
