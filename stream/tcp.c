/*
 *  Copyright (C) 2001 Bertrand BAUDET, 2006 Benjamin Zores
 *   Network helpers for TCP connections
 *   (originally borrowed from network.c,
 *      by Bertrand BAUDET <bertrand_baudet@yahoo.com>).
 *
 *   This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software Foundation,
 *  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "config.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <ctype.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef HAVE_WINSOCK2
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define closesocket close
#else
#include <winsock2.h>
#include <ws2tcpip.h>
#endif

#include "mp_msg.h"
#include "help_mp.h"
#include "tcp.h"

/* IPv6 options */
int network_prefer_ipv4 = 0;

/* Converts an address family constant to a string */
static const char *
af2String (int af)
{
  switch (af)
  {
  case AF_INET:
    return "AF_INET";
#ifdef HAVE_AF_INET6
  case AF_INET6:
    return "AF_INET6";
#endif
  default:
    return "Unknown address family!";
  }
}

static int
connect2Server_with_af (char *host, int port, int af ,int verb)
{
  int socket_server_fd;
  int err;
  socklen_t err_len;
  int ret, count = 0;
  fd_set set;
  struct timeval tv;

  union {
    struct sockaddr_in four;
#ifdef HAVE_AF_INET6
    struct sockaddr_in6 six;
#endif
  } server_address;

  size_t server_address_size;
  void *our_s_addr; /* Pointer to sin_addr or sin6_addr */
  struct hostent *hp = NULL;
  char buf[255];
	
#ifdef HAVE_WINSOCK2
  u_long val;
#endif
	
  socket_server_fd = socket (af, SOCK_STREAM, 0);
  if (socket_server_fd == -1)
    return TCP_ERROR_FATAL;

  switch (af)
  {
  case AF_INET:
    our_s_addr = (void *) &server_address.four.sin_addr;
    break;
#ifdef HAVE_AF_INET6
  case AF_INET6:
    our_s_addr = (void *) &server_address.six.sin6_addr;
    break;
#endif
  default:
    mp_msg (MSGT_NETWORK, MSGL_ERR, MSGTR_MPDEMUX_NW_UnknownAF, af);
    return TCP_ERROR_FATAL;
  }
	
  memset (&server_address, 0, sizeof (server_address));
	
#ifndef HAVE_WINSOCK2
#ifdef USE_ATON
  if (inet_aton (host, our_s_addr) !=1)
#else
  if (inet_pton (af, host, our_s_addr) !=1)
#endif /* USE_ATON */
#else
  if (inet_addr (host) == INADDR_NONE)
#endif /* HAVE_WINSOCK2 */
  {
    if (verb)
      mp_msg (MSGT_NETWORK, MSGL_STATUS,
              MSGTR_MPDEMUX_NW_ResolvingHostForAF, host, af2String (af));
		
#ifdef HAVE_GETHOSTBYNAME2
    hp = (struct hostent *) gethostbyname2 (host, af);
#else
    hp = (struct hostent *) gethostbyname (host);
#endif /* HAVE_GETHOSTBYNAME2 */

    if (!hp)
    {
      if (verb)
        mp_msg (MSGT_NETWORK, MSGL_ERR,
                MSGTR_MPDEMUX_NW_CantResolv, af2String (af), host);
      return TCP_ERROR_FATAL;
    }
		
    memcpy (our_s_addr, (void *) hp->h_addr_list[0], hp->h_length);
  }
#ifdef HAVE_WINSOCK2
  else
  {
    unsigned long addr = inet_addr (host);
    memcpy (our_s_addr, (void *) &addr, sizeof (addr));
  }
#endif /* HAVE_WINSOCK2 */
	
  switch (af)
  {
  case AF_INET:
    server_address.four.sin_family = af;
    server_address.four.sin_port = htons (port);			
    server_address_size = sizeof (server_address.four);
    break;
#ifdef HAVE_AF_INET6		
  case AF_INET6:
    server_address.six.sin6_family = af;
    server_address.six.sin6_port = htons (port);
    server_address_size = sizeof (server_address.six);
    break;
#endif /* HAVE_AF_INET6 */
  default:
    mp_msg (MSGT_NETWORK, MSGL_ERR, MSGTR_MPDEMUX_NW_UnknownAF, af);
    return TCP_ERROR_FATAL;
  }

#if defined(USE_ATON) || defined(HAVE_WINSOCK2)
  strncpy (buf, inet_ntoa (*((struct in_addr *) our_s_addr)), 255);
#else
  inet_ntop (af, our_s_addr, buf, 255);
#endif /* USE_ATON || HAVE_WINSOCK2 */
  
  if (verb)
    mp_msg (MSGT_NETWORK, MSGL_STATUS,
            MSGTR_MPDEMUX_NW_ConnectingToServer, host, buf, port);

  /* Turn the socket as non blocking so we can timeout on the connection */
#ifndef HAVE_WINSOCK2
  fcntl (socket_server_fd, F_SETFL,
         fcntl (socket_server_fd, F_GETFL) | O_NONBLOCK);
#else
  val = 1;
  ioctlsocket (socket_server_fd, FIONBIO, &val);
#endif /* HAVE_WINSOCK2 */
  
  if (connect (socket_server_fd, (struct sockaddr *) &server_address,
               server_address_size) == -1)
  {
#ifndef HAVE_WINSOCK2
    if (errno != EINPROGRESS)
#else
    if ((WSAGetLastError () != WSAEINPROGRESS)
        && (WSAGetLastError () != WSAEWOULDBLOCK))
#endif /* HAVE_WINSOCK2 */
    {
      if (verb)
        mp_msg (MSGT_NETWORK, MSGL_ERR,
                MSGTR_MPDEMUX_NW_CantConnect2Server, af2String (af));

      closesocket (socket_server_fd);
      return TCP_ERROR_PORT;
    }
  }

  tv.tv_sec = 0;
  tv.tv_usec = 500000;

  FD_ZERO (&set);
  FD_SET (socket_server_fd, &set);

  /* When the connection will be made, we will have a writable fd */
  while ((ret = select (socket_server_fd + 1, NULL, &set, NULL, &tv)) == 0)
  {
    if (ret < 0)
      mp_msg (MSGT_NETWORK, MSGL_ERR, MSGTR_MPDEMUX_NW_SelectFailed);
    else if (ret > 0)
      break;
    else if (count > 30 || mp_input_check_interrupt (500))
    {
      if (count > 30)
        mp_msg (MSGT_NETWORK, MSGL_ERR, MSGTR_MPDEMUX_NW_ConnTimeout);
      else
        mp_msg (MSGT_NETWORK, MSGL_V, "Connection interuppted by user\n");
      return TCP_ERROR_TIMEOUT;
    }

    count++;
    FD_ZERO (&set);
    FD_SET (socket_server_fd, &set);
    tv.tv_sec = 0;
    tv.tv_usec = 500000;
  }

  /* Turn back the socket as blocking */
#ifndef HAVE_WINSOCK2
  fcntl (socket_server_fd, F_SETFL,
         fcntl (socket_server_fd, F_GETFL) & ~O_NONBLOCK);
#else
  val = 0;
  ioctlsocket (socket_server_fd, FIONBIO, &val);
#endif /* HAVE_WINSOCK2 */
  
  /* Check if there were any error */
  err_len = sizeof (int);
  ret = getsockopt (socket_server_fd, SOL_SOCKET, SO_ERROR, &err, &err_len);
  if (ret < 0)
  {
    mp_msg (MSGT_NETWORK, MSGL_ERR,
            MSGTR_MPDEMUX_NW_GetSockOptFailed, strerror (errno));
    return TCP_ERROR_FATAL;
  }

  if (err > 0)
  {
    mp_msg (MSGT_NETWORK, MSGL_ERR,
            MSGTR_MPDEMUX_NW_ConnectError, strerror (err));
    return TCP_ERROR_PORT;
  }
	
  return socket_server_fd;
}

int
connect2Server (char *host, int port, int verb)
{
#ifdef HAVE_AF_INET6
  int r;
  int s = TCP_ERROR_FATAL;

  r = connect2Server_with_af (host, port,
                              network_prefer_ipv4 ? AF_INET:AF_INET6, verb);
  if (r > TCP_ERROR_PORT)
    return r;

  s = connect2Server_with_af (host, port,
                              network_prefer_ipv4 ? AF_INET6:AF_INET, verb);
  if (s == TCP_ERROR_FATAL)
    return r;

  return s;
#else	
  return connect2Server_with_af (host, port, AF_INET,verb);
#endif /* HAVE_AF_INET6 */
}
