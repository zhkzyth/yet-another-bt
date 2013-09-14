CC=gcc
CFLAGS= -Iinclude -Wall  -g -DDEBUG

ttorrent: main.o parse_metafile.o tracker.o bitfield.o message.o peer.o data.o policy.o torrent.o bterror.o log.o signal_hander.o
	$(CC) -o $@ $^ -ldl

.PHONY: clean
clean:
	#cat main.c
	rm -rf *.o ttorrent
