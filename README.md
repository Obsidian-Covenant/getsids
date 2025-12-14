# getsids

## Modernization Covenant

This is a refactored and modernized edition of **getsids**, a tool to enumerate Oracle Sids by sending the services command to the Oracle TNS listener.

Key changes:

- ✅ Fixed errors caused by old libraries
- ✅ Fixed warnings caused by old-style coding
- ✅ Cleaned autoreconf rules
- ✅ Refactored code to be used with latest gcc version

### Installation

#### Dependencies

Build dependencies:
```
gcc
```

Runtime dependencies:
```
glibc
```

#### From source

```bash
git clone https://github.com/Obsidian-Covenant/getsids.git
cd getsids
autoreconf -i
./configure
make
sudo make install
```

## README

Oracle Dump Sids <patrik.karlsson@ixsecurity.com> http://www.cqure.net

ODS tries to enumerate Oracle Sids using the services call to the
Oracle TNS listener. Nothing more nothing less ;)

Usage:
```shell
getsids <ip> <port>
```

--patrik
