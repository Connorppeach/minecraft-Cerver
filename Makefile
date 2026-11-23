CC=gcc  # /opt/intel/oneapi/compiler/latest/bin/icx
CFLAGS=-I. -I$(abspath ../rw/inc/) -ggdb -Wall -O0 # -Ofast  -ftree-vectorize -march=corei7 -mtune=corei7 -fopenmp # -lstdc++  -fPIE
LDFLAGS = -lm


%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@   
%.pic.o: %.c
	$(CC) -fpic -c $< $(CFLAGS) -o $@   


simple_terrain: demos/simple_terrain/main.o fast_noise_lite.o util.o protocol/libmcprotocol.a simple_server/libsimple_mc_server.a 
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) -lpcre2-8 ../rw/rw.a

server.so: demos/simple_terrain/main.pic.a fast_noise_lite.pic.o util.pic.o protocol/libmcprotocol.pic.a simple_server/libsimple_mc_server.pic.a
	$(CC) -shared -o $@ $^ $(CFLAGS) $(LDFLAGS) -lpcre2-8

tccserver.so: demos/tcc/main_tcc.pic.o libtcc.pic.a libtcc1.a fast_noise_lite.pic.o fast_noise_lite.pic.o util.pic.o protocol/libmcprotocol.pic.a simple_server/libsimple_mc_server.pic.a 
	$(CC) -shared -o $@ $^ $(CFLAGS) $(LDFLAGS) -lpcre2-8


main_tcc: demos/tcc/main_tcc.o util.o simple_server/libsimple_mc_server.a protocol/libmcprotocol.a
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) -ltcc
.PHONY: protocol/libmcprotocol.a protocol/libmcprotocol.pic.a simple_server/libsimple_mc_server.a simple_server/libsimple_mc_server.pic.a
protocol/libmcprotocol.a:
	$(MAKE) CFLAGS="$(CFLAGS)" -C protocol/ libmcprotocol.a

protocol/libmcprotocol.pic.a:
	$(MAKE) CFLAGS="$(CFLAGS)" -C protocol/ libmcprotocol.pic.a



simple_server/libsimple_mc_server.a:
	$(MAKE) CFLAGS="$(CFLAGS)"  -C simple_server/  libsimple_mc_server.a

simple_server/libsimple_mc_server.pic.a:
	$(MAKE) CFLAGS="$(CFLAGS)" -C simple_server/ libsimple_mc_server.pic.a


fast_noise_lite.o: fast_noise_lite.c 
	$(CC) -c $< $(CFLAGS) -o $@ -O2 # make noise fast




test_client: $(OBJ) test_client.o 
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)


clean:
	rm *.o -f
	$(MAKE) -C simple_server/ clean
	$(MAKE) -C protocol/ clean
