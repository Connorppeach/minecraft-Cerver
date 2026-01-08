CC=gcc  # /opt/intel/oneapi/compiler/latest/bin/icx
CFLAGS=-I. -ggdb -Wall -O0 # -Ofast  -ftree-vectorize -march=corei7 -mtune=corei7 -fopenmp # -lstdc++  -fPIE
LDFLAGS = -lm


%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@   

main: main.o fast_noise_lite.o protocol/libmcprotocol.a simple_server/libsimple_mc_server.a
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

protocol/libmcprotocol.a:
	$(MAKE) -C protocol/

simple_server/libsimple_mc_server.a:
	$(MAKE) -C simple_server/

fast_noise_lite.o: fast_noise_lite.c 
	$(CC) -c $< $(CFLAGS) -o $@ -Ofast # make noise fast




test_client: $(OBJ) test_client.o 
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)


clean:
	rm *.o -f
	$(MAKE) -C simple_server/ clean
	$(MAKE) -C protocol/
