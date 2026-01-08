CC=gcc  # /opt/intel/oneapi/compiler/latest/bin/icx
CFLAGS=-I. -ggdb -Wall -O0 # -Ofast  -ftree-vectorize -march=corei7 -mtune=corei7 -fopenmp # -lstdc++  -fPIE
LDFLAGS = -lm
DEPS=packets.o rw.o ../libnbt/miniz.o

%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@   

libmcprotocol.a: $(DEPS)
	ar rcs $@ $(DEPS)

packets.o: packets.c
	$(CC) -c $< $(CFLAGS) -o $@ -O2 # make packets(mostly for chunks) fast

clean:
	rm *.o *.a
