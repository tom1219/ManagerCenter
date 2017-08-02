sed -i -e s/{name}/ManagerCenter/g Makefile.am
aclocal
autoheader
autoconf
automake --add-missing
./configure CXXFLAGS="-g -O0 -std=c++14 -D__DEBUG" CFLAGS="-g -O0 -std=c++14 -D__DEBUG"
