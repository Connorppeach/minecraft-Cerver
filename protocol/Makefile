CC=gcc  # /opt/intel/oneapi/compiler/latest/bin/icx
CFLAGS=-I. -ggdb -Wall -O0 # -Ofast  -ftree-vectorize -march=corei7 -mtune=corei7 -fopenmp # -lstdc++  -fPIE
DEPS=packets.o rw.o
DEPS_PIC=packets.pic.o rw.pic.o 

%.pic.o: %.c
	$(CC) -fpic -c $< $(CFLAGS) -o $@   

%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@   

libmcprotocol.a: $(DEPS)
	ar rcs $@ $(DEPS)
libmcprotocol.pic.a: $(DEPS_PIC)
	ar rcs $@ $(DEPS_PIC)

packets.o: packets.c
	$(CC) -c $< $(CFLAGS) -o $@ -O2 # make packets(mostly for chunks) fast
packets.pic.o: packets.c
	$(CC) -fpic -c $< $(CFLAGS) -o $@ -O2 # make packets(mostly for chunks) fast

clean:
	rm -f *.o *.a
