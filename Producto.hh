/** @file Producto.hh
    @brief Especificación de la clase Producto.
*/

#ifndef _PRODUCTO_HH_
#define _PRODUCTO_HH_

#ifndef NO_DIAGRAM
#include <iostream>
#endif

using namespace std;

/** @class Producto
    @brief Representa un producto con peso y volumen.

    Permite gestionar información sobre productos que se
    comercian entre las ciudades. Cada producto tiene dos atributos principales:
    peso y volumen. Se incluyen operaciones para consultar estos atributos,
    así como para leer y escribir la información de los productos desde y hacia
    el canal estándar de entrada/salida. Además, se proporciona una operación
    constructora por defecto para inicializar un producto.
*/

class Producto
{

private:
  /** @brief  Variable que indica el peso del producto. */
  int _peso;
  /** @brief  Variable que indica el volumen del producto. */
  int _volumen;

public:
  // Constructora

  /** @brief Creadora por defecto. 
      Se ejecuta automáticamente al declarar un producto.
      \pre <em>cierto</em>
      \post El resultado es un producto no inicializado.
  */   
  Producto();

  // Consultoras

  /** @brief Consultora del peso.
      \pre Producto inicializado.
      \post El resultado es el peso del parámetro implícito.
  */
  int consultar_peso() const;
 
  /** @brief Consultora del volumen.
      \pre Producto inicializado.
      \post El resultado es el volumen del parámetro implícito.
  */
  int consultar_volumen() const;

  // Escritura

  /** @brief Operación de escritura.
      \pre Producto inicializado.
      \post Se ha escrito el ID, peso y volumen del parámetro implícito en el canal
      estándar de salida.
  */
  void escribir_producto() const;

  // Lectura

  /** @brief Operación de lectura.
      \pre En el canal estándar de entrada se encuentran dos enteros no negativos 
      que representan el peso y el volumen que se van a leer. 
      \post Se han leído el peso y volumen del parámetro implícito.
  */
  void leer_producto();
};

#endif