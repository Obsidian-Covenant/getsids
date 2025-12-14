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

char *processOracleServiceAnswer(HEXPACKET *pPacket) {
    int nLen = pPacket->size;
    char *pCmp = "SERVICE_DESC";
    int i = 0, j = 0;
    char *pSids;

    pSids = (char *)malloc(1024);
    memset(pSids, 0, 1024);

    for (i = 0; i < nLen - strlen(pCmp); i++) {
        if (strncmp((char *)pPacket->data + i, pCmp, strlen(pCmp)) == 0) {
            for (j = i; j < nLen - strlen(pCmp); j++) {
                if (strncmp((char *)pPacket->data + j, ")),", 3) == 0) {
                    /* Append safely to fixed 1024-byte buffer */
                    {
                        const size_t cap = 1024;
                        size_t used = strlen(pSids);
                        size_t want = (size_t)((j - i) + 2);
                        if (used < cap - 1) {
                            size_t room =
                                (cap - 1) - used; /* leave space for '\0' */
                            if (want > room) want = room;
                            strncat(pSids, (char *)pPacket->data + i, want);

                            /* Append newline without strncat edge-case warning
                             */
                            used = strlen(pSids);
                            if (used + 1 < cap) {
                                pSids[used] = '\n';
                                pSids[used + 1] = '\0';
                            }
                        }
                    }
                    break;
                }
            }
        }
    }

    return pSids;
}
