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

void freeHexPacket(HEXPACKET *pPacket) {
    free(pPacket->data);
    free(pPacket);
}

int sendHexPacket(int nFD, HEXPACKET *pPacket) {
    return send(nFD, pPacket->data, pPacket->size, 0);
}

void dumpHexPacketAsString(HEXPACKET *pPacket) {
    unsigned int i;

    if (pPacket->size == -1) {
        fprintf(stderr, "ERROR: Reading packet\n");
        return;
    }

    for (i = 0; i < pPacket->size; i++) {
        printf("%c", pPacket->data[i]);
    }
}

HEXPACKET *createHexPacket(char *pCharData) {
    int nLen = 0;
    char cHex[10];
    int i = 0;
    long n = 0;
    HEXPACKET *pHexPacket = NULL;

    nLen = strlen(pCharData);

    pHexPacket = (HEXPACKET *)malloc(sizeof(HEXPACKET));
    pHexPacket->data = (unsigned char *)malloc(nLen / 2);
    pHexPacket->size = nLen / 3 + 1;
    memset(pHexPacket->data, 0, nLen / 2);

    for (i = 0; i < nLen; i += 3) {
        memset(cHex, 0, sizeof(cHex));
        sprintf(cHex, "0x%c%c", pCharData[i], pCharData[i + 1]);
        n = strtol(cHex, NULL, 16);
        memset(pHexPacket->data + (i / 3), (int)n, 1);

        /* if we don't have a whitespace somethings wrong */
        if (nLen > i + 2 && pCharData[i + 2] != ' ') {
            freeHexPacket(pHexPacket);
            return NULL;
        }
    }

    return pHexPacket;
}
