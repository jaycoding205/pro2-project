/** @file Cjt_productos.cc
    @brief Código de la clase Conjunto de Productos.
*/

#include "Cjt_productos.hh"

// Constructora

// Pre: cierto.
// Post: Crea un conjunto de productos sin ningún elemento.

Cjt_productos::Cjt_productos() {
    _num_prod = 0;
}

// Consultoras

// Pre: Existe la id del producto.
// Post Devuelve cierto si el producto existe, falso en caso contrario.

bool Cjt_productos::hay_prod(int id_producto) const {
    return _productos.find(id_producto) != _productos.end();
}

// Pre: cierto.
// Post: El resultado es el número de productos diferentes.

int Cjt_productos::consultar_num() const {
    return _num_prod;
}

// Pre: Existe la id del producto.
// Post: Devuelve el peso del producto.

int Cjt_productos::consultar_peso_producto(int id_producto) const {
    auto it = _productos.find(id_producto);
    return it->second.consultar_peso();
}

// Pre: Existe la id del producto.
// Post Devuelve el volumen del producto.

int Cjt_productos::consultar_volumen_producto(int id_producto) const {
    auto it = _productos.find(id_producto);
    return it->second.consultar_volumen();
}

// Escritura

// Pre: cierto.
// Post: Se ha escrito el ID, peso y volumen del producto en el canal estándard
// de salida.

void Cjt_productos::escribir_producto(int id_producto) const {
    if (hay_prod(id_producto)) {
        cout << id_producto << ' ';
        auto it = _productos.find(id_producto);
        it->second.escribir_producto();
    } else {
        cout << "error: no existe el producto" << endl;
    }
}

// Lectura

// Pre: En el canal estándar de entrada se encuentran dos enteros
// no negativos num_productos veces que representan el peso y volumen
// de un producto. Los productos no podían existir anteriormente.
// Post: Se han leído los nuevos productos.

void Cjt_productos::agregar_productos(int num_productos) {
    for (int i = 0; i < num_productos; ++i) {
        Producto p;
        p.leer_producto();
        // Indexamos las ID's empezando por 1.
        _productos[_num_prod+1] = p;
        _num_prod++;
    }
}