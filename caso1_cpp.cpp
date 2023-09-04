/* COSAS DE TAMAÑO DINÁMICO

Los punteros recorren la memoria un segmento dado y usan la misma 
tecnica de la base y el desplazamiento. Es vital saber el tamanno de lo que esta apuntando
el puntero

SE DEBE SABER:
    - A lo que apunta
    - el valor del puntero -> direccion de memoria

PARA SACAR LA DIRECCION DE MEMORIA SE PUEDE USAR & O USAR UNA VARIABLE PUNTERO CON "*"
    - int a = 25
    - int *value; int* value;
    - value = &a
    - cout << value >> = da la direccion de memoria
    - cout << *value >> = da lo que contiene value, en este caso 25

OPERACIONES CON PUNTEROS
    - si hacemos value++ cambia la posicion de memoria, aumenta la cantidad de bits 
    que ocupe ese tipo de datos del apuntador, en el caso de int = 4

PUNTERO A CUALQUIER COSA
    - void* pointer = estos pointers se mueven de uno en uno

TRANSFORMAR VOID A OTRO TIPO
    - void* pointer = &algo[0]          -> hacemos el pointer
    - char *algo = (char*)pointer       -> transformar
    - char otro = *algo                 -> sacar a lo que apunta el pointer transformado
*/
#include <iostream>
#include <list>
#include <string>

#include "nodo_doble.h"
#include "lista_doble.cpp"

using namespace std;

int main() {
    // Crear una instancia de la lista doblemente enlazada
    listadoble lista;

    // Insertar noticias en la lista
    noticia noticia1 = {1, "Noticia 1"};
    noticia noticia2 = {2, "Noticia 2"};
    noticia noticia3 = {3, "Noticia 3"};
    noticia noticia4 = {4, "Noticia 4"};

    lista.insertar(&noticia1, POSITION_BEGINNING);
    lista.insertar(&noticia2, 1);
    lista.insertar(&noticia3, 2);
    lista.insertar(&noticia4, 3);

    lista.mostrar(); // Mostrará todo el contenido

    // Mostrar el tamaño de la lista
    std::cout << "Tamaño de la lista: " << lista.getSize() << std::endl;

    // Mostrar el contenido de un nodo en una posición específica
    lista.buscar(1); // Mostrará el contenido del segundo nodo

    // Mover una noticia hacia arriba en la lista
    //std::cout << "Moviendo la noticia 4 hacia arriba en la lista." << std::endl;
    //lista.moverNoticia(&noticia4, -1);
    //lista.mostrar();

    // Mover una noticia hacia abajo en la lista
    //std::cout << "Moviendo la noticia 3 hacia abajo en la lista." << std::endl;
    //lista.moverNoticia(&noticia3, 1);
    //lista.mostrar();

    // Eliminar un nodo en una posición específica
    lista.eliminar(1); // Eliminará el segundo nodo

    // Mostrar el tamaño de la lista después de la eliminación
    std::cout << "Tamaño de la lista después de eliminar: " << lista.getSize() << std::endl;

    // Mostrar el contenido de un nodo en una posición específica
    lista.buscar(1); // Mostrará el contenido del segundo nuevo nodo
}