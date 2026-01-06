CC=gcc  # /opt/intel/oneapi/compiler/latest/bin/icx
CFLAGS=-I. -ggdb -Wall -Ofast # -Ofast  -ftree-vectorize -march=corei7 -mtune=corei7 -fopenmp # -lstdc++  -fPIE
DEPS = packets.h types.h player.h simple_server.h ./packets/configuration.h ./packets/login.h ./packets/handshake.h ./packets/play.h 
OBJ = player.o rw.o packets.o util.o libnbt/miniz.o simple_server.o
LDFLAGS = -lm


%.o: %.c $(DEPS)
	$(CC) -c $< $(CFLAGS) -o $@   

main: $(OBJ) main.o fast_noise_lite.o 
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)



fast_noise_lite.o: fast_noise_lite.c 
	$(CC) -c $< $(CFLAGS) -o $@ -Ofast # make noise fast




test_client: $(OBJ) test_client.o 
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)


clean:
	rm *.o
