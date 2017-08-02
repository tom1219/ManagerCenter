sed -i -e s/{name}/test/g Makefile.am
aclocal
autoheader
autoconf
automake --add-missing
./configure CXXFLAGS="-O2 -std=c++14" CFLAGS="-O2 -std=c++14"
