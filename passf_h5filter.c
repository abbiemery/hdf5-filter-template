/*
*   The passfilter HDf5 filter
*
*   This contains the basic code to set up a filter, copy the data
*   from the input buffer to an output buffer, do nothing, then
*   pass it back.
*   
*   It's purpose is to act as a template for implementing
*   compression algorithms in a hdf5 filter.
*   
*   Further considerations need to be made to use this for compression
*   purposes. Such as allocating output buffersize, for decompression
*   you need to allocate a larger output buffer, and vise versa for
*   compression.
*
*   When compressing you might want to include further blocking.
*   
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

    void * outbuf = NULL;
    size_t outbuf_size; /* size of output buffer */
    size_t ret_value;

    if (flags & H5Z_FLAG_REVERSE){
        /** Decompress data **/

        /* prepare output buf*/
        outbuf_size = (*buf_size);
        if((outbuf == H5allocate_memory(outbuf_size, false))== NULL){
            fprintf(stderr, "Memory allocation failed\n");
            goto error;
        }
        
        /* decompress data */
        ret_value = decompress(outbuf, outbuf_size, *buf, nbytes);
        
    } else {
        /** Compress **/

        /* prepare output buf*/
        outbuf_size = (*buf_size);
        if((outbuf == H5allocate_memory(outbuf_size, false))== NULL){
            fprintf(stderr, "Memory allocation failed\n");
            goto error;
        }
        
        /* compress data */
        ret_value = compress(outbuf, outbuf_size, *buf, nbytes);
    }

    /* replace the input buffer with the output buffer */
    H5free_memory(*buf);
    *buf = outbuf;
    *buf_size = outbuf_size;
    ret_value = outbuf_size;
    outbuf = NULL;

    if(outbuf)
        H5free_memory(outbuf);
    return ret_value;


    error:
        if(outbuf)
            H5free_memory(outbuf);
            outbuf = NULL;
    return 0;
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