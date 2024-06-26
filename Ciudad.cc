/** @file Ciudad.cc
    @brief Código de la clase Ciudad.
*/

#include "Ciudad.hh"

// Constructora

// Pre: cierto.
// Post: El resultado es una ciudad no inicializada.

Ciudad::Ciudad() {
    _peso_total = 0;
    _volumen_total = 0;
}

// Modificadoras

// Pre: cierto.
// Post Se venden los productos indicados al barco.

void Ciudad::vender_prod(int id_producto, int vendidos, const Cjt_productos& cp) {
    _peso_total -= cp.consultar_peso_producto(id_producto) * vendidos;
    _volumen_total -= cp.consultar_volumen_producto(id_producto)* vendidos;
    auto it = _inv.find(id_producto); // Verificamos producto en ciudad.
    if (it != _inv.end()) {
        it->second._prod_tiene -= vendidos;
        if (it->second._prod_necesita == 0 and it->second._prod_necesita == 0) {
            _inv.erase(id_producto); // Si no tiene ni necesita, lo borramos.
        }
    }
}

// Pre: cierto.
// Post Se venden los productos indicados al barco.

void Ciudad::comprar_prod(int id_producto, int comprados, const Cjt_productos& cp) {
    _peso_total += cp.consultar_peso_producto(id_producto) * comprados;
    _volumen_total += cp.consultar_volumen_producto(id_producto)* comprados;
    auto it = _inv.find(id_producto);
    if (it != _inv.end()) { // Verificamos producto en ciudad.
        it->second._prod_tiene += comprados;
    }
}

// Pre: prod_tiene + prod_necesita > 0.
// Post: La ciudad pasa a tener el nuevo producto en el inventario.
// Se escribe el peso y volumen total.

void Ciudad::poner_prod(int id_producto, int prod_tiene, int prod_necesita, const Cjt_productos& cp) {
    inventario inv;
    // Verificamos errores en función de cuenca.

    _peso_total += cp.consultar_peso_producto(id_producto) * prod_tiene;
    _volumen_total += cp.consultar_volumen_producto(id_producto) * prod_tiene;
    inv._prod_tiene = prod_tiene;
    inv._prod_necesita = prod_necesita;
    _inv[id_producto] = inv;

    cout << _peso_total << ' ' << _volumen_total << endl;
}

// Pre: prod_tiene + prod_necesita > 0.
// Post: Los datos del producto indicado pasan a ser los nuevos.
// Se escribe el peso y volumen total.

void Ciudad::modificar_prod(int id_producto, int prod_tiene, int prod_necesita, const Cjt_productos& cp) {
    inventario inv;
    // Verificamos errores en función de cuenca.
    int volumen = cp.consultar_volumen_producto(id_producto);
    int peso = cp.consultar_peso_producto(id_producto);

    _peso_total -= peso * _inv[id_producto]._prod_tiene;
    _volumen_total -= volumen * _inv[id_producto]._prod_tiene;
    _peso_total += peso * prod_tiene;
    _volumen_total += volumen * prod_tiene;
    inv._prod_tiene = prod_tiene;
    inv._prod_necesita = prod_necesita;
    _inv[id_producto] = inv;

    cout << _peso_total << ' ' << _volumen_total << endl;
}

// Pre: cierto.
// Post: Se elimina el producto del inventario.
// Se escribe el peso y volumen total.

void Ciudad::quitar_prod(int id_producto, const Cjt_productos& cp) {
    // Verificamos errores en función de cuenca.
    _peso_total -= cp.consultar_peso_producto(id_producto) * _inv[id_producto]._prod_tiene;
    _volumen_total -= cp.consultar_volumen_producto(id_producto) * _inv[id_producto]._prod_tiene;
    _inv.erase(id_producto);

    cout << _peso_total << ' ' << _volumen_total << endl;
}

// Pre: El parámetro implícito y la ciudad c2 están correctamente inicializados y sus inventarios
// contienen productos con IDs válidos y consistentes respecto al conjunto de productos, que debe contener
// información válida sobre los productos, de sus pesos y volúmenes.

// Post: Se han intercambiado los productos que le sobran a una
// ciudad y que necesite la otra. Los inventarios de ambas ciudades se han actualizado.
// Los atributos de peso y volumen total de ambas ciudades se han ajustado adecuadamente.

