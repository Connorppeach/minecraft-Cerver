CC=gcc  # /opt/intel/oneapi/compiler/latest/bin/icx
CFLAGS=-I. -ggdb -Wall -O0 # -Ofast  -ftree-vectorize -march=corei7 -mtune=corei7 -fopenmp # -lstdc++  -fPIE
DEPS=util.o player.o simple_server.o registry.o
DEPS_PIC=util.pic.o player.pic.o simple_server.pic.o registry.pic.o


libsimple_mc_server.a: $(DEPS)
	ar rcs $@ $(DEPS)
libsimple_mc_server.pic.a: $(DEPS_PIC)
	ar rcs $@ $(DEPS_PIC)

%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@   
%.pic.o: %.c
	$(CC) -fpic -c $< $(CFLAGS) -o $@   

clean:
	rm -f *.o *.a
