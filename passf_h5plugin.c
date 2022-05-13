/*
*   Dynamically loaded filter plugin
*
*   This is the code required to allow hdf5 to dynamicaly load
*   the filter instead of registering it.
*/

#include "passf_h5filter.h"
#include "H5PLextern.h"

H5PL_type_t H5PLget_plugin_type(void) {return H5PL_TYPE_FILTER;}
const void* H5PLget_plugin_info(void) {return H5Z_passf;}