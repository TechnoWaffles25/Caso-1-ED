#include <iostream>
#include <list>
#include <string>

#include "nodo_doble.h"
#include "lista_doble.cpp"
#include "news.cpp"

using namespace std;

int main() {
    // Creamos una instancia del NewsAPI
    Newsapi newsApi;

    // Llamamos la funcion para popular el vector
    vector<struct noticia *> allrecords = newsApi.getRecords();

    // Obtenemos el tamaño del vecctor
    int vector_size = allrecords.size();
    cout << "Vector size: " << vector_size << std::endl;
    
    int i = 0;
    while (i < vector_size){
        cout << allrecords.at(i)->titular<< std::endl;
        i++;
    }

    // Crear una instancia de la lista doblemente enlazada
    listadoble lista;

    // Insertar noticias en la lista
    int contador = 0;
    cout << "-------------------" << std::endl;

    /*while (contador < vector_size){
        lista.insertar(allrecords.at(contador), contador++); // Insertar

        std::cout << "- insert exitoso "<< std::endl;
        contador++;   
    }*/
    
    lista.insertar(allrecords.at(0),0);
    cout << "-------------------" << std::endl;
    lista.buscar(0); // Mostrará el contenido del primer nodo
    lista.insertar(allrecords.at(1),1);
    lista.buscar(1);
    lista.insertar(allrecords.at(2),2);

    cout << "-------------------" << std::endl;
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