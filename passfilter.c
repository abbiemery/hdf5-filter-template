/*  The source code for the actual "passfilter"
*
*   This acts as the code that would do the compressing/decompressing
*   of the data chunk from the buffer.
*
*   Ideally keep this decoupled from hdf5.
*/

# include "passfilter.h"

/* 
*   Copies the data from the source buffer as is into the output buffer.
*   Return: 
*   Success: Length of the output buffer
*/
int compress(void* destination_buf, unsigned long destination_buf_length,
    void* source_buf,unsigned long nbytes){
        
        memcpy(destination_buf, source_buf, nbytes);
        return destination_buf_length;
    }

/* 
*   Also copies the data from the source buffer as is into the output buffer.
*   Return: 
*   Success: Length of the output buffer
*/
int decompress(void* destination_buf, unsigned long destination_buf_length,
    void* source_buf,unsigned long nbytes){

        memcpy(destination_buf, source_buf, nbytes);
        return destination_buf_length;
    }