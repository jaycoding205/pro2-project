/**
 * @file program.cc
 * @brief Programa principal.
 * 
 * Gestiona una cuenca con sus respectivas ciudades, barcos y productos. Permite la lectura de la 
 * estructura de la cuenca, la lectura y escritura de inventarios de las ciudades,
 * y la gestión de viajes y comercio entre las ciudades. Además, se encarga de 
 * coordinar las operaciones de redistribución de productos y la ejecución de viajes 
 * de barcos para la compra y venta de productos.
 */

/**
 * @mainpage Comercio Fluvial - Primavera 2024
 * 
 *
 *
 * 
 * @subsection introducción Introducción
 * 
 * En esta práctica se modela una cuenca fluvial con un río principal y varios afluentes. 
 * Hay ciudades ubicadas en las fuentes de los ríos y en los puntos de confluencia de los afluentes, 
 * incluida la desembocadura. 
 * 
 * El río y sus afluentes son arterias comerciales importantes entre las ciudades situadas a lo largo de ellos, 
 * ya que las ciudades comercian entre ellas a través del río. Además, existe un barco dedicado a realizar viajes
 * comerciales. El objetivo es que se hagan intercambio de productos, con su respectivo peso y volumen, entre
 * las diferentes ciudades que tienen necesidades cambiantes.
 * 
 * El programa principal para llevar a cabo el proyecto inicializa los componentes principales de la cuenca fluvial, lee los
 * datos iniciales y procesa los comandos de entrada para gestionar el comercio entre las ciudades. Los comandos permiten
 * leer y modificar inventarios, gestionar el barco, y realizar acciones comerciales entre las ciudades.
 * 
 * @subsection uso Comandos para simular el comercio
 * 
 * Se pueden utilizar diferentes comandos de acorde a las necesidades expuestas:
 * 
 * - `leer_rio` (`lr`): Lee la configuración del río.
 * - `leer_inventario` (`li`): Lee el inventario de una ciudad específica.
 * - `leer_inventarios` (`ls`): Lee los inventarios de todas las ciudades.
 * - `modificar_barco` (`mb`): Modifica la configuración del barco para un viaje comercial.
 * - `escribir_barco` (`eb`): Muestra la configuración actual del barco.
 * - `consultar_num` (`cn`): Consulta el número de productos.
 * - `agregar_productos` (`ap`): Agrega nuevos productos al sistema.
 * - `escribir_producto` (`ep`): Muestra la información de un producto específico.
 * - `escribir_ciudad` (`ec`): Muestra la información de una ciudad específica.
 * - `poner_prod` (`pp`): Agrega o actualiza un producto en el inventario de una ciudad.
 * - `modificar_prod` (`mp`): Modifica las cantidades de un producto en el inventario de una ciudad.
 * - `quitar_prod` (`qp`): Elimina un producto del inventario de una ciudad.
 * - `consultar_prod` (`cp`): Consulta las cantidades de un producto en una ciudad específica.
 * - `comerciar` (`co`): Realiza una acción de comercio entre dos ciudades.
 * - `redistribuir` (`re`): Redistribuye los productos entre las ciudades para optimizar los inventarios.
 * - `hacer_viaje` (`hv`): Realiza un viaje comercial con el barco.
 * 
 */


#include "Cjt_productos.hh"
#include "Cuenca.hh"
#include "Barco.hh"

int main() {
    Cuenca c;
    Cjt_productos cp;
    Barco b;

    c.lectura_inicial(cp, b);
    
   // COMANDOS
   
    string op;
    while (cin >> op and op != "fin") {
        if (op == "leer_rio" or op == "lr") {
            cout << '#' << op << endl;
            c.leer_rio();
            b.reiniciar_lista();
        }

        else if (op == "leer_inventario" or op == "li") {
            string id_ciudad;
            cin >> id_ciudad;
            cout << '#' << op << ' ' << id_ciudad << endl;
            c.leer_inventario(id_ciudad, cp);
        }

        else if (op == "leer_inventarios" or op == "ls") {
            cout << '#' << op << endl;
            c.leer_inventarios(cp);
        }

        else if (op == "modificar_barco" or op == "mb") {
            int id_producto_comprar, num_comprar, id_producto_vender, num_vender;
            cin >> id_producto_comprar >> num_comprar >> id_producto_vender >> num_vender;
            cout << '#' << op << endl;
            b.modificar_barco(id_producto_comprar, num_comprar, id_producto_vender, num_vender, cp);
        }
        
        else if (op == "escribir_barco" or op == "eb") {
            cout << '#' << op << endl;
            b.escribir_barco();
        }
        
        else if (op == "consultar_num" or op == "cn") {
            cout << '#' << op << endl;
            cout << cp.consultar_num() << endl;
        }
        
        else if (op == "agregar_productos" or op == "ap") {
            int num_productos;
            cin >> num_productos;
            cout << '#' << op << ' ' << num_productos << endl;
            cp.agregar_productos(num_productos);
        }
        
        else if (op == "escribir_producto" or op == "ep") {
            int id_producto;
            cin >> id_producto;
            cout << '#' << op << ' ' << id_producto << endl;
            cp.escribir_producto(id_producto);
        }
        
        else if (op == "escribir_ciudad" or op == "ec") {
            string id_ciudad;
            cin >> id_ciudad;   
            cout << '#' << op << ' ' << id_ciudad << endl;
            c.escribir_ciudad(id_ciudad);
        }
        
        else if (op == "poner_prod" or op == "pp") {
            string id_ciudad;
            int id_producto;
            int prod_tiene;
            int prod_necesita;
            cin >> id_ciudad >> id_producto >> prod_tiene >> prod_necesita;
            cout << '#' << op << ' ' << id_ciudad << ' ' << id_producto << endl;
            c.poner_prod(id_ciudad, id_producto, prod_tiene, prod_necesita, cp);
        }
        
        else if (op == "modificar_prod" or op == "mp") {
            string id_ciudad;
            int id_producto;
            int prod_tiene;
            int prod_necesita;
            cin >> id_ciudad >> id_producto >> prod_tiene >> prod_necesita;
            cout << '#' << op << ' ' << id_ciudad << ' ' << id_producto << endl;
            c.modificar_prod(id_ciudad, id_producto, prod_tiene, prod_necesita, cp);
        }
        
        else if (op == "quitar_prod" or op == "qp") {
            string id_ciudad;
            int id_producto;
            cin >> id_ciudad >> id_producto;
            cout << '#' << op << ' ' << id_ciudad << ' ' << id_producto << endl;
            c.quitar_prod(id_ciudad, id_producto, cp);
        }
        
        else if (op == "consultar_prod" or op == "cp") {
            string id_ciudad;
            int id_producto;
            cin >> id_ciudad >> id_producto;
            cout << '#' << op << ' ' << id_ciudad << ' ' << id_producto << endl;
            c.consultar_prod_ciudad(id_ciudad, id_producto, cp);
        }
        
        else if (op == "comerciar" or op == "co") {
            string id_ciudad1, id_ciudad2;
            cin >> id_ciudad1 >> id_ciudad2;
            cout << '#' << op << ' ' << id_ciudad1 << ' ' << id_ciudad2 << endl;
            c.comerciar(id_ciudad1, id_ciudad2, cp);
        }
        
        else if (op == "redistribuir" or op == "re") {
            cout << '#' << op << endl;
            c.redistribuir(cp);
        }
        
        else if (op == "hacer_viaje" or op == "hv") {
            cout << '#' << op << endl;
            c.hacer_viaje(b,cp);
        }

        else if (op == "//") {
            string comentario;
            getline(cin, comentario);
        }
    }
}