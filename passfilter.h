/* The headerfile for the actual "passfilter" */

#include<string.h>

int compress(void* destination_buffer, unsigned long destination_length,
    void* source_buffer,unsigned long nbytes);

int decompress(void* destination_buf, unsigned long destination_buf_length,
    void* source_buf,unsigned long nbytes);