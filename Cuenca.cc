/** @file Cuenca.cc
    @brief Código de la clase Cuenca
*/

#include "Cuenca.hh"

// Constructora

// Pre: cierto.
// Post: Devuelve una cuenca no inicializada.

Cuenca::Cuenca() {}
  
// Modificadoras

// Pre: En el canal estándar de entrada se encuentra un entero no negativo, seguido
// de una lista de productos no repetidos con el formato correcto, una estructura árborea 
// correcta de strings e ID's de comprar y vender válidas, num_comprar y vender > 0.
// Post: Se hace la lectura de la cuenca, de los productos y del barco.

void Cuenca::lectura_inicial(Cjt_productos& cp, Barco &b) {
    // Número de productos diferentes y añadirlos
    int num_productos;
    cin >> num_productos;
    cp.agregar_productos(num_productos);

    // Estructura de la cuenca
    leer_rio();

    // Datos barco
    int id_producto_comprar, num_comprar, id_producto_vender, num_vender;
    cin >> id_producto_comprar >> num_comprar >> id_producto_vender >> num_vender;
    b = Barco(id_producto_comprar, num_comprar, id_producto_vender, num_vender);
}

// Pre: El árbol t contiene nombres de ciudades correctos.
// Post: La ciudad en el nodo actual ha comerciado con la ciudad en su subárbol izquierdo, si existe.
// Después de procesar el subárbol izquierdo, la ciudad en el nodo actual ha comerciado con la ciudad en su subárbol derecho, si existe.
// La función se llama recursivamente para los subárboles izquierdo y derecho, siguiendo un recorrido en preorden.

void Cuenca::redistribuir_rec(BinTree<string>& t, const Cjt_productos& cp) {
    if (t.empty()) return; // Caso base, árbol vacío.

    // Caso recursivo:
    BinTree<string> left = t.left();
    BinTree<string> right = t.right();
    string id1 = t.value();
    // Empezamos por la izquierda.
    if (not t.left().empty()) { 
        string id2 = left.value();
        _lista_ciudades[id1].comerciar(_lista_ciudades[id2], cp);
    }
    redistribuir_rec(left, cp);
    if (not t.right().empty()) {
        string id2 = right.value();
        _lista_ciudades[id1].comerciar(_lista_ciudades[id2], cp);
    }
    redistribuir_rec(right, cp);
}

// Pre: cp es un conjunto de productos válido, inicializado y consistente con los productos en las ciudades.
// Post: La ciudad de la desembocaduraha comerciado con su ciudad río arriba a la derecha y
// luego con la ciudad río arriba a la izquierda, sucesivamente.

void Cuenca::redistribuir(const Cjt_productos& cp) {
    redistribuir_rec(_id_ciudades, cp); // Llamamos a la función auxiliar.
}

// Pre: cierto.
// Post: El barco sigue la ruta más corta para comprar y vender los
// productos, modificando los inventarios de las ciudades. Escribe
// el total de unidades compradas y vendidas del barco.

void Cuenca::hacer_viaje(Barco& b, const Cjt_productos& cp) {
    list<ElementoCamino> ruta;
    pair<int,int> res = encontrar_camino(_id_ciudades, b, 0, 0, ruta);
    int total = res.first + res.second; // Total de productos comprados y vendidos.
    cout << total << endl;
        
    if(total != 0){ // Si no se ha comerciado.
        hacer_camino(ruta, cp, b);
        b.agregar_ultima_ciudad((ruta.back()).id_ciudad);
    }
}

// Pre: cierto.
// Post: Hace las compras y ventas pasando por la ruta y modificando las ciudades.

void Cuenca::hacer_camino(const list<ElementoCamino>& ruta, const Cjt_productos& cp, Barco& b) {
    for (auto it = ruta.begin(); it != ruta.end(); ++it) {
        auto it2 = _lista_ciudades.find((*it).id_ciudad);
        it2->second.vender_prod(b.consultar_id_prod_comprar(), (*it).unidades_c, cp);
        it2->second.comprar_prod(b.consultar_id_prod_vender(), (*it).unidades_v, cp);
    }
}

// Pre: cierto.
// Post: Encuentra el camino que cumple las condiciones pedidas.

