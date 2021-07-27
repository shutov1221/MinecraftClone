#pragma once

#define SCR_WIDTH 360
#define SCR_HEIGHT 240


#define CHUNKS_AROUND 8

#define CHUNK_Z 16
#define CHUNK_X 16
#define CHUNK_Y 256
#define CHUNK_VOLUME CHUNK_Z * CHUNK_Y * CHUNK_X
#define SUPERCHUNK_X CHUNKS_AROUND
#define SUPERCHUNK_Z CHUNKS_AROUND
#define SUPERCHUNK_SIZE SUPERCHUNK_X * SUPERCHUNK_Z
