/** @file Barco.hh
    @brief Especificación de la clase Barco.
*/

#ifndef _BARCO_HH_
#define _BARCO_HH_

#ifndef NO_DIAGRAM
#include <iostream>
#include <list>
#include "Cjt_productos.hh" // para verificar errores
#endif

using namespace std;

/** @class Barco
    @brief Representa un barco, con los productos que busca comprar y vender.
    
    Gestiona las operaciones de compra y venta de productos. Permite 
    modificar los productos que se desean comprar y vender, reiniciar la lista de 
    ciudades visitadas y agregar nuevas ciudades visitadas. Proporciona métodos para 
    consultar los detalles de los productos que se buscan comprar y vender, así como 
    el historial de ciudades visitadas.
*/

class Barco
{

private:
  /** @brief ID del elemento que se intenta comprar. */
  int _id_prod_comprar;
  /** @brief ID del elemento que se intenta vender. */
  int _id_prod_vender;
  /** @brief Número de productos a comprar. */
  int _num_comprar;
  /** @brief Número de productos a vender.. */
  int _num_vender;
  /** @brief Últimas ciudades recorridas ordenadas cronológicamente */
  list<string> _ult_ciudad;

public:
  // Constructoras

  /** @brief Creadora por defecto. 
      Se ejecuta automáticamente al declarar un barco.
      \pre <em>cierto</em>
      \post El resultado es un barco no inicializado.
  */   
  Barco();

  /** @brief Creadora con valores inicializados.
      \pre num_comprar > 0, num_vender > 0, ID de comprar y vender correctas.
      \post El barco contiene el ID del producto que comprar,
      vender, y el número de elementos de ambos.
  */
  Barco(int id_producto_comprar, int num_comprar, int id_producto_vender, int num_vender);
  
  // Modificadoras

  /** @brief Modificadora para reiniciar ciudades visitadas.
      \pre <em>cierto</em>
      \post Se reinicia la lista que contiene las últimas ciudades
      visitadas en orden cronológico.
  */
  void reiniciar_lista();

  /** @brief Modificadora para el barco.
      \pre num_comprar > 0, num_vender > 0.
      \post El barco contiene el ID del producto que comprar,
      vender, y el número de elementos de ambos.
  */
  void modificar_barco(int id_producto_comprar, int num_comprar, int id_producto_vender, int num_vender, const Cjt_productos& cp);

  /** @brief Modificadora para la última ciudad.
      \pre <em>cierto<em>
      \post Añade al barco la última ciudad visitada.
  */
  void agregar_ultima_ciudad(string ultima_ciudad);
  
  // Consultoras

  /** @brief Consultora de la id del producto a comprar.
      \pre Barco inicializado.
      \post Devuelve la id del producto que el barco busca comprar.
  */
  int consultar_id_prod_comprar() const;

  /** @brief Consultora de la id del producto a vender.
      \pre Barco inicializado.
      \post Devuelve la id del producto que el barco busca vender.
  */
  int consultar_id_prod_vender() const;

  /** @brief Consultora del número de productos a comprar.
      \pre Barco inicializado.
      \post Devuelve el número de productos que el barco busca comprar.
  */
  int consultar_num_comprar() const;

  /** @brief Consultora del número de productos a vender.
      \pre Barco inicializado.
      \post Devuelve el número de productos que el barco busca vender.
  */
  int consultar_num_vender() const;

  // Escritura

  /** @brief Operación de escritura del barco.
      \pre Barco inicializado.
      \post Se escribe por el canal estándard de salida la información de la ID de producto
      que comprar, vender, y el número de elementos de ambos. También se escriben
      las últimas ciudades de los diferentes viajes en orden cronológico.
  */
  void escribir_barco() const;
};

#endif
