CC=gcc  # /opt/intel/oneapi/compiler/latest/bin/icx
CFLAGS=-I. -ggdb -Wall # -Ofast  -ftree-vectorize -march=corei7 -mtune=corei7 -fopenmp # -lstdc++  -fPIE
DEPS = packets.h ./packets/configuration.h ./packets/login.h ./packets/handshake.h ./packets/play.h
OBJ = player.o rw.o packets.o util.o libnbt/miniz.o
LDFLAGS = 


%.o: %.c $(DEPS)
	$(CC) -c $< $(CFLAGS) -o $@   

main: $(OBJ) main.o 
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

simple_server: $(OBJ) simple_server.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)


test_client: $(OBJ) test_client.o 
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)


clean:
	rm *.o
