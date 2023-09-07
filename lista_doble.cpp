#ifndef _LISTADOBLE_
#define _LISTADOBLE_ 0

#include <iostream>
#include <list>
#include <string>


#include "nodo_doble.h"

#define POSITION_BEGINNING 0
#define POSITION_END 100

using namespace std;

// Creamos la estructura
struct listadoble {
    int tamanno = 0; // comenzamos en 0 el tamaño
    nododoble* start = nullptr;
    nododoble* end = nullptr;
    
    // Dentro de la estructura tenemos sus funciones
    
    int getSize(){
            return tamanno;
    }

    // se declara noticia* como puntero para permitir a la funcion modificar 
    // directamente el objeto de tipo "noticia" al q apunta pValue.

    int insertar(struct noticia* pValue, int pPosition){
        std::cout << "tamanno0: " << tamanno << std::endl;
        int result = 0;
        // Creamos un puntero hacia un nuevo nodo 
        //luego asignamos la cantidad de memoria que seva a reservar para la estructura nododoble 
        //Por ultimo se convierte el puntero void* devuelto por "malloc" a un puntero del tipo correcto para su estructura */
        nododoble* newNodo = (nododoble*)malloc(sizeof(struct nododoble));
        // Se le asigna la estructura a contener en data del nuevo nodo doble.
        newNodo->data = *pValue;

        std::cout << "tamanno1: " << tamanno << std::endl;


        // Manejo de inserciones si la lista esa vacia
        if (tamanno==0) {
            std::cout << "tamanno2: " << tamanno << std::endl;
            // Como solo hay un nodo apunta el inicio y el fin a ese nodo
            start = newNodo; 
            end = newNodo;
            std::cout << "tamanno3: " << tamanno << std::endl;
            // newNodo sera el siguiente nodo despues del start
            newNodo->next = start; 
            // newNodo sera el nodo anterior al end
            newNodo->previous = end; 
            
            std::cout << "tamanno4: " << tamanno << std::endl;
            

        } else { // Manejo de inserciones al inicio con mas elementos presentes
            
            // Significa que se quiere introducir un nodo al inicio de la lista
            if (pPosition==0) { 
                std::cout << "tamanno5: " << tamanno << std::endl;
                // newNodo se vuelve el primer nodo de la lista
                newNodo->next =  start; 
                // newNodo se vuelve el nodo anterior al ultimo
                newNodo->previous = end; 
                // Ahora start tiene un enlace hacia atras al nuevo primer nodo
                start->previous = newNodo; 
                // Ahora end tiene un enlace hacia adelante al nuevo primer nodo
                end->next = newNodo; 
                // Ahora newNodo es el nuevo primer nodo de la lista
                start = newNodo; 

                std::cout << "tamanno6: " << tamanno << std::endl;
                
            } else { // Manejo de inserciones en una posicion especifica
                std::cout << "tamanno7: " << tamanno << std::endl;
                // currentPosition es como un contador mientras va recorriendo
                int currentPosition = 0;
                // Este apunta al primer nodo en la lista
                nododoble* cursor = start; 

                std::cout << "tamanno8: " << tamanno << std::endl;


            // Mientras el cursos no llegue al final y la posicion actual sea diferente a la deseada
                // Sigue avanzando
                while (cursor!=end && currentPosition<=pPosition) {
                    cursor = cursor->next;
                    currentPosition++;
                }
                
                // Al llegar a la posicion deseada
                // El puntero del nuevo nodo ahora apunta al nodo que estaba originalmente en esa posicion
                newNodo->next = cursor->next;
                // El puntero previo del nuevo nodo ahora apunta al nodo justo antes de la nueva posicion
                newNodo->previous = cursor;
                // Ahora el cursos del nodo original apunta al nuevo nodo
                cursor->next = newNodo;

                std::cout << "tamanno: " << tamanno << std::endl;
               

                // Se verifica si el cursor llego al final, significadno que el nuevo nodo fue introducido al final de la lista
                if (cursor==end) {
                    // El puntero del final y el previo al inicio ahora apuntan al nuevo nodo
                    end = newNodo;
                    start->previous = newNodo;
                }
                std::cout << "tamanno: " << tamanno << std::endl;
                

            }
        }
        tamanno++;
        return result;
    }

    struct noticia* eliminar(int pPosition){
        struct noticia* result = nullptr;

        if (tamanno==0){
            // Lista vacia, nada que eliminar
            return result; //! ERROR!
        } else if (tamanno==1){
            // Solo hay un nodo, por lo que se tiene que actualizar start y end
            result = &start->data;
            start = nullptr;
            end = nullptr;
            tamanno = 0;
        } else {
            if (pPosition == 0){ // Se quiere eliminar el nodo del inicio
                result = &start->data;
                start = start->next; // Start apunta al siguiente nodo
                start->previous->next = nullptr;// El nuevo primer nodo apunte hacia atras a nada
                start->previous = nullptr; 
                tamanno--; 
            } else {
                int currentPosition = 0;
                nododoble* cursor = start;
                while (cursor != end && currentPosition < pPosition){
                    cursor = cursor->next;
                    currentPosition++;
                }
                if (cursor==end){ // Se llego al final o se dio una posicion mas grande
                    return result; //! ERROR!
                } else {
                    result = &cursor->data;
                    cursor->previous->next = cursor->next; // Hacer que el nodo anterior apunte al siguiente nodo
                    cursor->next->previous = cursor->previous; // Hacer que el nodo siguiente apunte al nodo anterior
                    cursor->next = nullptr;
                    cursor->previous = nullptr;
                    tamanno--;
                }
            }

        }
        return result;
    };

