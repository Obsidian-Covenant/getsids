bin_PROGRAMS = getsids

getsids_SOURCES = \
	getsids.c \
	socket.c \
	packet.c \
	process.c \
	include/socket.h \
	include/packet.h \
	include/process.h

# Use headers from ./include
getsids_CPPFLAGS = -I$(srcdir)/include

# Winsock on Windows-like environments; empty elsewhere.
getsids_LDADD = @WS2_32_LIBS@

# Good hygiene for distributions made by "make dist"
EXTRA_DIST = README COPYING
