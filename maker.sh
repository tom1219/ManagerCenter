sed -i -e s/{name}/test/g Makefile.am
aclocal
autoheader
autoconf
automake --add-missing
./configure CXXFLAGS="-O2" CFLAGS="-O2"