    struct noticia* buscar(int pPosition){
        struct noticia* result = nullptr;

        if (tamanno==0){
            // Lista vacia, nada que eliminar
            return result; //! ERROR!

        } else if (pPosition < 0 || pPosition > tamanno) {
            // Out of range
            return result; //! ERROR!

        } else {
            int currentPosition = 0;
            nododoble* cursor = start;
            while (cursor != end && currentPosition < pPosition){
                cursor = cursor->next;
                currentPosition++;
            }
            std::cout <<"Nodo extraido BUSCAR: " << pPosition << ": " << cursor->data.numero << ", " << cursor->data.titular << std::endl;
        }  
        return result;
    };
    
    void mostrar() {
        if (tamanno != 0) {
            int currentPosition = 0;
            nododoble* cursor = start;

            while (cursor != end && currentPosition < POSITION_END) {
                std::cout << "Nodo extraído MOSTRAR: " << currentPosition << ": " << cursor->data.numero << ", " << cursor->data.titular << std::endl << "\n";
                cursor = cursor->next;
                currentPosition++;
            }
        }
    }

    /* void moverNoticia(struct noticia* pValue, int pEspacios){
        // Restricciones
        if (tamanno==0 || pValue == nullptr ||pEspacios == 0){
            return;

        } 
        // Esta seccion busca la posicion actual del nodo que queremos mover
        int currentPosition = 0;
        nododoble* nodoActual = start;

        while (nodoActual != nullptr ){
            if (&nodoActual->data == pValue){
                break;
            }
            nodoActual = nodoActual->next;
            currentPosition++;
        }

        // Verifica si encontro el nodo actual
        if (nodoActual  == nullptr){
            return; // No se encontro
        }

        // Calculamos la nueva posicion
        int posMover = currentPosition + pEspacios;

        // Restricciones para la nuvea posicion a mover
        // Si la nueva posicion es menor que cero
        if (posMover < 0){
            posMover = 0; // Se coloca al inicio

        // si la nueva posicion es mayor que el tamanno
        } else if (posMover >= tamanno){
            posMover = tamanno--; // Se coloca al final
        } 
        
        // Eliminamos el nodo actual de su posicion
        if (nodoActual->previous != nullptr) {
        nodoActual->previous->next = nodoActual->next;
        }
        if (nodoActual->next != nullptr) {
            nodoActual->next->previous = nodoActual->previous;
        }
        
        // Inserta el nodo en la nueva posición.
    if (posMover == 0) {
        // Coloca el nodo al principio de la lista.
        nodoActual->previous = nullptr;
        nodoActual->next = start;
        start->previous = nodoActual;
        start = nodoActual;
    } else {
        nododoble* nodoDespues = start;
        for (int i = 0; i < posMover - 1 && nodoDespues != nullptr; i++) {
            nodoDespues = nodoDespues->next;
        }

        nodoActual->previous = nodoDespues;
        nodoActual->next = nodoDespues->next;

        if (nodoDespues->next != nullptr) {
            nodoDespues->next->previous = nodoActual;
        }

        nodoDespues->next = nodoActual;
    }

    // Actualiza la posición de la noticia que ocupaba la nueva posición.
    if (posMover < currentPosition) {
        // La noticia se movió hacia arriba en la lista.
        nododoble* nodoSiguiente = nodoActual->next;
        nodoActual->next = nodoSiguiente->next;
        nodoActual->previous = nodoSiguiente;

        if (nodoSiguiente->next != nullptr) {
            nodoSiguiente->next->previous = nodoActual;
        }
        nodoSiguiente->next = nodoActual;

        if (nodoActual->previous != nullptr) {
            nodoActual->previous->next = nodoSiguiente;
        }

    } else {
        // La noticia se movió hacia abajo en la lista.
        nododoble* nodoAnterior = nodoActual->previous;
        nodoActual->previous = nodoAnterior->previous;
        nodoActual->next = nodoAnterior;
        if (nodoAnterior->previous != nullptr) {
            nodoAnterior->previous->next = nodoActual;
        }
        nodoAnterior->previous = nodoActual;
        if (nodoActual->next != nullptr) {
            nodoActual->next->previous = nodoAnterior;
        }
    }
}*/
};
/*int main() {
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
    std::cout << "Moviendo la noticia 4 hacia arriba en la lista." << std::endl;
    //lista.moverNoticia(&noticia4, -1);
    lista.mostrar();

    // Mover una noticia hacia abajo en la lista
    std::cout << "Moviendo la noticia 3 hacia abajo en la lista." << std::endl;
    //lista.moverNoticia(&noticia3, 1);
    lista.mostrar();

    // Eliminar un nodo en una posición específica
    lista.eliminar(1); // Eliminará el segundo nodo

    // Mostrar el tamaño de la lista después de la eliminación
    std::cout << "Tamaño de la lista después de eliminar: " << lista.getSize() << std::endl;

    // Mostrar el contenido de un nodo en una posición específica
    lista.buscar(1); // Mostrará el contenido del segundo nuevo nodo

    return 0;
}*/
#endif