pair<int,int> Cuenca::encontrar_camino(const BinTree<string>& t, Barco& b, int compradas, int vendidas, list<ElementoCamino>& ruta) {
    if (t.empty() or (compradas == b.consultar_num_comprar() and vendidas == b.consultar_num_vender())) {
        ruta = list<ElementoCamino>();
        return make_pair(0,0);
    } else {
        auto it = _lista_ciudades.find(t.value());
        int unidades_c = 0;
        int unidades_v = 0;
        if ((*it).second.hay_prod_ciudad(b.consultar_id_prod_comprar())) {
            int sobra_ciudad_c = (*it).second.consultar_necesitareal_ciudad(b.consultar_id_prod_comprar());
            if(sobra_ciudad_c > 0){ // Le sobran, podemos comprar.
                if (sobra_ciudad_c <= b.consultar_num_comprar()-compradas) {
                    unidades_c = sobra_ciudad_c;
                } else {
                    unidades_c = b.consultar_num_comprar()-compradas;
                }
            }
        }
        if ((*it).second.hay_prod_ciudad(b.consultar_id_prod_vender())) {
            int sobra_ciudad_v = (*it).second.consultar_necesitareal_ciudad(b.consultar_id_prod_vender());
            if(sobra_ciudad_v < 0){ // Le faltan, podemos vender.
                sobra_ciudad_v = -sobra_ciudad_v;
                if (sobra_ciudad_v <= b.consultar_num_vender()-vendidas) {
                    unidades_v = sobra_ciudad_v;
                } else {
                    unidades_v = b.consultar_num_vender()-vendidas;
                }
            }
        }

        list<ElementoCamino> ruta_izq, ruta_der;
        pair<int,int> res_izq = encontrar_camino(t.left(), b, compradas+unidades_c, vendidas+unidades_v, ruta_izq);
        int sumaleft = res_izq.first+res_izq.second;
        pair<int,int> res_der = encontrar_camino(t.right(), b, compradas+unidades_c, vendidas+unidades_v, ruta_der);
        int sumaright = res_der.first+res_der.second;
    
        pair<int,int> ruta_mejor;
        list<ElementoCamino> ruta_esc;
        
        // Escogemos la mejor ruta.
        if (sumaleft < sumaright) {
            ruta_mejor = res_der;
            ruta_esc = ruta_der;
        }
        else if(sumaleft > sumaright){
            ruta_mejor = res_izq;
            ruta_esc = ruta_izq;
        }
        else{
            if(ruta_izq.size() <= ruta_der.size()){
                ruta_mejor = res_izq;
                ruta_esc = ruta_izq;
            }   
            else{
                ruta_mejor = res_der;
                ruta_esc = ruta_der;
            }
        }

        // Hacer push cuando solo cuando sea necesario.
        if (unidades_c > 0 or unidades_v > 0 or !ruta_esc.empty()) {
            ElementoCamino ec;
            ec.id_ciudad = t.value();
            ec.unidades_c = unidades_c;
            ec.unidades_v = unidades_v;
            ruta_esc.push_front(ec);
        }
        // Asignamos la ruta correcta.
        ruta = ruta_esc;

        // Actualizamos los productos que hemos comerciado.
        return make_pair(ruta_mejor.first+unidades_c, ruta_mejor.second+unidades_v);
    }
}

// Pre: Las ID's de las ciudades representan ciudades con inventarios que contienen productos con IDs válidos y consistentes 
// respecto al conjunto de productos, que debe contener información válida sobre los productos, de sus pesos y volúmenes.
// Post: Se han intercambiado los productos que le sobran a una
// ciudad y que necesite la otra. Los inventarios de ambas ciudades se han actualizado.
// Los atributos de peso y volumen total de ambas ciudades se han ajustado adecuadamente.

void Cuenca::comerciar(string id_ciudad1, string id_ciudad2, const Cjt_productos& cp) {
    if (not hay_ciudad(id_ciudad1) or not hay_ciudad(id_ciudad2)) {
        cout << "error: no existe la ciudad" << endl;
    } else if (id_ciudad1 == id_ciudad2) {
        cout << "error: ciudad repetida" << endl;
    } else {
        _lista_ciudades[id_ciudad1].comerciar(_lista_ciudades[id_ciudad2], cp);
    }
}

// Pre: prod_tiene + prod_necesita > 0
// Post: Añade el producto al inventario de la ciudad.

void Cuenca::poner_prod(string id_ciudad, int id_producto, int prod_tiene, int prod_necesita, const Cjt_productos& cp) {
    if (not cp.hay_prod(id_producto)) {
        cout << "error: no existe el producto" << endl;
    } else if (not hay_ciudad(id_ciudad)) {
        cout << "error: no existe la ciudad" << endl;
    } else if (hay_prod_ciudad(id_ciudad, id_producto)) {
        cout << "error: la ciudad ya tiene el producto" << endl;
    } else {
        _lista_ciudades[id_ciudad].poner_prod(id_producto, prod_tiene, prod_necesita, cp);
    }
}

// Pre: prod_tiene + prod_necesita > 0
// Post: Modifica los datos del inventario de la ciudad.

void Cuenca::modificar_prod(string id_ciudad, int id_producto, int prod_tiene, int prod_necesita, const Cjt_productos& cp) {
    if (not cp.hay_prod(id_producto)) {
        cout << "error: no existe el producto" << endl;
    } else if (not hay_ciudad(id_ciudad)) {
        cout << "error: no existe la ciudad" << endl;
    } else if (not hay_prod_ciudad(id_ciudad, id_producto)) {
        cout << "error: la ciudad no tiene el producto" << endl;
    } else {
        _lista_ciudades[id_ciudad].modificar_prod(id_producto, prod_tiene, prod_necesita, cp);
    }
}

