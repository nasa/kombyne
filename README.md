Visualization plugin based on Kombyne :tm: from Intelligent Light :tm:

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
