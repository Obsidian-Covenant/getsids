# Process this file with autoconf to produce a configure script.
AC_INIT([getsids],[0.1],[unknown])
AC_CONFIG_SRCDIR([getsids.c])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_CANONICAL_HOST

AC_PROG_CC
AC_USE_SYSTEM_EXTENSIONS

dnl Basic headers / functions
AC_CHECK_HEADERS([ \
  stdlib.h string.h stdio.h \
  sys/types.h sys/socket.h \
  arpa/inet.h netinet/in.h \
  winsock2.h ws2tcpip.h \
])
AC_CHECK_FUNCS([memset strtol socket send])

dnl Windows winsock library (MinGW/MSYS, Cygwin typically needs it too if using winsock)
WS2_32_LIBS=""
case "$host_os" in
  mingw*|msys*|cygwin*)
    WS2_32_LIBS="-lws2_32"
    ;;
esac
AC_SUBST([WS2_32_LIBS])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
