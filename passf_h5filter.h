/*
*   The passfilter HDf5 filter
*
*   This contains the basic header code to set up a filter.
*   Its purpose is to act as a template for implementing
*   compression algorithms in a hdf5 filter.
*
*   The "compression" that this filter applies just copies
*   the data from the input buffer to an output buffer, does
*   nothing then passes it back.
*   
*/

#ifndef PASSF_H5FILTER_H
#define PASSF_H5FILTER_H

#include "hdf5.h"

/* use an intiger greater than 256 to be id of the registered filter. */
#define H5Z_FILTER_PASSF 3000

const H5Z_class_t H5Z_passf[1];

/* declare a filter function */
size_t H5Z_filter_passf(unsigned flags, size_t cd_nelmts, const unsigned cd_values[], 
            size_t nbytes, size_t *buf_size, void**buf);

/* ---- passf_register_h5filter ----
 *
 * Register the passf HDF5 filter within the HDF5 library.
 *
 * Call this before using the passf HDF5 filter from C unless
 * using dynamically loaded filters, then it does not need registering.
 *
 */
int passf_register_h5filter(void);

#endif // PASSF_H5FILTER_H