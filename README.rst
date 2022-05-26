=====================
HDF5 Filter Template
=====================

This is a basic template for making a filter to use with hdf5.

This example uses the idea of compression and decompression, but filters are broader than this. 
There are some `rules <https://docs.hdfgroup.org/hdf5/rfc/HDF5DynamicallyLoadedFilters.pdf>`_ on how a filter must behave
defined by hdf5.

      1. An HDF5 filter is bidirectional.
          The filter handles both input and output to the file; a flag is passed to the filter to indicate the
          direction.
      2. An HDF5 filter operates on a buffer.
          The filter reads data from a buffer, performs some sort of transformation on the data, places
          the result in the same or new buffer, and returns the buffer pointer and size to the caller.
      3. An HDF5 filter should return zero in the case of failure.

This template acts as a "compression" filter however it intially does nothing. It simply copies data from the input
buffer, to an output buffer and hands the output back. It has three main parts:

passf_h5filter.c/passf_h5filter.h
----------------------------------

These files are the interface between the filter function and hdf5. This manages the filter entity for hdf5
and manages the buffers for the data. This makes the calls to ``compress`` and ``decompress`` but does not contain
the code for them.

passfilter.c/passfilter.h
--------------------------
These store the implementation of the filter. In this case the ``compress`` and ``decompress`` functions. This can be
(ideally) independent of hdf5 as they are acting purely on data from a buffer.

passf_h5plugin.c
-----------------
This exists to implement the dynamically loaded filter aspect of hdf5 filters.


The code is present register this filter correctly, however the example does not do so. It instead loads the filter
dynamically as this is how I will be using them. To use a dynamic filter you need to set the envrionment variable
HDF5_PLUGIN_PATH. For example::
  export HDF5_PLUGIN_PATH=/path/to/hdf5-filter-template/dist

Some vscode configs have been included to set this automatically when you run the example in debug.

To build and run
-----------------
To run this you need to build the library and the example. Do this
with::

  make
  make lib
  make ex

Then run the example in debug by selecting the run and debug tab,selecting "debug example" from the drop down menu and pressing run.
This should apply HDF5_PLUGIN_PATH and LD_LIBRARY_PATH for you.