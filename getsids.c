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
#include "process.h"
#include "socket.h"

void usage(char **argv) {
    fprintf(stdout,
            "\nOracleDumpSids v0.0.1 <patrik.karlsson@ixsecurity.com>\n");
    fprintf(stdout, "---------------- http://cqure.net --------------------\n");
    fprintf(stdout, "%s <ip> <port>\n", argv[0]);
    fprintf(stdout, "\n");
}

int sendServicesQuery(int nFD) {
    HEXPACKET *pPacket;

#ifdef WIN32
    if (isWriteable(nFD) != 0) return -1;
#endif

    pPacket = createHexPacket(
        "00 c7 00 00 01 00 00 00 01 36 01 2c 00 00 08 00 "
        "7f ff a3 0a 00 00 01 00 00 8d 00 3a 00 00 07 f8 "
        "0c 0c 00 00 00 00 00 00 00 00 00 00 05 00 00 00 "
        "00 02 00 00 00 00 00 00 00 00 28 44 45 53 43 52 "
        "49 50 54 49 4f 4e 3d 28 43 4f 4e 4e 45 43 54 5f "
        "44 41 54 41 3d 28 43 49 44 3d 28 50 52 4f 47 52 "
        "41 4d 3d 29 28 48 4f 53 54 3d 29 28 55 53 45 52 "
        "3d 41 64 6d 69 6e 69 73 74 72 61 74 6f 72 29 29 "
        "28 43 4f 4d 4d 41 4e 44 3d 73 65 72 76 69 63 65 "
        "73 29 28 41 52 47 55 4d 45 4e 54 53 3d 36 34 29 "
        "28 53 45 52 56 49 43 45 3d 4c 49 53 54 45 4e 45 "
        "52 29 28 56 45 52 53 49 4f 4e 3d 31 33 35 32 38 "
        "36 37 38 34 29 29 29");

    sendHexPacket(nFD, pPacket);
    freeHexPacket(pPacket);

    return 0;
}

int main(int argc, char **argv) {
    int nFD = -1;
    HEXPACKET *pPacket;
    char *pFoo;

    /* do we have enough arguments ? */
    if (argc < 3) {
        usage(argv);
        exit(1);
    }

    /* is it a acceptable port ? */
    if (atoi(argv[2]) == 0) {
        usage(argv);
        exit(1);
    }

    nFD = connectSocket(argv[1], atoi(argv[2]));

    /* an error occured connecting to server */
    if (nFD == -1) exit(1);

    /* Could we connect to the damn listener ? */
    if (sendServicesQuery(nFD) == -1) {
        fprintf(stderr, "ERROR: Connecting to Oracle Listener\n");
        exit(1);
    }

    for (;;) {
        if ((pPacket = recvData(nFD)) == NULL) break;
        pFoo = processOracleServiceAnswer(pPacket);

        if (pFoo != NULL) printf("%s", pFoo);

        freeHexPacket(pPacket);
        free(pFoo);
    }

    return 0;
}