void Ciudad::comerciar(Ciudad& c2, const Cjt_productos& cp) {
    auto it1 = _inv.begin(); // Iterador para la primera ciudad.
    auto it2 = c2._inv.begin(); // Iterador para la segunda ciudad.
    
    // Recorremos ambos inventarios simultáneamente.
    while (it1 != _inv.end() and it2 != c2._inv.end()) {
        // Si los productos coinciden en ambos inventarios:
        if (it1->first == it2->first) {
            int excedente1 = it1->second._prod_tiene - it1->second._prod_necesita;
            int excedente2 = it2->second._prod_tiene - it2->second._prod_necesita;

            // Si a la primera ciudad le sobran y a la segunda le faltan:
            if (excedente1 > 0 and excedente2 < 0) {
                // Actualizamos los inventarios y atributos de ambas ciudades
                int min_balance = min(excedente1, abs(excedente2));
                it1->second._prod_tiene -= min_balance;
                it2->second._prod_tiene += min_balance;
                int volumen = cp.consultar_volumen_producto(it1->first);
                int peso = cp.consultar_peso_producto(it1->first);

                _peso_total -= min_balance * peso;
                _volumen_total -= min_balance * volumen;
                c2._peso_total += min_balance * peso;
                c2._volumen_total += min_balance * volumen;
            }
            // Si a la primera ciudad le faltan y a la segunda le sobran:
            else if (excedente1 < 0 and excedente2 > 0) {
                // Actualizamos los inventarios y atributos de ambas ciudades
                int min_balance = min(abs(excedente1), excedente2);
                it2->second._prod_tiene -= min_balance;
                it1->second._prod_tiene += min_balance;
                int volumen = cp.consultar_volumen_producto(it1->first);
                int peso = cp.consultar_peso_producto(it1->first);

                c2._peso_total -= min_balance * peso;
                c2._volumen_total -= min_balance * volumen;
                _peso_total += min_balance * peso;
                _volumen_total += min_balance * volumen;
            }
            ++it1; // Avanzamos ambos iteradores.
            ++it2;
        }
        // Si la ID del producto de la primera ciudad es menor que el de la segunda, avanzamos el iterador de la primera.
        else if (it1->first < it2->first) {
            ++it1;
        }
        // Si la ID del producto de la segunda ciudad es menor que el de la segunda, avanzamos el iterador de la segunda.
        else {
            ++it2;
        }
    }
}
  
// Consultoras

// Pre: El producto pertenece a la ciudad.
// Post: Devuelve cuántas unidades de ese producto tiene la ciudad.

int Ciudad::consultar_tiene_ciudad(int id_producto) const {
    return _inv.at(id_producto)._prod_tiene;
}

// Pre: El producto pertenece a la ciudad.
// Post: Devuelve cuántas unidades de ese producto necesita la ciudad.

int Ciudad::consultar_necesita_ciudad(int id_producto) const {
    return _inv.at(id_producto)._prod_necesita;
}

// Pre: El producto pertenece a la ciudad.
// Post: Devuelve cuántas unidades de ese producto tiene y necesita la ciudad.

void Ciudad::consultar_prod_ciudad(int id_producto) const {
    auto it = _inv.find(id_producto);
    cout << it->second._prod_tiene << ' ' << it->second._prod_necesita << endl;
}

// Pre: El producto pertenece a la ciudad.
// Post: Devuelve cuántas unidades de ese producto tiene la ciudad menos las que necesita.

int Ciudad::consultar_necesitareal_ciudad(int id_producto) const {
    return _inv.at(id_producto)._prod_tiene - _inv.at(id_producto)._prod_necesita;
}

// Pre: cierto.
// Post: Devuelve true si el producto está en el inventario, falso de lo contrario.

bool Ciudad::hay_prod_ciudad(int id_producto) const {
    return _inv.find(id_producto) != _inv.end();
}

// Escritura

// Pre: cierto.
// Post: Se ha escrito el inventario, peso y volumen total de la ciudad por el canal estándard de salida.

void Ciudad::escribir_ciudad() const {
    for (auto it = _inv.begin(); it != _inv.end(); ++it) {
        cout << it->first << ' ' << it->second._prod_tiene << ' ' << it->second._prod_necesita << endl;
    }
    cout << _peso_total << ' ' << _volumen_total << endl;
}


// Lectura

// Pre: En el canal estándar de entrada se encuentra un entero no negativo.
// Posteriormente, se leen tres enteros el número de veces indicado por el anterior entero, 
// todos estrictamente positivos excepto el segundo que puede ser cero.
// Post: Se ha leído el inventario de la ciudad.
void Ciudad::leer_inventario(const Cjt_productos& cp) {
    _inv.clear(); // Limpiamos el inventario anterior.
    _peso_total = 0; // Reiniciamos el peso y volumen total.
    _volumen_total = 0;

    int num_elem;
    cin >> num_elem;

    for (int i = 0; i < num_elem; ++i) {
        int id_producto, prod_tiene, prod_necesita;
        cin >> id_producto >> prod_tiene >> prod_necesita;

        _peso_total += cp.consultar_peso_producto(id_producto) * prod_tiene;
        _volumen_total += cp.consultar_volumen_producto(id_producto) * prod_tiene;
        
        inventario inv;
        inv._prod_tiene = prod_tiene;
        inv._prod_necesita = prod_necesita;
        _inv[id_producto] = inv;
    }
}