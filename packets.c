#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "packets.h"
#define PACKET_IMPL
#define PACKET_READ_IMPL
#include "packets.h"
#undef PACKET_READ_IMPL
#define PACKET_WRITE_IMPL
#include "packets.h"

