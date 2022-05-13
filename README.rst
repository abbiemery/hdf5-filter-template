HDF5 Filter Template

This is just a basic template for making filters to use with hdf5.

The aim is to give myself and easier starting point to add custom
compression algorithms as a hdf5 filter to be used as a dynamically
loaded filter.

This filter intentionally does nothing to the chunk it is applied to.
It copies the chunk from one buffer to another and reassigns it back.

The code pertinent to the hdf5 interface is in the files prefixed
with passf_. The code that would apply the algorithm would be in
the passfilter.c .

Todo:
fix and commit the makefile