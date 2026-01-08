CC=gcc  # /opt/intel/oneapi/compiler/latest/bin/icx
CFLAGS=-I. -ggdb -Wall -O0 # -Ofast  -ftree-vectorize -march=corei7 -mtune=corei7 -fopenmp # -lstdc++  -fPIE
LDFLAGS = -lm
DEPS=util.o player.o simple_server.o


libsimple_mc_server.a: $(DEPS)
	ar rcs $@ $(DEPS)
%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@   

clean:
	rm -f *.o *.a
