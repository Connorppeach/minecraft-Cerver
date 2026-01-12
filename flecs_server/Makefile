CC=gcc  # /opt/intel/oneapi/compiler/latest/bin/icx
CFLAGS=-I. -ggdb -Wall -O0 # -Ofast  -ftree-vectorize -march=corei7 -mtune=corei7 -fopenmp # -lstdc++  -fPIE
LDFLAGS = -lm
DEPS=util.o components.o flecs_server.o network.o flecs/flecs.o


libflecs_mc_server.a: $(DEPS)
	ar rcs $@ $(DEPS)

main: $(DEPS) main.c ../protocol/libmcprotocol.a
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) -lpcre2-8

%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@   

clean:
	rm -f *.o *.a
