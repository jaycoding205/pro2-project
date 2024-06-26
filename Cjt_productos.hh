/** @file Cjt_productos.hh
    @brief Especificación de la clase Conjunto de Productos.
*/

#ifndef CJT_PRODUCTOS_HH
#define CJT_PRODUCTOS_HH

#include "Producto.hh"

#ifndef NO_DIAGRAM
#include <map>
#endif

/** @class Cjt_productos
    @brief Representa un conjunto ordenado de productos identificados por una ID.
    
    Gestiona un conjunto de productos, permitiendo operaciones de consulta,
    escritura y lectura. Los productos están identificados de manera única por un ID y se almacenan 
    en un mapa para un acceso rápido. Proporciona métodos para verificar la existencia de productos, 
    consultar sus atributos, y realizar la lectura y escritura de productos.
*/

class Cjt_productos
{

private:
  /** @brief Conjunto ordenado por ID de los productos. */
  map<int, Producto> _productos;
  /** @brief Número de productos que hay en el conjunto. */
  int _num_prod;

public:
  // Constructora 

  /** @brief Creadora por defecto. 
      Se ejecuta automáticamente al declarar Cjt_productos.
      \pre <em>cierto</em>
      \post El resultado es un conjunto sin ningún producto.
  */   
  Cjt_productos();
  
  // Consultoras

  /** @brief Consultora de existencia producto.
      \pre Existe la id del producto.
      \post Devuelve cierto si el producto existe, falso en caso contrario
  */
  bool hay_prod(int id_producto) const;

 /** @brief Consultora del número de productos.
      \pre <em>cierto</em>
      \post El resultado es el número de productos diferentes.
  */
  int consultar_num() const;

  /** @brief Consultora del peso de un producto.
      \pre Existe la id del producto.
      \post Devuelve el peso del producto.
  */
  int consultar_peso_producto(int id_producto) const;

  /** @brief Consultora del volumen de un producto.
      \pre Existe la id del producto.
      \post Devuelve el volumen del producto.
  */
  int consultar_volumen_producto(int id_producto) const;

  // Escritura

  /** @brief Operación de escritura.
      \pre <em>cierto</em>
      \post Se ha escrito el ID, peso y volumen del producto en el canal estándard
      de salida.
  */
  void escribir_producto(int id_producto) const;

  // Lectura

  /** @brief Operación de lectura.
      \pre En el canal estándar de entrada se encuentran dos enteros
      no negativos num_productos veces que representan el peso y volumen
      de un producto. Los productos no podían existir anteriormente.
      \post Se han leído los nuevos productos.
  */
  void agregar_productos(int num_productos);
};

#endif