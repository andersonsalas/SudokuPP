/*

Desarrollado por Anderson Salas (contacto@andersonsalas.com.ve)

-----

ENUNCIADO:

"Realice un programa que cargue automáticamente un sudoku. Los 9 valores iniciales deben ser
cargados aleatoriamente con el comando rand() y no pueden repetirse en toda la matriz 9x9. Una
vez generado el sudoku bajo las reglas del juego, permitirle al usuario escoger si quiere llenarlo
manualmente o que el programa genere una solución automática al sudoku generado. Tienen (que)
tener en cuenta las distintas restricciones que el juego posee, por lo que debe investigar bien las
características del juego.

Nota: Deben usar clase y todos los conocimientos adquiridos hasta el momento. El sudoku está
conformado por una matriz grande 9x9 y internamente subdividida en 9 matrices pequeñas 3x3"

*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

using namespace std;

class Sudoku
{
      public:
            int generarTablero(int sudokuMain[9][9], int numerosRellenar);
            int mostrarTablero(int sudokuMain[9][9]);
            int jugar(int sudokuMain[9][9]);
            int casillasVacias(int sudokuMain[9][9]);
            int agregarNumero(int sudokuMain[9][9], int posX, int posY, int numero);
            int generarSolucion(int fila, int columna, int sudokuMain[9][9]);
            int auxiliarGenerarSolucion(int fila, int columna, int n, int sudokuMain[9][9]);
            int sudokuGanar( int sudokuMain[9][9] );
            
};

int main()
{
    int sudokuMain[9][9]; // Creamos el arreglo
    
    Sudoku sudokuMainJuego;                         // Instanciamos un objeto de la clase Sudoku
    sudokuMainJuego.generarTablero(sudokuMain,9);   // Generamos el tablero
    sudokuMainJuego.jugar(sudokuMain);              // Iniciamos el juego
    
    system("pause");
    return 0;
}

int Sudoku::auxiliarGenerarSolucion(int fila, int columna, int n, int sudokuMain[9][9])
{
 
      int r, c, br, bc;
      
      if (sudokuMain[fila][columna] == n)
      {
          return 1;
      }
      if (sudokuMain[fila][columna] != 0)
      {
         return 0;
      }
      for (c = 0; c < 9; c++)
      {
        if (sudokuMain[fila][c] == n)
        {
           return 0;
        }
      }
      for (r = 0; r < 9; r++)
      {
        if (sudokuMain[r][columna] == n)
        {
           return 0;
        }
      }
      
      br = fila / 3;
      bc = columna / 3;
      
      for (r = br * 3; r < (br + 1) * 3; r++)
      {
        for (c = bc * 3; c < (bc + 1) * 3; c++)
        {
          if (sudokuMain[r][c] == n)
          {
             return 0;
          }
        }
      }
      
      return 1;
}

int Sudoku::generarSolucion(int fila, int columna, int sudokuMain[9][9])
{
 
    int n, t; 
    if(fila == 9)
    {      
        Sudoku::sudokuGanar(sudokuMain);
    }
    else
    {
      
       for (n = 1; n <= 9; n++)
       {
          if (Sudoku::auxiliarGenerarSolucion(fila, columna, n, sudokuMain))
          {
              t = sudokuMain[fila][columna];
              sudokuMain[fila][columna] = n;
              if (columna == 8)
              {
                 Sudoku::generarSolucion(fila + 1, 0, sudokuMain);
              }
              else
              {
                 Sudoku::generarSolucion(fila, columna + 1,sudokuMain);
                 sudokuMain[fila][columna] = t;
              }
          }
       }   
    }

   return 0;
}

int Sudoku::generarTablero(int sudokuMain[9][9], int numerosRellenar)
{
    // Rellenamos las 81 posiciones con ceros
    // (En el proceso interno del programa las posiciones con el valor 0 se
    // asumiran como casillas vacias. En otras palabras, aqui lo que estamos
    // haciendo es generar un tablero vacio
    
    for(int rb = 0; rb <= 8; rb++)
    {
        for(int k = 0; k <= 8; k++)
        {
            sudokuMain[rb][k] = 0;
        }
    }
    
    // Lo primero que necesitamos para generar el tablero es definir todas las 
    // variables necesarias para ello, comenzado por la "semilla" que usaremos
    // para generar los numeros aleatorios. Esto se hace con la funcion srand():
            
    srand (time(NULL)); 
    
    // Definimos una variable del tipo INT llamada "numeroAleatorio"
    // otra llamada "rellenar", y un booleano llamado "validoAgregar"
     
    int numeroAleatorio, rellenar, numerosUsados[9] = {0,0,0,0,0,0,0,0,0}, cuentaAgregados = 0;
    bool validoAgregar, numeroUsado;

    // El booleano "numeroUsado" y el arreglo "numerosUsados" nos serviran
    // para una serie de comprobaciones mas adelante

    // Empezamos a rellenar el tablero:
    for( int i = 0; i <= 8; i++)
    {
         
         for (int y = 0; y <= 8; y++)
         {
             // Lo que sucede es lo siguente: a medida que el ciclo va recorriendo
             // las 81 posiciones del arreglo, se van generando automaticamente
             // en cada iteracion dos numeros aleatorios, el primero: "rellenar",
             // y el segundo "numeroAleatorio". Como la idea es generar numeros
             // aleatoriamente, pero a su vez que estos también estén dispersos
             // por todo el tablero, se establece la condicion de que solo se
             // van a rellenar las casillas en donde el numero que genere la
             // variable "rellenar" sea igual a 1 y, obviamente, que todavia
             // queden numeros por rellenar.                      

             // Las siguientes condiciones son para controlar la dispersion de los numeros en base
             // al numero de posibilidades que exista de que rellenar sea igual a 1
             
             // Mientras menor sea el argumento de la funcion rand, mas posibilidades
             // hay de que se tenga que rellenar esa casilla. Con esto nos evitamos
             // que faltan numeros por rellenar de los 9 que se nos piden en
             // el enunciado.
             
             if( i * y > 0)
             {
                 rellenar = rand() % 5;//<- posibilidad de 4:1
             }
             else if( i * y > 10)
             {
                  rellenar = rand() % 3;//<- posibilidad de 3:1
             }
             else if( i * y > 65)
             {
                  rellenar = rand() % 2;//<- posibilidad de 2:1
             }
             else if( i * y > 75)
             {
                  rellenar = 1;// <- Siempre va a rellenar
             }
             
             numeroAleatorio = rand() % 9 + 1;//<- va a generar un numero
                                              // entre 1 y 9 para ser comprobado
                                              
             // Una vez que "rellenar" sea igual a 1, comienza otro ciclo,
             // que es del de buscar la posicion correcta para asignar el
             // "numeroAleatorio"

             if( rellenar == 1 && numerosRellenar > 0)
             {
                 
                 numeroUsado = true;
                 while(numeroUsado == true)
                 {
                      numeroUsado = false;
                      for( int a = 0; a <= 8; a++)
                      {
                           if(numerosUsados[a] == numeroAleatorio)
                           {
                                numeroUsado = true;
                           }
                      }
                      if (numeroUsado == true)
                      {
                            numeroAleatorio = rand() % 9 + 1;//<- va a generar num entre 1 y 9;
                      }
                 }
                 
                 // Al comenzar el proceso de buscar el numero correcto para
                 // insertarlo (entiendase por esto que: NO se repita en la misma
                 // fila, NO se repita en la misma columna y NO se repita dentro
                 // de la sub-matriz de 3x3 en la que pertenezca), se asigna
                 // "validoAgregar" como FALSE, y el ciclo se va a repetir
                 // mientras siga siendo FALSE.
                 
                 validoAgregar = false;
                 
                 while( validoAgregar == false)
                 {
                     validoAgregar = true;
         
                     // Lo primero sera asignar la variable "validoAgregar" como
                     // TRUE, y en caso de que el numero coincida en la misma
                     // fila, columna o sub-matriz, se hara FALSE, se descarta
                     // dicho numero y se genera otro, reiniciando la busqueda.
                     
                     // PRIMERA BUSQUEDA: Verificar que el numero no se repita
                     // en la misma columna
                     for( int x = i; x <= i; x++)
                     {
                          for( int z = 0; z <= 8; z++)
                          {    
                               if( numeroAleatorio == sudokuMain[x][z] )
                               {
                                     // Si coincide con algun numero de esa misma columna,
                                     // automaticamente "validoAgregar" se asigna como FALSE
                                     validoAgregar = false;
                                     break;
                               }
                          }
                     }
                     
                     // Si todavia "validoAgregar" sigue siendo TRUE, se procede
                     // con la SEGUNDA BUSQUEDA: Verificar que el numero no se
                     // repita en la misma fila
                     
                     if( validoAgregar == true )
                     {
                         for ( int x = 0; x <= 8; x++ )
                         {
                             if( numeroAleatorio == sudokuMain[x][y] )
                             {
                                   // Si coincide con algun numero de esa misma fila
                                   // "validoAgregar" se hara FALSE
                                   validoAgregar = false;
                                   break;
                             }
                         }
                     }
                            
                     // Si todavia "validoAgregar" sigue siendo TRUE (osea, que
                     // el numero no se repite ni en la misma fila ni en la misma
                     // columna) se procede con la TERCERA BUSQUEDA: Verificar
                     // que dicho numero no se repita en la misma sub matriz
                     // Para ello nos ayudaremos con el valor que tengan las variables
                     // "i" y "y", que son las que rigen los dos ciclos FOR principales
                     
                     if(validoAgregar == true)
                     {
                         if( (i >= 0 && i <= 2) && (y >= 0 && y <= 2) )     // Verificamos la sub-matriz 1
                         {
                             for( int a = 0; a <= 2; a++)
                             {
                                  for (int b = 0; b <= 2; b++)
                                  {
                                      if(numeroAleatorio == sudokuMain[a][b])
                                      {
                                           validoAgregar = false;
                                           break;
                                      }
                                  }
                             }
                         }
                         else if ( (i >= 3 && i <= 5) && (y >= 0 && y <= 2) ) // Verificamos la sub-matriz 2
                         {
                             for( int a = 3; a <= 5; a++)
                             {
                                  for (int b = 0; b <= 2; b++)
                                  {
                                      if(numeroAleatorio == sudokuMain[a][b])
                                      {
                                           validoAgregar = false;
                                           break;
                                      }
                                  }
                             }                          
                         }
                         else if ( (i >= 6 && i <= 8) && (y >= 0 && y <= 2) ) // Verificamos la sub-matriz 3
                         {
                             for( int a = 6; a <= 8; a++)
                             {
                                  for (int b = 0; b <= 2; b++)
                                  {
                                      if(numeroAleatorio == sudokuMain[a][b])
                                      {
                                           validoAgregar = false;
                                           break;
                                      }
                                  }
                             }                              
                         }
                         else if ( (i >= 0 && i <= 2) && (y >= 3 && y <= 5) ) // Verificamos la sub-matriz 4
                         {
                             for( int a = 0; a <= 2; a++)
                             {
                                  for (int b = 3; b <= 5; b++)
                                  {
                                      if(numeroAleatorio == sudokuMain[a][b])
                                      {
                                           validoAgregar = false;
                                           break;
                                      }
                                  }
                             }                              
                         }
                         else if ( (i >= 3 && i <= 5) && (y >= 3 && y <= 5) ) // Verificamos la sub-matriz 5
                         {
                             for( int a = 3; a <= 5; a++)
                             {
                                  for (int b = 3; b <= 5; b++)
                                  {
                                      if(numeroAleatorio == sudokuMain[a][b])
                                      {
                                           validoAgregar = false;
                                           break;
                                      }
                                  }
                             }                              
                         }
                         else if ( (i >= 6 && i <= 8) && (y >= 3 && y <= 5) ) // Verificamos la sub-matriz 6
                         {
                             for( int a = 6; a <= 8; a++)
                             {
                                  for (int b = 3; b <= 5; b++)
                                  {
                                      if(numeroAleatorio == sudokuMain[a][b])
                                      {
                                           validoAgregar = false;
                                           break;
                                      }
                                  }
                             }                              
                         }
                         else if ( (i >= 0 && i <= 2) && (y >= 6 && y <= 8) ) // Verificamos la sub-matriz 7
                         {
                             for( int a = 0; a <= 2; a++)
                             {
                                  for (int b = 6; b <= 8; b++)
                                  {
                                      if(numeroAleatorio == sudokuMain[a][b])
                                      {
                                           validoAgregar = false;
                                           break;
                                      }
                                  }
                             }                              
                         } 
                         else if ( (i >= 3 && i <= 5) && (y >= 6 && y <= 8) ) // Verificamos la sub-matriz 8
                         {
                             for( int a = 3; a <= 5; a++)
                             {
                                  for (int b = 6; b <= 8; b++)
                                  {
                                      if(numeroAleatorio == sudokuMain[a][b])
                                      {
                                           validoAgregar = false;
                                           break;
                                      }
                                  }
                             }                              
                         }
                         else if ( (i >= 6 && i <= 8) && (y >= 6 && y <= 8) ) // Verificamos la sub-matriz 9
                         {
                             for( int a = 6; a <= 8; a++)
                             {
                                  for (int b = 6; b <= 8; b++)
                                  {
                                      if(numeroAleatorio == sudokuMain[a][b])
                                      {
                                           validoAgregar = false;
                                           break;
                                      }
                                  }
                             }                              
                         }
                     }

                     // Una vez finalizada las 3 BUSQUEDAS, si "validoAgregar"
                     // sigue siendo TRUE, se procede a agregar ese numero aleatorio
                     // en la posicion actual del ciclo:
                     
                     if(validoAgregar == true)
                     {
                           
                           numerosRellenar--;
                           sudokuMain[i][y] = numeroAleatorio;
                           numerosUsados[cuentaAgregados] = numeroAleatorio;
                           cuentaAgregados++;
                     }
                     else
                     {
                         // De lo contrario, se genera otro numero aleatorio,
                         // y como "validoAgregar" en este caso es FALSE, se reinicia
                         // el ciclo

                         if( i * y > 0)
                         {
                             rellenar = rand() % 5;
                         }
                         else if( i * y > 10)
                         {
                              rellenar = rand() % 3;
                         }
                         else if( i * y > 60)
                         {
                              rellenar = rand() % 2;
                         }
                         else if( i * y > 75)
                         {
                              rellenar = 1 ;
                         }
                         
                         numeroAleatorio = rand() % 9 + 1;//<- se genera otro numero aleatori entre 1 y 9

                     }              
                 }
             }
         }
    }
    return 0;
}
int Sudoku::mostrarTablero( int sudokuMain[9][9] )
{
    // La la finalidad del metodo "mostrarTablero" es puramente estetica.
    // Aqui lo que se hace es dibujarle en pantalla al jugador el tablero
    // con la situacion actual del juego.
    // El trazado del tablero se hace linea por linea, sumando 19
    // lineas que dibujan el tablero como tal (incluidos los numeros), y
    // las dos primeras lineas que dibujan el titulo del juego,
    // Todo esto se hace con ciclos for, cout's y printf ...

    //  ---- [ El titulo de la ventana ]  ----  //

    for(int a = 1; a <= 10; a++)
    {
        printf("%c",178);
    }
    for(int a = 1; a <= 10; a++)
    {
        printf("%c",177);
    }
    for(int a = 1; a <= 10; a++)
    {
        printf("%c",176);
    }
    cout<<"       Sudoku!      ";
    for(int a = 1; a <= 10; a++)
    {
        printf("%c",176);
    }
    for(int a = 1; a <= 10; a++)
    {
        printf("%c",177);
    }
    for(int a = 1; a <= 10; a++)
    {
        printf("%c",178);
    }
    for(int a = 1; a <= 80; a++)
    {
        printf("%c",223);
    }    
    //  ---- [ El tablero como tal ]  ----  //
    int ii = 0;
    cout<<"\t       1  2  3     4  5  6     7  8  9      > : Fil  -  \\/ : Col "<<endl;
    for( int i = 1; i <= 19; i++ )
    {
         if( (i >= 3 && i <= 5) || (i >= 9 && i <= 11) || (i >= 15 && i <= 17) )
         {
             cout<<"\t  "<<(ii + 1)<<" ";
         }
         else
         {
             cout<<"\t    ";
         }
         if( i == 1)
         {
            printf("%c",201); for(int a = 1; a <= 35; a++) { if(a == 12 || a == 24){ printf("%c",203); } else { printf("%c",205); } } printf("%c",187); 
         }
         else if (i == 2)
         {
            printf("%c",186); for(int a = 1; a <= 35; a++) { if(a == 12 || a == 24) { printf("%c",186); } else { if(a != 34){ cout<<" "; } else { cout<<"  "; printf("%c",186);} } }  cout<<"   Faltan "<<Sudoku::casillasVacias(sudokuMain)<<" casillas";
         }
         else if ( i == 6 || i == 8 || i == 12 || i == 14 )
         {
             printf("%c",186); for(int a = 1; a <= 33; a++){ if(a == 1) { cout<<" "; } if(a == 11 || a == 23){ printf("%c",186);} else { cout<<" "; } if(a == 33){ cout<<" "; } } printf("%c",186);
         }
         else if ( i == 7 || i == 13 )
         {
            for(int a = 1; a <= 33; a++){ if(a == 1) { printf("%c",204); printf("%c",205); } if(a == 11 || a == 23) { printf("%c",206); } else { printf("%c",205); } if(a == 33) { printf("%c",205); printf("%c",185);  } }
         }
         else if (i == 18)
         {       
            printf("%c",186); for(int a = 1; a <= 35; a++) { if(a == 12 || a == 24) { printf("%c",186); } else { cout<<" "; } } printf("%c",186); 
         }
         else if (i == 19)
         {
            printf("%c",200); for(int a = 1; a <= 35; a++) { if(a == 12 || a == 24){ printf("%c",202); } else { printf("%c",205); } } printf("%c",188);              
         }
         else 
         {
         // ----- [ Trazado de los numeros ] ------//
            printf("%c",186); 
            for(int y = 0; y <= 8; y++)
            {      
                if( y == 0)
                {
                    cout<<" ";
                }
                       
                if(sudokuMain[ii][y] == 0)
                {  
                   cout<<" _ ";          
                }
                else
                {
                    cout<<" "<<sudokuMain[ii][y]<<" ";
                }
            
                if( y == 2 || y == 5 )
                {
                    cout<<" ";
                    printf("%c",186);
                    cout<<" ";
                }
                if( y == 8 )
                {
                    cout<<" ";
                    printf("%c",186);
                    ii++;
                }            
            }
         // ----- [ Trazado de los numeros ] ------//
         } 
         cout<<endl;
    }
    return 0;
}
int Sudoku::agregarNumero(int sudokuMain[9][9], int posX, int posY, int numero)
{
    // Este metodo el similar al de "generarTablero", lo que cambia es que
    // el jugador selecciona arbitrariamente el numero que desea agregar y
    // la coordenada donde desea agregarlo
    // Ademas, se procede a verificar si puede o no agregarlo en dicha posicion
    // y se le muestra en pantalla el resultado
    
     bool validoAgregar = false;
     
     if(sudokuMain[posX-1][posY-1]!=0)
     {
        return 3;
     }
     
     while( validoAgregar == false)
     {
         validoAgregar = true;
         for( int x = posX-1; x <= posX-1; x++)
         {
              for( int z = 0; z <= 8; z++)
              {    
                   if( numero == sudokuMain[x][z] )
                   {
                         return 1;
                   }
              }
         }
         if(validoAgregar == true)
         {
             for ( int x = 0; x <= 8; x++ )
             {
                if( numero == sudokuMain[x][posY-1] )
                 {
                       return 1;
                 }
             }
         }

         if(validoAgregar == true)
         {

             if( ((posX -1) >= 0 && (posX -1) <= 2) && ((posY - 1) >= 0 && (posY - 1) <= 2) ) // Sub matriz 1
             {
                 for( int a = 0; a <= 2; a++)
                 {
                      for (int b = 0; b <= 2; b++)
                      {
                          if(numero == sudokuMain[a][b])
                          {
                               return 1;
                          }
                      }
                 }
             }
             else if ( ((posX -1) >= 3 && (posX -1) <= 5) && ((posY - 1) >= 0 && (posY - 1) <= 2) ) // Sub matriz 2
             {
                 for( int a = 3; a <= 5; a++)
                 {
                      for (int b = 0; b <= 2; b++)
                      {
                          if(numero == sudokuMain[a][b])
                          {
                               return 1;
                          }
                      }
                 }                          
             }
             else if ( ((posX -1) >= 6 && (posX -1) <= 8) && ((posY - 1) >= 0 && (posY - 1) <= 2) ) // Sub matriz 3
             {
                 for( int a = 6; a <= 8; a++)
                 {
                      for (int b = 0; b <= 2; b++)
                      {
                          if(numero == sudokuMain[a][b])
                          {
                               return 1;
                          }
                      }
                 }                              
             }
             else if ( ((posX -1) >= 0 && (posX -1) <= 2) && ((posY - 1) >= 3 && (posY - 1) <= 5) ) // Sub matriz 4
             {
                 for( int a = 0; a <= 2; a++)
                 {
                      for (int b = 3; b <= 5; b++)
                      {
                          if(numero == sudokuMain[a][b])
                          {
                               return 1;
                          }
                      }
                 }                              
             }
             else if ( ((posX -1) >= 3 && (posX -1) <= 5) && ((posY - 1) >= 3 && (posY - 1) <= 5) ) // Sub matriz 5
             {
                 for( int a = 3; a <= 5; a++)
                 {
                      for (int b = 3; b <= 5; b++)
                      {
                          if(numero == sudokuMain[a][b])
                          {
                               return 1;
                          }
                      }
                 }                              
             }
             else if ( ((posX -1) >= 6 && (posX -1) <= 8) && ((posY - 1) >= 3 && (posY - 1) <= 5) ) // Sub matriz 6
             {
                 for( int a = 6; a <= 8; a++)
                 {
                      for (int b = 3; b <= 5; b++)
                      {
                          if(numero == sudokuMain[a][b])
                          {
                               return 1;
                          }
                      }
                 }                              
             }
             else if ( ((posX -1) >= 0 && (posX -1) <= 2) && ((posY - 1) >= 6 && (posY - 1) <= 8) ) // Sub matriz 7
             {
                 for( int a = 0; a <= 2; a++)
                 {
                      for (int b = 6; b <= 8; b++)
                      {
                          if(numero == sudokuMain[a][b])
                          {
                               return 1;
                          }
                      }
                 }                              
             } 
             else if ( ((posX -1) >= 3 && (posX -1) <= 5) && ((posY - 1) >= 6 && (posY - 1) <= 8) ) // Sub matriz 8
             {
                 for( int a = 3; a <= 5; a++)
                 {
                      for (int b = 6; b <= 8; b++)
                      {
                          if(numero == sudokuMain[a][b])
                          {
                               return 1;
                          }
                      }
                 }                              
             }
             else if ( ((posX -1) >= 6 && (posX -1) <= 8) && ((posY - 1) >= 6 && (posY - 1) <= 8) ) // Sub matriz 9
             {
                 for( int a = 6; a <= 8; a++)
                 {
                      for (int b = 6; b <= 8; b++)
                      {
                          if(numero == sudokuMain[a][b])
                          {
                               return 1;
                          }
                      }
                 }                              
             }
         }
         if(validoAgregar == true)
         {
             sudokuMain[posX-1][posY-1] = numero;             
             return 2;
         }
         else
         {
             return 1;
         }           
     }
    return 0;
}
int Sudoku::casillasVacias(int sudokuMain[9][9])
{

    int contador = 0;
    for(int rb = 0; rb <= 8; rb++)
    {
        for(int k = 0; k <= 8; k++)
        {
            if( sudokuMain[rb][k] == 0 )
            {
                contador++;
            }
        }
    }
    return contador; 
       
}
int Sudoku::jugar(int sudokuMain[9][9])
{
    // Este metodo muestra en todo momento por pantalla las opciones que tiene
    // el jugador: Agregar un numero manualmente en el tablero o pedirle a la 
    // maquina que genere una solucion.
    
    int fila, columna, accion = 0, numeroIngresar;

    do{
        system("cls");
        Sudoku::mostrarTablero(sudokuMain);
        do{
           cout<<"\t    Que deseas hacer?\n\t    1: Rellenar una casilla - 2: Generar Solucion - 3: Salir ?\t";  ;      
           while(!(cin >> accion)){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                system("cls");
                Sudoku::mostrarTablero(sudokuMain);
                cout<<"\t    Que deseas hacer?\n\t    1: Rellenar una casilla - 2: Generar Solucion - 3: Salir ?\t";               
            }
        } while( accion == 0 );
        
        if( accion == 1)
        {
            system("cls");
            Sudoku::mostrarTablero(sudokuMain);
            cout<<"\t              Selecciona la fila : "; 
             
            while(!(cin >> fila)){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                system("cls");
                Sudoku::mostrarTablero(sudokuMain);
                cout<<"\t              Selecciona la fila : ";               
            
            }
            cout<<"\t           Selecciona la columna : ";
            while(!(cin >> columna)){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                system("cls");
                Sudoku::mostrarTablero(sudokuMain);
                cout<<"\t           Selecciona la columna : ";            
            }
            if(fila > 9 || fila < 1 || columna > 9 || columna < 1)
            {
                      cout<<"\t\t\tCoordenada Invalida!! ";
                      Sleep(2000);
            } else {
                cout<<"   Escribe el numero a ingresar ( 1 - 9) : ";
                while(!(cin >> numeroIngresar)){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    system("cls");
                    Sudoku::mostrarTablero(sudokuMain);
                    cout<<"\t              Selecciona la fila : "<<fila<<endl; 
                    cout<<"\t           Selecciona la columna : "<<columna<<endl; 
                    cout<<"   Escribe el numero a ingresar ( 1 - 9) : ";       
                }
                if(numeroIngresar > 0 && numeroIngresar <= 9)
                {
                      if(Sudoku::agregarNumero(sudokuMain,fila,columna,numeroIngresar) == 2)
                      {
                            system("cls");
                            Sudoku::mostrarTablero(sudokuMain);
                            cout<<"\t\tOk, el numero es valido"<<endl;
                            Sleep(1000);
                      }
                      else if (Sudoku::agregarNumero(sudokuMain,fila,columna,numeroIngresar) == 1)
                      {
                            system("cls");
                            Sudoku::mostrarTablero(sudokuMain);
                            cout<<"\t\tEl numero se repite! Ingresa otro"<<endl;
                            Sleep(1000);
                      }
                      else if (Sudoku::agregarNumero(sudokuMain,fila,columna,numeroIngresar) == 3)
                      {
                            system("cls");
                            Sudoku::mostrarTablero(sudokuMain);
                            cout<<"\t       Esa casilla no esta vacia! Escoge Otra\t"<<endl;  
                            Sleep(1500);                        
                      }
                }  
            }
        }
        if( accion == 2)
        {
             system("cls");
             Sudoku::generarSolucion(0,0,sudokuMain);
             Sudoku::mostrarTablero(sudokuMain);
             break;
        }
        if( accion == 3){
            system("cls");
            cout<<"\n\n\n\n\n\n\t\t\t\t   Adios!   :)  "<<endl;
            Sleep(1500); 
            system("taskkill /IM Sudoku.exe");
        }
    }while(Sudoku::casillasVacias(sudokuMain) > 0); 
     
    if( Sudoku::casillasVacias(sudokuMain) == 0 )
    {
        Sudoku::sudokuGanar(sudokuMain);
    }
    
    return 0;
}
int Sudoku::sudokuGanar( int sudokuMain[9][9] )
{
    // Este metodo se ejecuta cuando el jugador logra rellenar todo el tablero
    // del sudoku o le pide a la maquina hacerlo
    
    system("cls");
    Sudoku::mostrarTablero(sudokuMain);
    cout<<"\n\t\t        -- Felicidades!! Has ganado :) --  "<<endl;
    Sleep(3000);
    system("cls");
    Sudoku::mostrarTablero(sudokuMain);
    cout<<"\n\t  Jugar de nuevo?        ( 1: Si  -  Cualquier otra tecla: No )"<<endl;
    
    int res;
    cin>>res;
    
    if(res == 1)
    {
        Sudoku sudokuMainJuego;                         // Instanciamos un objeto de la clase Sudoku (otra vez)
        sudokuMainJuego.generarTablero(sudokuMain,9);   // Generamos el tablero(otra vez)
        sudokuMainJuego.jugar(sudokuMain);              // Iniciamos el juego (otra vez)   
                       
    }
    else
    {
        system("tskill sudoku"); // Enviar la señal de cierre para Windows XP Home
        system("taskkill /IM Sudoku.exe"); // Enviar señal de cierre para Windows XP Profesional, Vista y posteriores...
    }  
       
    return 0;
}
