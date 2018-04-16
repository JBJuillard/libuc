/*
** strings.h
**
** Header file for strings subset of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/04/15 by Juillard Jean-Baptiste
** Updated: 2018/04/15 by Juillard Jean-Baptiste
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

#ifndef STRINGS_H
# define STRINGS_H						1

void	bcopy(const void *src, void *dest, size_t n);	/* Obsolette */
void	bzero(void *s, size_t n);						/* Obsolette */
void	explicit_bzero(void *s, size_t n);				/* Obsolette */
int		bcmp(const void *s1, const void *s2, size_t n);	/* Obsolette */

#endif
