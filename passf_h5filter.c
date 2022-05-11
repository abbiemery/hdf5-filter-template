/*
*   The passfilter HDf5 filter
*/

#include "passfilter.h"
#include "passf_h5filter.h"

#define PUSH_ERR(func, minor, str)                                      \
    H5Epush1(__FILE__, func, __LINE__, H5E_PLINE, minor, str)

#define H5Z_CLASS_T_VERS 2


const H5Z_class2_t H5Z_passf[1] = {{
    H5Z_CLASS_T_VERS,   /* H5Z_class_t version */
    (H5Z_filter_t)H5Z_FILTER_PASSF, /* Filter id number */
    1,              /* encoder_present flag (set to true) */
    1,              /* decoder_present flag (set to true) */
    "passfilter",   /* Filter name for debugging */
    NULL,                       /* The "can apply" callback     */
    NULL,                       /* The "set local" callback     */
    (H5Z_func_t)H5Z_filter_passf, /* The actual filter function */
}};

size_t H5Z_filter_passf(unsigned flags,size_t cd_nelmts,
                        const unsigned cd_values[],size_t nbytes,
                        size_t *buf_size,void**buf)
{

    void *outbuf = NULL;
    size_t outbuflen, outdatalen;
    size_t ret_value;

    if (flags & H5Z_FLAG_REVERSE){
        /** Decompress data.
         **
            ** This process is troublesome since the size of uncompressed data
            ** is unknown, so the low-level interface must be used.
            ** Data is decompressed to the output buffer (which is sized
            ** for the average case); if it gets full, its size is doubled
            ** and decompression continues.  This avoids repeatedly trying to
            ** decompress the whole block, which could be really inefficient.
            **/
        
        
    } else {
        /** Compress data.
         **
         ** This is quite simple, since the size of compressed data in the worst
         ** case is known and it is not much bigger than the size of uncompressed
         ** data.  This allows us to use the simplified one-shot interface to
         ** compression.
         **/


        /* Get compression block size if present. */


        /* Prepare the output buffer. */


        /* Compress data. */


    }

}

int passf_register_h5filter(void){

    int retval;

    retval = H5Zregister(H5Z_passf);
    if(retval<0){
        PUSH_ERR("passf_register_h5filter",
                H5E_CANTREGISTER, "Can't register passfilter filter");
    }
    return retval;
}

error:
    if(outbuf)
        H5free_memory(outbuf);
        outbuf = NULL;
  return 0;