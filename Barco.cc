/** @file Barco.cc
    @brief Código de la clase Barco.
*/

#include "Barco.hh"

// Constructoras

// Pre: cierto.
// Post: Crea un barco no inicializado.
 
Barco::Barco() {
}

// Pre: num_comprar > 0, num_vender > 0, ID de comprar y vender correctas.
// Post: El barco contiene el ID del producto que comprar,
// vender, y el número de elementos de ambos.

Barco::Barco(int id_producto_comprar, int num_comprar, int id_producto_vender, int num_vender) {
    _id_prod_comprar = id_producto_comprar;
    _num_comprar = num_comprar;
    _id_prod_vender = id_producto_vender;
    _num_vender = num_vender;
}

// Modificadoras

// Pre: cierto.
// Post Se reinicia la lista que contiene las últimas ciudades
// visitadas en orden cronológico.

void Barco::reiniciar_lista() {
    _ult_ciudad.clear();
}

// Pre: num_comprar > 0, num_vender > 0.
// Post El barco contiene el ID del producto que comprar,
// vender, y el número de elementos de ambos.

void Barco::modificar_barco(int id_producto_comprar, int num_comprar, int id_producto_vender, int num_vender, const Cjt_productos& cp) {
    if (!cp.hay_prod(id_producto_comprar) or !cp.hay_prod(id_producto_vender)) {
        cout << "error: no existe el producto" << endl;
    } else if (id_producto_comprar == id_producto_vender) {
        cout << "error: no se puede comprar y vender el mismo producto" << endl;
    } else {
        _id_prod_comprar = id_producto_comprar;
        _num_comprar = num_comprar;
        _id_prod_vender = id_producto_vender;
        _num_vender = num_vender;
    }
}

// Pre: cierto.
// Post: Añade al barco la última ciudad visitada

void Barco::agregar_ultima_ciudad(string ultima_ciudad) {
    _ult_ciudad.push_back(ultima_ciudad);
}
  
// Consultoras

// Pre: Barco inicializado.
// Post: Devuelve la id del producto que el barco busca comprar.

int Barco::consultar_id_prod_comprar() const {
    return _id_prod_comprar;
}

// Pre: Barco inicializado.
// Post: Devuelve la id del producto que el barco busca vender.

int Barco::consultar_id_prod_vender() const {
    return _id_prod_vender;
}

// Pre: Barco inicializado.
// Post: Devuelve el número de productos que el barco busca comprar.

int Barco::consultar_num_comprar() const {
    return _num_comprar;
}

// Pre: Barco inicializado.
// Post: Devuelve el número de productos que el barco busca vender.

int Barco::consultar_num_vender() const {
    return _num_vender;
}

// Escritura

// Pre: Barco inicializado.
// Post: Se escribe por el canal estándard de salida la información de la ID de producto que comprar,
// vender, y el número de elementos de ambos. También se escriben
// las últimas ciudades de los diferentes viajes en orden cronológico.

void Barco::escribir_barco() const {
    cout << _id_prod_comprar << ' ' << _num_comprar << ' ' << _id_prod_vender << ' ' << _num_vender << endl;
    for (auto it = _ult_ciudad.begin(); it != _ult_ciudad.end(); ++it) {
        cout << *it << endl;
    }
}

