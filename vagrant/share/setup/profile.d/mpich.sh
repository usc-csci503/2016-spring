# Add /usr/lib64/mpich/bin to the path for sh compatible users

if ! echo $PATH | grep -q /usr/lib64/mpich/bin ; then
  export PATH=$PATH:/usr/lib64/mpich/bin
fi
