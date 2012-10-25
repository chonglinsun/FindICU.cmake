1) Move into test's directory (cd /.../FindICU.cmake/tests/RB/c_pkg_shared)
2) Configure it: cmake . -DCMAKE_INSTALL_PREFIX=/tmp
3) Build it: make
4) Install it: make install
5) Move to installation directory: cd /tmp/bin
6) Run it: ./rb
Don't forget to redefine LD_LIBRARY_PATH (or equivalent) for a non standard location (export LD_LIBRARY_PATH=/tmp/bin:$LD_LIBRARY_PATH)

If it works as expected, you should read as output:
   translation enabled: fr
   ...
   fr.txt

(the most important line is the last one)
