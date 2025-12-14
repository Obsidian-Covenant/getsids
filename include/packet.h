/* 
   Oracle Service Dump
   Copyright (C) Patrik Karlsson 2001
   
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#ifndef _PACKET_H
#define _PACKET_H

#ifdef WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <sys/types.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct hexPacket {
    unsigned int size;
    unsigned char *data;
} HEXPACKET;

HEXPACKET *createHexPacket(char *);
void freeHexPacket(HEXPACKET *);
int sendHexPacket(int, HEXPACKET *);

#endif
