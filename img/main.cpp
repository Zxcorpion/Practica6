
//
//  Created by Antonio Rueda y Lidia Ortega 
//

#include <fstream>
#include <iostream>
#include <vector>
#include "img.h"

#include <math.h>

using namespace std;

int main (int argc, const char * argv[])
{
    RGBColor blanco (255,255,255);
    
    Img img(700, 1300, blanco); // rectángulo de 700 filas x 1300 columnas
	
    int nfilas = img.numFilas();
    int ncol = img.numColumnas();
    
        
    cout << "Imagen creada con " << nfilas << "filas y " << ncol << " columnas." <<endl;

    int r = 0; // azul
    int g = 0;
    int b = 255;
    
    // sabemos el tamaño de la caja envolvente de los datos, pero volver a calcular 

    double minlat = 35.86688;
    double maxlat = 43.272616;
    double minlon = -9.99443;
    double maxlon = 3.98926;

      
    // Calculamos el número de pixeles asociados a un grado 

    cout << "lat: xmin = " << minlon <<  ", " << "xmax = " << maxlon << endl;
    cout << "lon: ymin = " << minlat <<  ", " << "ymax = " << maxlat << endl;

    double rangoy = maxlat - minlat;
    double rangox = maxlon - minlon;

    cout << "rango x = " << rangox << endl;
    cout << "rango y = " << rangoy << endl;

    cout << "nfilas = " << nfilas << endl;
    cout << "ncol = " << ncol << endl;

    double pixelPorGradoY = (double) (nfilas - 1) / rangoy;
    double pixelPorGradoX = (double) (ncol - 1) / rangox;


    cout << "Pixel por Grado X = " << pixelPorGradoX << endl;
    cout << "Pixel por Grado Y = " << pixelPorGradoY << endl;

 
    // elegimos las coordenada de un recuadro cualquiera

    double lat1 = 40;
    double lon1 = -8;

    double lat2 = 42.0;
    double lon2 = -5.0;

    //Nota: invertir coordenada Y (latitudes)
    img.pintarRecuadro( ((lon1 - minlon) * pixelPorGradoX), nfilas -1 - (lat1 - minlat) * pixelPorGradoY, 
                        ((lon2 - minlon) * pixelPorGradoX), nfilas -1 - (lat2 - minlat) * pixelPorGradoY, 255, 0, 0);


    // ejemplo de punto que debe estar por el centro, lo pintamos acto seguido

    double vlat = 39.569748;
    double vlon = -3.002585;

    int posY = nfilas -1 - (vlat - minlat) * pixelPorGradoY; //Invertir coordenada Y
    int posX = ((vlon -minlon) * pixelPorGradoX);
    img.pintarPixelGrande(posX,posY,r,g,b);
    //img.pintarPixel(posX,posY,r,g,b);


    try {
    img.guardar("../mapaResultado.ppm");
    }
    catch(ErrorEscrituraFichero &e) {
    	cout << "Error al escribir fichero" << endl;
    	return 1;
    }
    
    cout << "Operación realizada con exito, ahora visualizarlo con cualquier visor de imágenes" << endl;
   
    return EXIT_SUCCESS;
}

