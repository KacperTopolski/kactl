c() {
 g++ -std=c++20 -Wall -Wextra -Wshadow -Wconversion \
 -Wno-sign-conversion -Wfloat-equal -D_GLIBCXX_DEBUG \
 -D_GLIBCXX_DEBUG_PEDANTIC -fsanitize=address,undefined \
 -ggdb3 -DLOC $1.cpp -o$1; }
cf() { g++ -std=c++20 -static -O3 -DLOCF $1.cpp -o$1; }
libhash() { cat $1.cpp | cpp -dD -P -fpreprocessed | \
tr -d '[:space:]'| md5sum |cut -c-6; }