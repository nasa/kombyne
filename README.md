Visualization plugin based on Kombyne™ from Intelligent Light™

To configure and build with GNU Autotools, you will have to first bootstrap the raw source after cloning the repository.  This is typically only required after the initial clone.

```
% git clone https://github.com/nasa/kombyne.git
% cd kombyne
% ./bootstrap
% mkdir _build
% cd _build
% ../configure --prefix=`pwd` \
               --with-KombyneLite=/path/to/KombyneLite \
               --with-mpi=${MPI_ROOT} \
               --with-png=/path/to/libpng/lib
```

In order for applications to discover the plugin under Linux, add the
"lib" sub-directory of the installation path given above to configure as
"--prefix" to your environment library search path (environment variable
$LD_LIBRARY_PATH under Linux).

Instruct your simulation software to use the Kombyne plugin for
visualization and create the necessary input files to define your
rendering pipelines according to the Kombyne documentation.
