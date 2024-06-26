/** @file Ciudad.hh
    @brief Especificación de la clase Ciudad.
*/

#ifndef CIUDAD_HH
#define CIUDAD_HH

#include "Cjt_productos.hh"

#ifndef NO_DIAGRAM
#include <cmath>
#endif

/** @class Ciudad
    @brief Representa una ciudad con su inventario, peso y volumen total.

    Gestiona el inventario de productos, permitiendo la compra y venta de productos, 
    la modificación y eliminación de productos, y el comercio entre ciudades. Proporciona métodos 
    para consultar los productos que posee y necesita, así como el peso y volumen total de los productos.
*/

class Ciudad
{

private:
  /** @brief Struct de los productos que tiene y necesita */
  struct inventario {
    int _prod_tiene; // Número de productos que posee.
    int _prod_necesita;  // Número de productos que precisa.
  };
  /** @brief Conjunto ordenado de productos que relaciona ID con los productos que tiene y necesita. */
  map<int, inventario> _inv;
  /** @brief Peso total de los productos de la ciudad. */
  int _peso_total;
  /** @brief Volumen total de los productos de la ciudad. */
  int _volumen_total;

public:
  // Constructora

  /** @brief Creadora por defecto. 
      Se ejecuta automáticamente al declarar una ciudad.
      \pre <em>cierto</em>
      \post El resultado es una ciudad no inicializada.
  */   
  Ciudad();
  
  // Modificadoras

  /** @brief Modificadora para vender un producto al barco.
      \pre <em>cierto</em>
      \post Se venden los productos indicados al barco.
  */
  void vender_prod(int id_producto, int vendidos, const Cjt_productos& cp);

   /** @brief Modificadora para comprarle un producto al barco.
      \pre <em>cierto</em>
      \post Se compran los productos indicados al barco.
  */
  void comprar_prod(int id_producto, int comprados, const Cjt_productos& cp);

  /** @brief Modificadora para añadir un producto.
      \pre prod_tiene + prod_necesita > 0.
      \post La ciudad pasa a tener el nuevo producto en el inventario.
      Se escribe el peso y volumen total.
  */
  void poner_prod(int id_producto, int prod_tiene, int prod_necesita, const Cjt_productos& cp);

  /** @brief Modificadora para un producto.
      \pre prod_tiene + prod_necesita > 0.
      \post Los datos del producto indicado pasan a ser los nuevos.
      Se escribe el peso y volumen total.
  */
  void modificar_prod(int id_producto, int prod_tiene, int prod_necesita, const Cjt_productos& cp);

  /** @brief Modificadora para eliminar un producto.
      \pre <em>cierto</em>
      \post Se elimina el producto del inventario.
      Se escribe el peso y volumen total.
  */
  void quitar_prod(int id_producto, const Cjt_productos& cp);

  /** @brief Operación de comerciar
      \pre El parámetro implícito y la ciudad c2 están correctamente inicializados y sus inventarios
      contienen productos con IDs válidos y consistentes respecto al conjunto de productos, que debe contener
      información válida sobre los productos, de sus pesos y volúmenes.
      \post Se han intercambiado los productos que le sobran a una
      ciudad y que necesite la otra. Los inventarios de ambas ciudades se han actualizado.
      Los atributos de peso y volumen total de ambas ciudades se han ajustado adecuadamente.
  */
  void comerciar(Ciudad& c2, const Cjt_productos& cp);

  // Consultoras

  /** @brief Consultora de producto poseídos.
      \pre El producto pertenece a la ciudad.
      \post Devuelve cuántas unidades de ese producto tiene la ciudad.
  */
  int consultar_tiene_ciudad(int id_producto) const;

  /** @brief Consultora de productos necesarios.
      \pre El producto pertenece a la ciudad.
      \post Devuelve cuántas unidades de ese producto necesita la ciudad.
  */
  int consultar_necesita_ciudad(int id_producto) const;

  /** @brief Consultora de productos sobrantes.
      \pre El producto pertenece a la ciudad.
      \post Devuelve cuántas unidades de ese producto tiene la ciudad menos las que necesita.
  */
  int consultar_necesitareal_ciudad(int id_producto) const;

 /** @brief Consultora de producto.
      \pre El producto pertenece a la ciudad.
      \post Devuelve cuántas unidades de ese producto tiene y necesita la ciudad.
  */
  void consultar_prod_ciudad(int id_producto) const;

  /** @brief Consultora de producto en inventario.
      \pre <em>cierto</em>
      \post Devuelve true si el producto está en el inventario, falso de lo contrario.
  */
  bool hay_prod_ciudad(int id_producto) const;

  // Escritura

  /** @brief Operación de escritura.
      \pre <em>cierto</em>
      \post Se ha escrito el inventario, peso y volumen total de la ciudad por el canal estándard
      de salida.
  */
  void escribir_ciudad() const;

  // Lectura

  /** @brief Operación de lectura.
      \pre En el canal estándar de entrada se encuentra un entero no negativo.
      Posteriormente, se leen tres enteros el número de veces indicado por el anterior entero, 
      todos estrictamente positivos excepto el segundo que puede ser cero.
      \post Se ha leído el inventario de la ciudad.
  */
  void leer_inventario(const Cjt_productos& cp);
};

#endif