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

#include "packet.h"
#include "socket.h"

int isWriteable(int nFD) {
    fd_set rfds;
    struct timeval tv;
    int retval;

    FD_ZERO(&rfds);
    FD_SET(nFD, &rfds);
    tv.tv_sec = 0;
    tv.tv_usec = 500;

    retval = select(nFD + 1, NULL, &rfds, NULL, &tv);

    if (retval) {
        return 0;
    }

    return -1;
}

HEXPACKET *recvData(int nFD) {
    HEXPACKET *pPacket;
    const unsigned int MAX_PACKET_SIZE = 1024;

    pPacket = (HEXPACKET *)malloc(sizeof(HEXPACKET));
    pPacket->data = (unsigned char *)malloc(MAX_PACKET_SIZE);
    pPacket->size = 0;

    pPacket->size = recv(nFD, pPacket->data, MAX_PACKET_SIZE, 0);

    /* no data */
    if (pPacket->size == 0) {
        free(pPacket->data);
        return NULL;
    }

    return pPacket;
}

int connectSocket(char *pIP, int nPort) {
    int nFD = -1;
    struct sockaddr_in sock;

#ifdef WIN32
    WORD wVersionRequested = 0;
    WSADATA wsaData;

    wVersionRequested = MAKEWORD(1, 1);
    WSAStartup(wVersionRequested, &wsaData);
#endif

    nFD = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    /* An error occured */
    if (nFD == -1) {
        fprintf(stderr, "ERROR: Creating socket...\n");
    }

    sock.sin_addr.s_addr = inet_addr(pIP);
    sock.sin_family = AF_INET;
    sock.sin_port = htons(nPort);

    connect(nFD, (struct sockaddr *)&sock, sizeof(sock));

    return nFD;
}
