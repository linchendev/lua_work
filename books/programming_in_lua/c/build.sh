#g++ $1 -I./ -I/usr/local/include/ -L/usr/local/lib/ /usr/local/lib/liblua.a
g++ $1 -I./ -I/usr/local/include/ -L/usr/local/lib/ -lm -ldl /usr/local/lib/liblua.a

