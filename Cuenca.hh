/** @file Cuenca.hh
    @brief Especificación de la clase Cuenca.
*/

#ifndef CUENCA_HH
#define CUENCA_HH

#include "Cjt_productos.hh"
#include "Ciudad.hh"
#include "Barco.hh"

#ifndef NO_DIAGRAM
#include "BinTree.hh"
#endif

/** @class Cuenca
    @brief Representa una cuenca, con sus respectivas ciudades.
    
    Permite gestionar una estructura fluvial compuesta por un río principal y varios afluentes, 
    con ciudades ubicadas en puntos específicos como las fuentes y las confluencias de los ríos. 
    Proporciona diversas operaciones para gestionar la lectura y escritura de datos de la cuenca, 
    redistribuir productos entre las ciudades, y realizar operaciones comerciales mediante un barco.
*/

class Cuenca
{

private:
  /** @brief Struct para optimizar función hacer_viaje */
  struct ElementoCamino {
    string id_ciudad;
    int unidades_c; // Almacena las operaciones que hacemos dentro de encontrar_camino
    int unidades_v; // para que el código sea más eficiente y no repetir cálculos
  };
  /** @brief Conjunto de ID's de ciudades ordenado árboreamente río arriba. */
  BinTree<string> _id_ciudades;
  /** @brief Contenedor donde relacionar ID con ciudad. */
  map<string, Ciudad> _lista_ciudades;
  
  // Métodos privados

  /** @brief Operación auxiliar de leer_rio.
      \pre En el canal estándar de entrada se encuentran strings con nombres
      de ciudades y "#" que forman una estructura árborea binaria válida. 
      \post Se ha leído un árbol binario desde el canal estándar de entrada en preorden.
       Cada nodo contiene un nombre de ciudad, y los nodos hoja se representan con "#".
       Se devuelve un BinTree<string> que representa la estructura leída.
  */   
  BinTree<string> leer_rio_rec();

  /** @brief Operación auxiliar de redistribuir.
      \pre El árbol t contiene nombres de ciudades correctos.
      \post La ciudad en el nodo actual ha comerciado con la ciudad en su subárbol izquierdo, si existe.
       Después de procesar el subárbol izquierdo, la ciudad en el nodo actual ha comerciado con la ciudad en su subárbol derecho, si existe.
       La función se llama recursivamente para los subárboles izquierdo y derecho, siguiendo un recorrido en preorden.
  */  
  void redistribuir_rec(BinTree<string>& t, const Cjt_productos& cp);

  // FORMATO DOXYGEN
  void hacer_camino(const list<ElementoCamino>& ruta, const Cjt_productos& cp, Barco& b); // Función auxiliar para la operación hacer viaje.
  pair<int,int> encontrar_camino(const BinTree<string>& t, Barco& b, int compradas, int vendidas, list<ElementoCamino>& ruta); // Función auxiliar para la operación hacer viaje.

public:
  // Constructora

  /** @brief Creadora por defecto. 
      Se ejecuta automáticamente al declarar una cuenca.
      \pre <em>cierto</em>
      \post El resultado es una cuenca no inicializada.
  */   
  Cuenca();
  
  // Modificadoras

  /** @brief Lectura inicial del barco
      \pre En el canal estándar de entrada se encuentra un entero no negativo, seguido
      de una lista de productos no repetidos con el formato correcto, una estructura árborea 
      correcta de strings e ID's de comprar y vender válidas, num_comprar y vender > 0.
      \post Se hace la lectura de la cuenca, de los productos y del barco.
  */

  void lectura_inicial(Cjt_productos& cp, Barco &b);

  /** @brief Acción de redistribuir.
      \pre cp es un conjunto de productos válido, inicializado y consistente con los productos en las ciudades.
      \post La ciudad de la desembocaduraha comerciado con su ciudad río arriba a la derecha y
      luego con la ciudad río arriba a la izquierda, sucesivamente.
  */
  void redistribuir(const Cjt_productos& cp);

