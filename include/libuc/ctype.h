/*
** ctype.h
**
** Header file for ctype subset of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/02/18 by Juillard Jean-Baptiste
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

#ifndef CTYPES_H
# define	CTYPES_H		1

extern int	isalnum(int c);
//extern int	isalnum_l(int c, locale_t l);
extern int	isalpha(int c);
//extern int	isalpha_l(int c, locale_t l);
extern int	isascii(int c);						// Obsolete POSIX.1-2008
extern int	isblank(int c);
//extern int	isblank_l(int c, locale_t l);
extern int	iscntrl(int c);
//extern int	iscntrl_l(int c, locale_t l);
extern int	isdigit(int c);
//extern int	isdigit_l(int c, locale_t l);
extern int	isgraph(int c);
//extern int	isgraph_l(int c, locale_t l);
extern int	islower(int c);
//extern int	islower_l(int c, locale_t l);
extern int	isprint(int c);
//extern int	isprint_l(int c, locale_t l);
extern int	ispunct(int c);
//extern int	ispunct_l(int c, locale_t l);
extern int	isspace(int c);
//extern int	isspace_l(int c, locale_t l);
extern int	isupper(int c);
//extern int	isupper_l(int c, locale_t l);
extern int	isxdigit(int c);
//extern int	isxdigit_l(int c, locale_t l);
extern int	toascii(int c);
extern int	tolower(int c);
//extern int	tolower_l(int c, locale_t l);
extern int	toupper(int c);
//extern int	toupper_l(int c, locale_t l);

# define	_toupper(c)		((((int)(c)) >= (int)('a') && ((int)(c)) <= (int)('z')) ? (((int)(c)) - 0x20) : ((int)(c)))
# define	_tolower(c)		((((int)(c)) >= (int)('A') && ((int)(c)) <= (int)('Z')) ? (((int)(c)) + 0x20) : ((int)(c)))

#endif
