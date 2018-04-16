/*
** inet.h
**
** Header file for inet subset of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/03/27 by Juillard Jean-Baptiste
** Updated: 2018/04/05 by Juillard Jean-Baptiste
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

#ifndef ARPA_INET_H
# define ARPA_INET_H				1

/*
** uint32_t and uint16_t
*/
# include <libuc/stdint.h>
/*
** in_port_t,
** in_addr, in_addr_t,
** in6_addr, in6_addr_t,
** INET_ADDRSTRLEN, INET6_ADDRSTRLEN
*/
# include <libuc/netinet/in.h>

uint32_t	htonl(uint32_t hostlong);
uint16_t	htons(uint16_t hostshort);
uint32_t	ntohl(uint32_t netlong);
uint16_t	ntohs(uint16_t netshort);

in_addr_t	inet_addr(const char *cp);
char		*inet_ntoa(struct in_addr in);
const char	*inet_ntop(int af, const void * restrict src, char * restrict dest,
						socklen_t size);
int			inet_pton(int af, const char * restrict src, void * restrict dest);

#endif
