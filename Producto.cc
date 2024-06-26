/** @file Producto.cc
    @brief Código de la clase Producto.
*/

#include "Producto.hh"

// Constructora
  
Producto::Producto() {}

// Consultoras

// Pre: Producto inicializado.
// Post: El resultado es el peso del parámetro implícito.

int Producto::consultar_peso() const {
    return _peso;
}

// Pre: Producto inicializado.
// Post: El resultado es el volumen del parámetro implícito.
 
int Producto::consultar_volumen() const {
    return _volumen;
}

// Escritura

// Pre: Producto inicializado.
// Post: Se ha escrito el ID, peso y volumen del parámetro implícito
// en el canal estándar de salida.

void Producto::escribir_producto() const {
    cout << _peso << ' ' << _volumen << endl;
}

// Lectura

// Pre: En el canal estándar de entrada se encuentran dos enteros no negativos 
// que representan el peso y el volumen que se van a leer. 
// Post Se han leído el peso y volumen del parámetro implícito.

void Producto::leer_producto() {
    int peso;
    int volumen;
    cin >> peso >> volumen;
    _peso = peso;
    _volumen = volumen;
}