  /** @brief Acción de hacer viaje.
      \pre Barco inicializado.
      \post El barco sigue la ruta más corta para comprar y vender los
      productos, modificando los inventarios de las ciudades. Escribe
      el total de unidades compradas y vendidas del barco.
  */
  void hacer_viaje(Barco& b, const Cjt_productos& cp);

  /** @brief Acción de comerciar.
      \pre Las ID's de las ciudades representan ciudades con inventarios que contienen productos con IDs válidos y consistentes 
      respecto al conjunto de productos, que debe contener información válida sobre los productos, de sus pesos y volúmenes.
      \post Se han intercambiado los productos que le sobran a una
      ciudad y que necesite la otra. Los inventarios de ambas ciudades se han actualizado.
      Los atributos de peso y volumen total de ambas ciudades se han ajustado adecuadamente.
  */
  void comerciar(string id_ciudad1, string id_ciudad2, const Cjt_productos& cp);

  /** @brief Modificadora para añadir producto a ciudad.
      \pre prod_tiene + prod_necesita > 0
      \post Añade el producto al inventario de la ciudad.
  */
  void poner_prod(string id_ciudad, int id_producto, int prod_tiene, int prod_necesita, const Cjt_productos& cp);

  /** @brief Modificadora de producto de ciudad.
      \pre prod_tiene + prod_necesita > 0
      \post Modifica los datos del inventario de la ciudad.
  */
  void modificar_prod(string id_ciudad, int id_producto, int prod_tiene, int prod_necesita, const Cjt_productos& cp);

  /** @brief Modificadora para eliminar producto de ciudad.
      \pre <em>cierto</em>
      \post Quita un producto del inventario.
  */
  void quitar_prod(string id_ciudad, int id_producto, const Cjt_productos& cp);
  
  // Consultoras

   /** @brief Consultora de existencia ciudad.
      \pre <em>cierto</em>
      \post Devuelve true si existe la ciudad, false de lo contrario.
  */
  bool hay_ciudad(string id_ciudad) const;

  /** @brief Consultora de existencia de producto en ciudad.
      \pre <em>cierto</em>
      \post Escribe true si el producto está en el inventario, falso de lo contrario.
  */
  bool hay_prod_ciudad(string id_ciudad, int id_producto) const;

  /** @brief Operación para consultar un producto de una ciudad.
      \pre <em>cierto</em>
      \post Escribe cuántas unidades de ese producto tiene y necesita la ciudad indicada.
  */
  void consultar_prod_ciudad(string id_ciudad, int id_producto, const Cjt_productos& cp) const;

 // Escritura

  /** @brief Operación de escritura de una ciudad.
      \pre <em>cierto</em>
      \post Se ha escrito el inventario, peso y volumen total de la ciudad en el canal estándard
      de salida.
  */
  void escribir_ciudad(string id_ciudad) const;

  // Lectura

  /** @brief Operación de lectura de la estructura de la cuenca.
      \pre En el canal estándar de entrada se encuentran strings con nombres
      de ciudades y "#" que forman una estructura árborea binaria válida. 
      \post Se han leído los nombres de las ciudades indicando la estructura de la cuenca.
  */
  void leer_rio();

  /** @brief Operación de lectura de los inventarios de las ciudades.
      \pre En el canal estándar de entrada se encuentran uno o más strings representando
      una ID de ciudad y por cada string, un entero no negativo. Posteriormente, se leen
      tres enteros el número de veces indicado por el anterior entero, todos 
      estrictamente positivos excepto el segundo que puede ser cero.
      \post Se han leído los inventarios de las ciudades.
  */
  void leer_inventarios(const Cjt_productos& cp);    

  /** @brief Operación de lectura de un inventario.
      \pre En el canal estándar de entrada se encuentran un string representando
      una ID de ciudad y un entero no negativo. Posteriormente, se leen
      tres enteros el número de veces indicado por el anterior entero, todos 
      estrictamente positivos excepto el segundo que puede ser cero.
      \post Se ha leído el inventario de la ciudad.
  */
  void leer_inventario(string id_ciudad, const Cjt_productos& cp);
};

#endif