#ifndef _LISTADOBLE_
#define _LISTADOBLE_ 0

#include <iostream>
#include <list>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>


#include "nodo_doble.h"

#define POSITION_BEGINNING 0
#define POSITION_END 1000

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
        int result = 0;
        // Creamos un puntero hacia un nuevo nodo 
        //luego asignamos la cantidad de memoria que seva a reservar para la estructura nododoble 
        //Por ultimo se convierte el puntero void* devuelto por "malloc" a un puntero del tipo correcto para su estructura */
        nododoble* newNodo = (nododoble*)malloc(sizeof(struct nododoble));
        // Se le asigna la estructura a contener en data del nuevo nodo doble.
        newNodo->data = pValue;

        // Manejo de inserciones si la lista esa vacia
        if (tamanno==0) {
  
            // Como solo hay un nodo apunta el inicio y el fin a ese nodo
            start = newNodo; 
            end = newNodo;

            // newNodo sera el siguiente nodo despues del start
            newNodo->next = start; 
            // newNodo sera el nodo anterior al end
            newNodo->previous = end; 

        } else { // Manejo de inserciones al inicio con mas elementos presentes
            
            // Significa que se quiere introducir un nodo al inicio de la lista
            if (pPosition==0) { 
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
                
            } else { // Manejo de inserciones en una posicion especifica
                // currentPosition es como un contador mientras va recorriendo
                int currentPosition = 0;
                // Este apunta al primer nodo en la lista
                nododoble* cursor = start; 

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

                // Se verifica si el cursor llego al final, significadno que el nuevo nodo fue introducido al final de la lista
                if (cursor==end) {
                    // El puntero del final y el previo al inicio ahora apuntan al nuevo nodo
                    end = newNodo;
                    start->previous = newNodo;
                }
            }
        }
        tamanno++;
        return result;
    }

    void buscar(string pKey) {
        // Creamos un vector para almacenar cada palabra
        std::vector<std::string> keywords; 
        // Se declara como stringstream para luego operar sobre ella
        std::istringstream iss(pKey);
        string keyword;
        if (tamanno == 0) { // Lista vacia, nada que eliminar
            return;
        } else {
            int currentPosition = 1;
            nododoble* cursor = start;

            // Separamos las palabras que recibimos en cada coma
            while (std::getline(iss, keyword, ',')) {
                // Convertimos a minuscula (case-sensitive)
                std::transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);
                keywords.push_back(keyword);
            }
            // Loopeamos la nueva lista
            while (cursor != end) {
                // Extraer cada titular
                string titularString = cursor->data->titular;
                // Transformamos el titular a lower
                std::transform(titularString.begin(), titularString.end(), titularString.begin(), ::tolower);

                // Revisa si contiene almenos una palabra que buscamos
                bool keywordFound = false;
                for (const string& kw : keywords) {
                    if (titularString.find(kw) != std::string::npos) {
                        keywordFound = true;
                        break;
                    }
                }
                // Si lo encuentra lo imprime
                if (keywordFound) {
                    printf("%d: %s\n", currentPosition, cursor->data->titular.c_str());
                    currentPosition++;
                }
                cursor = cursor->next;
            }
        }
    }
    
    void getTop5Key(string pKey) {
        std::vector<std::string> keywords; 
        std::istringstream iss(pKey);
        std::string keyword;
        int i = 0;
        if (tamanno == 0) {
            // Lista vacia, nada que eliminar
            return;
        } else {
            int currentPosition = 1;
            nododoble* cursor = start;

            // convertimos a minuscula
            while (std::getline(iss, keyword, ',')) {
                std::transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);
                keywords.push_back(keyword);
            }
            // Loopeamos la nueva lista
            while (cursor != end) {
                string titularString = cursor->data->titular;
                std::transform(titularString.begin(), titularString.end(), titularString.begin(), ::tolower);

                bool keywordFound = false;
                for (const std::string& kw : keywords) {
                    if (titularString.find(kw) != std::string::npos) {
                        keywordFound = true;
                        break;
                    }
                }
                // Encuentra la noticia e imprime las primeras 5 que incluyan alguno de las palabras dadas
                if (keywordFound && i < 5) {
                    printf("%d: %s\n", currentPosition, cursor->data->titular.c_str());
                    currentPosition++;
                    i ++;
                }
                cursor = cursor->next;
            }
        }
    }
    
    void mostrar() {
        // Si la lista NO esta vacia
        if (tamanno != 0) {
            int currentPosition = 0;
            nododoble* cursor = start;

            // Recorre toda la lista e imprime cada noticia
            while (currentPosition < tamanno) {
                std::cout << currentPosition << ": " << cursor->data->numero << ", " << cursor->data->titular << std::endl << "\n";
                cursor = cursor->next;
                currentPosition++;
            }
        }
    }

    void getTop5() {
        // Si la lista NO esta vacia
        if (tamanno != 0) {
            int currentPosition = 0;
            nododoble* cursor = start;

            // Imprime solo las primeras 5 noticias en general
            while (currentPosition < 5) {
                std::cout << currentPosition << ": " << cursor->data->numero << ", " << cursor->data->titular << std::endl << "\n";
                cursor = cursor->next;
                currentPosition++;
            }
        }
    }

    void buscar_eliminar(string pKey) {
        // Misma logica de buscar pero cuando lo encuentra lo elimina
        std::vector<std::string> keywords; 
        std::istringstream iss(pKey);
        std::string keyword;
        int i = 1;
        
        while (std::getline(iss, keyword, ',')) {
            std::transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);
            keywords.push_back(keyword);
        }

        int currentPosition = 0;
        nododoble* cursor = start;
        nododoble* nextCursor = nullptr;  // Store the next cursor to avoid issues when deleting a node

        while (cursor != end) {
            string titularString = cursor->data->titular;
            std::transform(titularString.begin(), titularString.end(), titularString.begin(), ::tolower);

            bool keywordFound = false;

            for (const std::string& kw : keywords) {
                if (titularString.find(kw) != std::string::npos) {
                    keywordFound = true;
                    break;
                }
            }

            if (keywordFound) {
                //printf("eliminando %d: %s\n", cursor->data->titular.c_str());
                nextCursor = cursor->next;  // Guarda el siguiente cursor antes de borrar el actual
                eliminar(currentPosition);
                cursor = nextCursor;  // Nos movemos al siguiente nodo despues de eliminar
                i++;
            } else {
                currentPosition++;
                cursor = cursor->next;
            }
        }
        cout << "Se han eliminado " << i << " noticias" << std::endl;
    }
    
    struct noticia* eliminar(int pPosition) {
        struct noticia* result = nullptr;
        if (tamanno == 0) {
            // Lista vacía, nada que eliminar
            return result; //! ERROR!
        } else if (tamanno == 1) {
            // Solo hay un nodo, por lo que se tiene que actualizar start y end
            result = start->data;
            start = nullptr;
            end = nullptr;
            tamanno = 0;
        } else {
            if (pPosition == 0) { // Se quiere eliminar el nodo del inicio
                result = start->data;
                start = start->next; // Start apunta al siguiente nodo
                start->previous->next = nullptr; // El nuevo primer nodo apunte hacia atrás a nada
                start->previous = nullptr;
                tamanno--;
            } else {
                int currentPosition = 0;
                nododoble* cursor = start;
                while (cursor != end && currentPosition < pPosition) {
                    cursor = cursor->next;
                    currentPosition++;
                }
                if (cursor == end) { // Se llegó al final o se dio una posición más grande
                    return result; //! ERROR!
                } else {
                    result = cursor->data;
                    cursor->previous->next = cursor->next; // Hacer que el nodo anterior apunte al siguiente nodo
                    cursor->next->previous = cursor->previous; // Hacer que el nodo siguiente apunte al nodo anterior
                    cursor->next = nullptr;
                    cursor->previous = nullptr;
                    tamanno--;
                }
            }
        }
        return result;
    }

    void reacomodar(int sourcePosition, int destinationPosition) {
        // Comprobar si la lista está vacía o si las posiciones son inválidas
        if (tamanno == 0 || sourcePosition < 0 || sourcePosition >= tamanno || destinationPosition < 0 || destinationPosition >= tamanno) {
            // Manejar el error o retornar temprano
            cout << "Posiciones inválidas o lista vacía." << endl;
            return;
        }

        // Si las posiciones de origen y destino son las mismas, no es necesario reorganizar
        if (sourcePosition == destinationPosition) {
            cout << "Las posiciones de origen y destino son iguales. No se necesita reorganización." << endl;
            return;
        }

        // Encontrar los nodos de origen y destino
        nododoble* sourceNode = nullptr;
        nododoble* destinationNode = nullptr;

        if (sourcePosition < destinationPosition) {
            // Recorrer la lista desde el principio para encontrar los nodos de origen y destino
            int currentPosition = 0;
            nododoble* cursor = start;

            while (cursor != nullptr) { // Mientras no llegue al final
                if (currentPosition == sourcePosition) {
                    sourceNode = cursor;
                }
                if (currentPosition == destinationPosition) {
                    destinationNode = cursor;
                    break;
                }
                cursor = cursor->next;
                currentPosition++;
            }
        } else {
            // Recorrer la lista desde el final para encontrar los nodos de origen y destino
            int currentPosition = tamanno - 1;
            nododoble* cursor = end; // Empezamos desde el final

            while (cursor != nullptr) {
                if (currentPosition == sourcePosition) {
                    sourceNode = cursor;
                }
                if (currentPosition == destinationPosition) {
                    destinationNode = cursor;
                    break;
                }
                cursor = cursor->previous; // Vamos retrocediendo
                currentPosition--;
            }
        }

        // Comprobar si se encontraron los nodos de origen y destino
        if (sourceNode == nullptr || destinationNode == nullptr) {
            cout << "Nodo de origen o destino no encontrado." << endl;
            return;
        }

        // Desconectar el nodo de origen de su posición actual
        if (sourceNode->previous != nullptr) {
            sourceNode->previous->next = sourceNode->next;
        } else {
            // El nodo de origen es el primer nodo
            start = sourceNode->next;
        }
        if (sourceNode->next != nullptr) {
            sourceNode->next->previous = sourceNode->previous;
        } else {
            // El nodo de origen es el último nodo
            end = sourceNode->previous;
        }

        // Insertar el nodo de origen en la posición de destino
        if (destinationPosition == 0) {
            // Insertar al principio
            sourceNode->next = start;
            start->previous = sourceNode;
            sourceNode->previous = nullptr;
            start = sourceNode;
        } else {
            // Insertar en la posición de destino
            sourceNode->next = destinationNode;
            sourceNode->previous = destinationNode->previous;
            destinationNode->previous->next = sourceNode;
            destinationNode->previous = sourceNode;
        }
    }
};
#endif