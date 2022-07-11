/************************************************************

  This example just writes to and reads from a dataset using
  the passfilter as a dynamically loaded filter in its pipeline.

  It writes intigers to a dataset through the filter then closes
  the file. It then reopens the file reads back the data,
  and outputs the type of compression and the maximum value 
  in the dataset to the screen.

  The two max values should be the same.

  This example is essentially copied from the bzip2 example
  provided by hdf5. 

 ************************************************************/

#include "hdf5.h"
#include "passf_h5filter.h"
#include <stdio.h>
#include <stdlib.h>

#define FILE            "example_pass.h5"
#define DATASET         "DS-pass"
#define DIM0            5
#define DIM1            10
#define CHUNK0          1
#define CHUNK1          10

int main (void)
{
    hid_t           file, space, dset, dcpl;    /* Handles */
    herr_t          status;
    H5Z_filter_t    filter_type;
    hsize_t         dims[2] = {DIM0, DIM1},
                    chunk[2] = {CHUNK0, CHUNK1};
    size_t          nelmts;
    unsigned int    flags,
                    filter_info;
    const unsigned cd_values[1] = {7};          /* random custom values*/
    int             wdata[DIM0][DIM1],          /* Write buffer */
                    rdata[DIM0][DIM1],          /* Read buffer */
                    maxr, maxw,
                    i, j;

    

    /*
     * Initialize data and find its maximum value to check later.
     */
    for (i=0; i<DIM0; i++)
        for (j=0; j<DIM1; j++)
            wdata[i][j] = i * j - j;
    maxw = wdata[0][0];
    for (i=0; i<DIM0; i++)
        for (j=0; j<DIM1; j++)
            if (maxw < wdata[i][j])
                maxw = wdata[i][j];


    /*
     * Create a new file using the default properties.
     */
    file = H5Fcreate (FILE, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    /*
     * Create dataspace.  Setting maximum size to NULL sets the maximum
     * size to be the current size.
     */
    space = H5Screate_simple (2, dims, NULL);

    /*
     * Create the dataset creation property list, add the
     * filter and set the chunk size.
     */
    dcpl = H5Pcreate (H5P_DATASET_CREATE);
    status = H5Pset_filter (dcpl, (H5Z_filter_t)H5Z_FILTER_PASSF, H5Z_FLAG_MANDATORY, (size_t)1, cd_values);
    status = H5Pset_chunk (dcpl, 2, chunk);

    /*
     * Create the dataset.
     */
    dset = H5Dcreate (file, DATASET, H5T_STD_I32BE, space, H5P_DEFAULT, dcpl, H5P_DEFAULT);

    /*
     * Write the data to the dataset.
     */
    status = H5Dwrite (dset, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT,
                wdata);

    /*
     * Close and release resources.
     */
    status = H5Pclose (dcpl);
    status = H5Dclose (dset);
    status = H5Sclose (space);
    status = H5Fclose (file);


    /*
     * Now we begin the read section of this example.
     */

    /*
     * Open file and dataset using the default properties.
     */
    file = H5Fopen (FILE, H5F_ACC_RDONLY, H5P_DEFAULT);
    dset = H5Dopen (file, DATASET, H5P_DEFAULT);

    /*
     * Retrieve dataset creation property list.
     */
    dcpl = H5Dget_create_plist (dset);

    /*
     * Retrieve and print the filter type.  Here we only retrieve the
     * first filter because we know that we only added one filter.
     */
    nelmts = 0;
    filter_type = H5Pget_filter (dcpl, 0, &flags, &nelmts, NULL, 0, NULL,
                &filter_info);
    printf ("Filter type is: ");
    switch (filter_type) {
        case H5Z_FILTER_PASSF:
            printf ("H5Z_FILTER_PASSF\n");
            break;
        default:
            printf ("Not PASSF as expected\n");
    }

    /*
     * Read the data using the default properties.
     */
    status = H5Dread (dset, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT,
                rdata);

    /*
     * Find the maximum value in the dataset, to verify that it was
     * read correctly.
     */
    maxr = rdata[0][0];
    for (i=0; i<DIM0; i++) {
        for (j=0; j<DIM1; j++)  {
            printf ("%d %d \n", wdata[i][j], rdata[i][j]);
            if (maxr < rdata[i][j])
                maxr = rdata[i][j];
        }
    }
    /*
     * Print the maximum value.
     */
    printf ("Maximum value maxr in %s is: %d\n", DATASET, maxr);
    printf ("Maximum value maxw in %s is: %d\n", DATASET, maxw);

    /*
     * Close and release resources.
     */
    status = H5Pclose (dcpl);
    status = H5Dclose (dset);
    status = H5Fclose (file);

    return 0;
}
