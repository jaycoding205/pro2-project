OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11 -fno-extended-identifiers

program.exe: Barco.o Producto.o Cjt_productos.o Ciudad.o Cuenca.o program.o
	g++ -o program.exe Barco.o Producto.o Cjt_productos.o Ciudad.o Cuenca.o program.o

Barco.o: Barco.cc Barco.hh
	g++ -c Barco.cc $(OPCIONS)

Producto.o: Producto.cc Producto.hh
	g++ -c Producto.cc $(OPCIONS)

Cjt_productos.o: Cjt_productos.cc Cjt_productos.hh
	g++ -c Cjt_productos.cc $(OPCIONS)

Ciudad.o: Ciudad.cc Ciudad.hh
	g++ -c Ciudad.cc $(OPCIONS)

Cuenca.o: Cuenca.cc Cuenca.hh
	g++ -c Cuenca.cc $(OPCIONS)

program.o: program.cc
	g++ -c program.cc $(OPCIONS)

clean:
	rm -f *.o
	rm -f *.exe *.tar

tar:
	tar cvf practica.tar program.cc Barco.cc Barco.hh Producto.cc Producto.hh Cjt_productos.cc Cjt_productos.hh Ciudad.cc Ciudad.hh Cuenca.cc Cuenca.hh BinTree.hh Makefile