// Pre: cierto.
// Post: Quita un producto del inventario.

void Cuenca::quitar_prod(string id_ciudad, int id_producto, const Cjt_productos& cp) {
    if (!cp.hay_prod(id_producto)) {
        cout << "error: no existe el producto" << endl;
    } else if (not hay_ciudad(id_ciudad)) {
        cout << "error: no existe la ciudad" << endl;
    } else if (not hay_prod_ciudad(id_ciudad, id_producto)) {
        cout << "error: la ciudad no tiene el producto" << endl;
    } else {
        _lista_ciudades[id_ciudad].quitar_prod(id_producto, cp);
    }
}
  
// Consultoras

// Pre: cierto.
// Post: Devuelve true si existe la ciudad, false de lo contrario.

bool Cuenca::hay_ciudad(string id_ciudad) const {
    return _lista_ciudades.find(id_ciudad) != _lista_ciudades.end();
}

// Pre: cierto.
// Post: Escribe true si el producto está en el inventario, falso de lo contrario.

bool Cuenca::hay_prod_ciudad(string id_ciudad, int id_producto) const {
    return _lista_ciudades.at(id_ciudad).hay_prod_ciudad(id_producto);
}

// Pre: cierto.
// Post: Devuelve el producto consultado.

void Cuenca::consultar_prod_ciudad(string id_ciudad, int id_producto, const Cjt_productos& cp) const {
    if (not cp.hay_prod(id_producto)) {
        cout << "error: no existe el producto" << endl;
    } else if (not hay_ciudad(id_ciudad)) {
        cout << "error: no existe la ciudad" << endl;
    } else if (not hay_prod_ciudad(id_ciudad, id_producto)) {
        cout << "error: la ciudad no tiene el producto" << endl;
    } else {
        _lista_ciudades.at(id_ciudad).consultar_prod_ciudad(id_producto);
    }
}

// Escritura

// Pre: cierto.
// Post: Se ha escrito el inventario, peso y volumen total de la ciudad en el canal estándard
// de salida.

void Cuenca::escribir_ciudad(string id_ciudad) const {
    if (hay_ciudad(id_ciudad)) {
        _lista_ciudades.at(id_ciudad).escribir_ciudad();
    } else {
        cout << "error: no existe la ciudad" << endl;
    }
}

// Lectura

// Pre: En el canal estándar de entrada se encuentran strings con nombres
// de ciudades y "#" que forman una estructura árborea binaria válida. 
// Post: Se han leído los nombres de las ciudades indicando la estructura de la cuenca.

void Cuenca::leer_rio() {
    _lista_ciudades.clear();
    _id_ciudades = leer_rio_rec(); // Se reinicia correctamente?
}

// Pre: En el canal estándar de entrada se encuentran strings con nombres
// de ciudades y "#" que forman una estructura árborea binaria válida. 
// Post: Se ha leído un árbol binario desde el canal estándar de entrada en preorden.
    // Cada nodo contiene un nombre de ciudad, y los nodos hoja se representan con "#".
    // Se devuelve un BinTree<string> que representa la estructura leída.

BinTree<string> Cuenca::leer_rio_rec() {
    string id_ciudad;
    cin >> id_ciudad;

    // Leemos en preorden
    if (id_ciudad != "#") {
        Ciudad c;
        _lista_ciudades[id_ciudad] = c;
        BinTree<string> left = leer_rio_rec();
        BinTree<string> right = leer_rio_rec();
        return BinTree<string>(id_ciudad, left, right);
    } else {
        return BinTree<string>();
    }
}

// Pre: En el canal estándar de entrada se encuentran uno o más strings representando
// una ID de ciudad y por cada string, un entero no negativo. Posteriormente, se leen
// tres enteros el número de veces indicado por el anterior entero, todos 
// estrictamente positivos excepto el segundo que puede ser cero.
// Post: Se han leído los inventarios de las ciudades.

void Cuenca::leer_inventarios(const Cjt_productos& cp) {
    string id_ciudad;
    while (cin >> id_ciudad and id_ciudad != "#") {
        _lista_ciudades[id_ciudad].leer_inventario(cp);
    }
}    

// Pre: En el canal estándar de entrada se encuentran un string representando
// una ID de ciudad y un entero no negativo. Posteriormente, se leen
// tres enteros el número de veces indicado por el anterior entero, todos 
// estrictamente positivos excepto el segundo que puede ser cero.
// Post: Se ha leído el inventario de la ciudad.

void Cuenca::leer_inventario(string id_ciudad, const Cjt_productos& cp) {
    if (hay_ciudad(id_ciudad)) {
            _lista_ciudades[id_ciudad].leer_inventario(cp);
    } else {
            cout << "error: no existe la ciudad" << endl;
    }
}