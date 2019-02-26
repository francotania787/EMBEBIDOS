#include "datos_entrenamiento.h" // matriz principal 
#include"datos_test.h"

////////////////Radio para reduccion/////////////////////////
float radio = 0.1; // radio con la seleccion para la base
String r;
/////////////////Vectores//////////////////////////////////////////
float matriz_final[60][5];
float matriz_final1[60][5];
float matriz_final_1 [5];
float matriz_final_2 [5];
float matriz_final_3 [5];
float vec_dist_1[40];
float vec_c_dist_1[40];
float vec_divi_1[40];
float vec_dist_2[40];
float vec_c_dist_2[40];
float vec_divi_2[40];
float vec_dist_3[40];
float vec_c_dist_3[40];
float vec_divi_3[40];

///////////////Varaibles de control ////////////////
int i;
int j;
float dist = 0;
float dist_total = 0;
float mayor;
float divi;
int cont;
float mayor_2;
float divi_2;
float mayor_3;
float divi_3;
int cont_total;
int cont_f = 0;
float promedio;
float suma = 0;
 float r1 = 0.2;
float dist1 = 0;
float dist_total1 = 0;
float mayor1;
float divi1;
int cont1;
float mayor_21;
float divi_21;
float mayor_31;
float divi_31;
int cont_total1;
int cont_f1 = 0;
float promedio1;
float suma1 = 0;
int on = 0, a = 0, b = 0, total = 0, on1 = 0,on2=0,on3=0,on4=0, a1 = 0, b1 = 0;
float result;
float result1;
int total1=0;
///////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);
      Serial.println("**********************UTN**************************");
      Serial.println(" ");
          Serial.println("Para que la matriz reducida por el radio ingresado sea graficada");
          delay(250);
          Serial.println("Dicha matriz debe tener un rendimiento de prediccion knn");
          delay(250);
          Serial.println("Mayor al rendimiento de la matriz original y mayor a 79%");
          delay(250);
          Serial.println("Caso contrario se grafica la matriz minima que cumple este requisito");
          delay(250);
  Serial.println(" ");
  Serial.println("Ingrese un radio normalizado SIN COMA");
}

///////////////////////////////////////////////////////////
void loop() {
  if (Serial.available()>0){// verifico si hay dato disponible
    r=Serial.readString();
        Serial.print("valor: ");
    Serial.println(r);
     radio = r.toFloat();
     if(radio<10){
     radio=radio/10;
     Serial.print("Radio: ");
    Serial.println(radio);
          Serial.print(" ");
          }
          else if(radio>9 && radio<100){
            radio=radio/100;
            Serial.print("Valor float radio:  ");
    Serial.println(radio);
    Serial.println(" ");
            }
  reduccion();
  prediccion2();
  prediccion1();
  comparacion2();

 }
 
}

/////////////////////////////////
void prediccion1 (){
  if (on == 0) {
       Serial.println(" ");
    for (int i = 0; i <= 29; i++) {
      result = knn(cont, 5, 3, 3, prueba[i]);
      if (result == prueba[i][4]) {
        a++;
      }
      else {
        b++;
      }
    }
   Serial.println("Matriz Reducirda");
    Serial.print("Aciertos: ");
    Serial.println(a);
    Serial.print("Erroneos: ");
    Serial.println(b);
    total = (a * 100) / 30;
    Serial.print("Eficiencia: ");
   Serial.print(total);
   Serial.println("%");
   on=1;
  }
  }

////////////////////////////////////////////////////////////////
float knn (int fila, int col, int k, int label, float datos[]) {
  int c = 0; // movernos en columnas
  int f = 0; // movernos en fila
  float k_vecinos_dist[k]; // vector de almacenamiento de k distancias menores
  float etiquetas [2][label]; // matriz y conteo de etiquetas
  float distk = 0; // variable que almacena cada distancia
  float dist_totalk = 0; // varaible para almacenamiento de distancia
  // llenar vector k_vecinos_dist con valores altos
  float eti_menor[k]; //vector de etiquetas de distancia menor
  int k_cont = 0;
  int i = 0;
  float clase; // retornar etiqueta
  float comparacion; // comparar k-vecino mayor
  for (; c < k; c++) {
    k_vecinos_dist[c] = 2000.0 + c; // valores altos y ordenados
  }
  c = 0; // reiniciar varaible
  // llenar matriz etiquetas
  for (; c < label; c++) {
    etiquetas[0][c] = c + 1; // lleno con valores de etiqueta
    etiquetas[1][c] = 0; // lleno con el conteo de etiqueta
  }
  c = 0; //renicio variable
  // la distacia mas corta del nuevo punto hacia la matriz
  for (; f < fila; f++) {
    for (; c < col - 1; c++) {
      distk = distk + pow((matriz_final[f][c] - datos[c]), 2); // distancia entre dos puntos
    }
    dist_totalk = sqrt(distk); // raiz de la formula
    // Serial.println(dist_total);
    for (; k_cont < k; k_cont++) { // determinar las k distancias menores y ordenarlas
      if (dist_totalk < k_vecinos_dist[k_cont]) {
        k_vecinos_dist[k_cont] = dist_totalk; // asignar nuevo valor a vector de distancias menores
        eti_menor[k_cont] = matriz_final[f][col - 1]; // col =5 , 4
      }
    }
    k_cont = 0;
    distk = 0;
    dist_totalk = 0;
    c = 0;
  } //for fila
  // seleccion de los k vecino
  for (; c < label; c++) {
    for (; k_cont < k; k_cont++) { // recorro cada posicion de eti_menor y comparo con etiquetas y cuento si son iguales
      if (etiquetas[0][c] == eti_menor[k_cont]) {
        i++;
        etiquetas[1][c] = i;
      }
    }
    k_cont = 0;
    i = 0;
  }
  c = 1;
  comparacion = etiquetas[1][0];
  clase = etiquetas[0][0];
  for (; c < label; c++) {
    if (etiquetas[1][c] > comparacion) { // comparacion entre valores de suma de etiqueta
      clase = etiquetas[0][c];
      comparacion = etiquetas[1][c];
    }
  }
  comparacion = 0;
  c = 0;
  return clase;
}


////////////////////////////////////////////////////////////////////////////
void prediccion2 (){
  if (on1 == 0) {
    for (int i = 0; i <= 29; i++) {
      result1 = knn1(30, 5, 3, 3, prueba[i]);
      if (result1 == prueba[i][4]) {
        a1++;
        //Serial.print(a1);
        //Serial.print(", ");
      //     Serial.println(" ");
      }
      else {
        b1++;
        }
    }
   Serial.println("Matriz Original");
    Serial.print("Aciertos Matriz Original: ");
    Serial.println(a1);
    Serial.print("Erroneos Matriz Original: ");
    Serial.println(b1);
    total1 = (a1 * 100) / 30;
    Serial.print("Eficiencia Matriz Original: ");
   Serial.print(total1);
   Serial.println("%");
  }
   on1 = 1;
  }

////////////////////////////////////////////////////////////////
float knn1 (int fila1, int col1, int k1, int label1, float datos1[]) {
  i=0;
  j=0;
  int c1 = 0; // movernos en columnas
  int f1 = 0; // movernos en fila
  int i1=0;
  float k_vecinos_dist1[k1]; // vector de almacenamiento de k distancias menores
  float etiquetas1 [2][label1]; // matriz y conteo de etiquetas
  float distk1 = 0; // variable que almacena cada distancia
  float dist_totalk1 = 0; // varaible para almacenamiento de distancia
  // llenar vector k_vecinos_dist con valores altos
  float eti_menor1[k1]; //vector de etiquetas de distancia menor
  int k_cont1 = 0;
  float clase1; // retornar etiqueta
  float comparacion1; // comparar k-vecino mayor
  
  for (; c1 < k1; c1++) {
    k_vecinos_dist1[c1] = 2000.0 + c1; // valores altos y ordenados
  }
  c1 = 0; // reiniciar varaible
  // llenar matriz etiquetas
  for (; c1 < label1; c1++) {
    etiquetas1[0][c1] = c1 + 1; // lleno con valores de etiqueta
    etiquetas1[1][c1] = 0; // lleno con el conteo de etiqueta
  }
  c1 = 0; //renicio variable
  // la distacia mas corta del nuevo punto hacia la matriz
  for (; f1 < fila1; f1++) {
    for (; c1 < col1 - 1; c1++) {
      distk1 = distk1 + pow((matriz[f1][c1] - datos1[c1]), 2); // distancia entre dos puntos
    }
    dist_totalk1 = sqrt(distk1); // raiz de la formula
    // Serial.println(dist_total);
    for (; k_cont1 < k1; k_cont1++) { // determinar las k distancias menores y ordenarlas
      if (dist_totalk1 < k_vecinos_dist1[k_cont1]) {
        k_vecinos_dist1[k_cont1] = dist_totalk1; // asignar nuevo valor a vector de distancias menores
        eti_menor1[k_cont1] = matriz_final1[f1][col1 - 1]; // col =5 , 4
      }
    }
    k_cont1 = 0;
    distk1 = 0;
    dist_totalk1 = 0;
    c1 = 0;
  } //for fila
  // seleccion de los k vecino
  for (; c1 < label1; c1++) {
    for (; k_cont1 < k1; k_cont1++) { // recorro cada posicion de eti_menor y comparo con etiquetas y cuento si son iguales
      if (etiquetas1[0][c1] == eti_menor1[k_cont1]) {
        i++;
        etiquetas1[1][c1] = i;
      }
    }
    k_cont1 = 0;
    i1 = 0;
  }
  c1 = 1;
  comparacion1 = etiquetas1[1][0];
  clase1 = etiquetas1[0][0];
  for (; c1 < label1; c1++) {
    if (etiquetas1[1][c1] > comparacion1) { // comparacion entre valores de suma de etiqueta
      clase1 = etiquetas1[0][c1];
      comparacion1 = etiquetas1[1][c1];
    }
  }
  comparacion1 = 0;
  c1 = 0;
  return clase1;
}



  /////////////////////////////////////////
  void reduccion(){
  if(on3==0){

 // Serial.println("La seleccion se hace con 0.2");
 
  for (i = 0; i <= 3; i++) {  // para recorrer las columnas
    for ( j = 0; j <= 39; j++) {   // para recorrer las filas
      suma +=  matriz[j][i]; // se guarda en la variable
      promedio = suma / 40.0;   // la suma total se divide para el numero de datos
    }
    
    matriz_final_1[i] = promedio;
    matriz_final_1[4] = 1;
    suma = 0;      // se reinicia la suma
    promedio = 0;
    
    for ( j = 40; j <= 79; j++) {   // para recorrer las filas
      suma +=  matriz[j][i]; // se guarda en la variable
      promedio = suma / 40.0;   // la suma total se divide para el numero de datos
    }
    matriz_final_2[i] = promedio;
    matriz_final_2[4] = 2;
    suma = 0;      // se reinicia la suma
    promedio = 0;
    
    for ( j = 80; j <= 119; j++) {   // para recorrer las filas
      suma +=  matriz[j][i]; // se guarda en la variable
      promedio = suma / 40.0;   // la suma total se divide para el numero de datos
    }
    matriz_final_3[i] = promedio;
    matriz_final_3[4] = 3;
    suma = 0;      // se reinicia la suma
    promedio = 0;
  }
  
  /////////////////////////////////////////////////////////////////////////////////////
  for ( int k = 0; k <= 39; k++) {   // para recorrer las filas
    for (int l = 0; l <= 3; l++) {  // para recorrer las columnas
      dist = dist + pow(matriz[k][l] - matriz_final_1[l], 2); // distancia de un punto
    }
    dist_total = sqrt(dist); // raiz para la distancia
    vec_dist_1[k] = dist_total;  // guardamos en un vector
    vec_c_dist_1[k] = dist_total; // guardamos en un vector copia
    dist = 0; // reinicio de variables
    dist_total = 0; // reinicio de variables
  }
  
  for (int z = 0; z < 40; z++) {  // determinar el mayor de todo el vector
    if (vec_c_dist_1[z] > mayor) { // metodo para determinar el mayor
      mayor = vec_c_dist_1[z]; //obtenemos el numero mayor
    }
  }
  
  for (int z = 0; z < 40; z++) {  // realizamos la normalizada
    divi = vec_dist_1[z] / mayor; // dividimos cada puesto del vector para  el numero mayor
    vec_divi_1[z] = divi; // guardamos el resultado
  }
  
  for (int z = 0; z < 40; z++) { // aciertos en el radio establecido
    if (vec_divi_1[z] <= radio) { // comparacion con el radio
      cont++; // contador de terminos acertados
    }
  }
  
  ///////////////////////////////////////////////////////////////////////////////////////
  for ( int k = 40; k <= 79; k++) {   // para recorrer las filas
    for (int l = 0; l <= 3; l++) {  // para recorrer las columnas
      dist = dist + pow(matriz[k][l] - matriz_final_2[l], 2);// distancia de un punto
    }
    dist_total = sqrt(dist); // raiz para la distancia
    vec_dist_2[k - 40] = dist_total; // guardamos en un vector
    vec_c_dist_2[k - 40] = dist_total;// guardamos en un vector copia
    dist = 0;// reinicio de variables
    dist_total = 0;// reinicio de variables
  }
  for (int z = 0; z < 40; z++) {// determinar el mayor de todo el vector
    if (vec_c_dist_2[z] > mayor_2) { // metodo para determinar el mayor
      mayor_2 = vec_c_dist_2[z];// metodo para determinar el mayor
    }
  }
  for (int z = 0; z < 40; z++) {// realizamos la normalizada
    divi_2 = vec_dist_2[z] / mayor_2;// dicidimos cada puesto del vector para  el numero mayor
    vec_divi_2[z] = divi_2;// guardamos el resultado
  }
  for (int z = 0; z < 40; z++) {// aciertos en el radio establecido
    if (vec_divi_2[z] <= radio) { // comparacion con el radio
      cont++;// contador de terminos acertados
    }
  }
  
  ///////////////////////////////////////////////////////////
  for ( int k = 80; k <= 119; k++) {   // para recorrer las filas
    for (int l = 0; l <= 3; l++) {  // para recorrer las columnas
      dist = dist + pow(matriz[k][l] - matriz_final_3[l], 2);// distancia de un punto
    }
    dist_total = sqrt(dist); // raiz para la distancia
    vec_dist_3[k - 80] = dist_total;// guardamos en un vector
    vec_c_dist_3[k - 80] = dist_total;// guardamos en un vector copia
    dist = 0;// reinicio de variables
    dist_total = 0;// reinicio de variables
  }
  for (int z = 0; z < 40; z++) {// determinar el mayor de todo el vector
    if (vec_c_dist_3[z] > mayor_3) { // metodo para determinar el mayor
      mayor_3 = vec_c_dist_3[z];// metodo para determinar el mayor
    }
  }
  for (int z = 0; z < 40; z++) {// realizamos la normalizada
    divi_3 = vec_dist_3[z] / mayor_3;// dicidimos cada puesto del vector para  el numero mayor
    vec_divi_3[z] = divi_3;// dicidimos cada puesto del vector para  el numero mayor
  }
  for (int z = 0; z < 40; z++) {// aciertos en el radio establecido
    if (vec_divi_3[z] <= radio) { // comparacion con el radio
      cont++;// contador de terminos acertados
    }
  }
  
  ///////////////////////Obtencion de los aciertos////////////////////////////////////
  matriz_final[cont][5]; // declaramos las filas de la matriz
  for (int z = 0; z < 40; z++) {
    if (vec_divi_1[z] <= radio) { //
      cont_f++;
      for (int x = 0; x <= 3; x++) {
        matriz_final[cont_f - 1][x] = matriz[z][x];
        matriz_final[cont_f - 1][4] = 1;
      }
    }
  }
  
  for (int z = 0; z < 40; z++) {
    if (vec_divi_2[z] <= radio) { //
      cont_f++;
      for (int x = 0; x <= 3; x++) {
        matriz_final[cont_f - 1][x] = matriz[z + 40][x];
        matriz_final[cont_f - 1][4] = 2;
      }
    }
  }
  
  for (int z = 0; z < 40; z++) {
    if (vec_divi_3[z] <= radio) { //
      cont_f++;
      for (int x = 0; x <= 3; x++) {
        matriz_final[cont_f - 1][x] = matriz[z + 80][x];
        matriz_final[cont_f - 1][4] = 3;
      }
    }
  }
    
    }
    on3=1;
  }


void comparacion2(){
  if(on2==0){
  if(total>total1 && total>=80){
     Serial.println(" ");
     Serial.println("*********Operacion reduccion exitosa*********");
      Serial.println(" "); 
     Serial.print("Cantidad filas Matriz Reducida = "); Serial.println(cont);
         Serial.println(" "); 
  for ( int k = 0; k < cont; k++) {   // para recorrer las filas
    for (int l = 0; l <= 4; l++) {  // para recorrer las columnas
      Serial.print(matriz_final[k][l]);
      Serial.print(',');
    }
    Serial.println(' ');
  } 
    }
  
  else{
         Serial.println(" ");
    Serial.println("Radio no cumple con los parametros minimos");
    Serial.println("A continuacion se presenta la solucion minima optima con radio de eleccion de 0.2");
Serial.println(" ");

matriz_final[60][5];
matriz_final_1 [5];
matriz_final_2 [5];
matriz_final_3 [5];
vec_dist_1[40];
vec_c_dist_1[40];
vec_divi_1[40];
vec_dist_2[40];
vec_c_dist_2[40];
vec_divi_2[40];
vec_dist_3[40];
vec_c_dist_3[40];
vec_divi_3[40];
//dist = 0;
//dist_total = 0;
mayor=0;
divi=0;
cont=0;
mayor_2=0;
divi_2=0;
mayor_3=0;
divi_3=0;
cont_total=0;
cont_f = 0;
promedio=0;
suma = 0;
 
      if(on4==0){
 // Serial.println("La seleccion se hace con 0.2");
 
  for (i = 0; i <= 3; i++) {  // para recorrer las columnas
    for ( j = 0; j <= 39; j++) {   // para recorrer las filas
      suma +=  matriz[j][i]; // se guarda en la variable
      promedio = suma / 40.0;   // la suma total se divide para el numero de datos
    }
    
    matriz_final_1[i] = promedio;
    matriz_final_1[4] = 1;
    suma = 0;      // se reinicia la suma
    promedio = 0;
    
    for ( j = 40; j <= 79; j++) {   // para recorrer las filas
      suma +=  matriz[j][i]; // se guarda en la variable
      promedio = suma / 40.0;   // la suma total se divide para el numero de datos
    }
    matriz_final_2[i] = promedio;
    matriz_final_2[4] = 2;
    suma = 0;      // se reinicia la suma
    promedio = 0;
    
    for ( j = 80; j <= 119; j++) {   // para recorrer las filas
      suma +=  matriz[j][i]; // se guarda en la variable
      promedio = suma / 40.0;   // la suma total se divide para el numero de datos
    }
    matriz_final_3[i] = promedio;
    matriz_final_3[4] = 3;
    suma = 0;      // se reinicia la suma
    promedio = 0;
  }
  
  /////////////////////////////////////////////////////////////////////////////////////
  for ( int k = 0; k <= 39; k++) {   // para recorrer las filas
    for (int l = 0; l <= 3; l++) {  // para recorrer las columnas
      dist = dist + pow(matriz[k][l] - matriz_final_1[l], 2); // distancia de un punto
    }
    dist_total = sqrt(dist); // raiz para la distancia
    vec_dist_1[k] = dist_total;  // guardamos en un vector
    vec_c_dist_1[k] = dist_total; // guardamos en un vector copia
    dist = 0; // reinicio de variables
    dist_total = 0; // reinicio de variables
  }
  
  for (int z = 0; z < 40; z++) {  // determinar el mayor de todo el vector
    if (vec_c_dist_1[z] > mayor) { // metodo para determinar el mayor
      mayor = vec_c_dist_1[z]; //obtenemos el numero mayor
    }
  }
  
  for (int z = 0; z < 40; z++) {  // realizamos la normalizada
    divi = vec_dist_1[z] / mayor; // dividimos cada puesto del vector para  el numero mayor
    vec_divi_1[z] = divi; // guardamos el resultado
  }
  
  for (int z = 0; z < 40; z++) { // aciertos en el radio establecido
    if (vec_divi_1[z] <= r1) { // comparacion con el radio
      cont++; // contador de terminos acertados
    }
  }
  
  ///////////////////////////////////////////////////////////////////////////////////////
  for ( int k = 40; k <= 79; k++) {   // para recorrer las filas
    for (int l = 0; l <= 3; l++) {  // para recorrer las columnas
      dist = dist + pow(matriz[k][l] - matriz_final_2[l], 2);// distancia de un punto
    }
    dist_total = sqrt(dist); // raiz para la distancia
    vec_dist_2[k - 40] = dist_total; // guardamos en un vector
    vec_c_dist_2[k - 40] = dist_total;// guardamos en un vector copia
    dist = 0;// reinicio de variables
    dist_total = 0;// reinicio de variables
  }
  for (int z = 0; z < 40; z++) {// determinar el mayor de todo el vector
    if (vec_c_dist_2[z] > mayor_2) { // metodo para determinar el mayor
      mayor_2 = vec_c_dist_2[z];// metodo para determinar el mayor
    }
  }
  for (int z = 0; z < 40; z++) {// realizamos la normalizada
    divi_2 = vec_dist_2[z] / mayor_2;// dicidimos cada puesto del vector para  el numero mayor
    vec_divi_2[z] = divi_2;// guardamos el resultado
  }
  for (int z = 0; z < 40; z++) {// aciertos en el radio establecido
    if (vec_divi_2[z] <= r1) { // comparacion con el radio
      cont++;// contador de terminos acertados
    }
  }
  
  ///////////////////////////////////////////////////////////
  for ( int k = 80; k <= 119; k++) {   // para recorrer las filas
    for (int l = 0; l <= 3; l++) {  // para recorrer las columnas
      dist = dist + pow(matriz[k][l] - matriz_final_3[l], 2);// distancia de un punto
    }
    dist_total = sqrt(dist); // raiz para la distancia
    vec_dist_3[k - 80] = dist_total;// guardamos en un vector
    vec_c_dist_3[k - 80] = dist_total;// guardamos en un vector copia
    dist = 0;// reinicio de variables
    dist_total = 0;// reinicio de variables
  }
  for (int z = 0; z < 40; z++) {// determinar el mayor de todo el vector
    if (vec_c_dist_3[z] > mayor_3) { // metodo para determinar el mayor
      mayor_3 = vec_c_dist_3[z];// metodo para determinar el mayor
    }
  }
  for (int z = 0; z < 40; z++) {// realizamos la normalizada
    divi_3 = vec_dist_3[z] / mayor_3;// dicidimos cada puesto del vector para  el numero mayor
    vec_divi_3[z] = divi_3;// dicidimos cada puesto del vector para  el numero mayor
  }
  for (int z = 0; z < 40; z++) {// aciertos en el radio establecido
    if (vec_divi_3[z] <= r1) { // comparacion con el radio
      cont++;// contador de terminos acertados
    }
  }
  
  ///////////////////////Obtencion de los aciertos////////////////////////////////////
  matriz_final[cont][5]; // declaramos las filas de la matriz
  for (int z = 0; z < 40; z++) {
    if (vec_divi_1[z] <= r1) { //
      cont_f++;
      for (int x = 0; x <= 3; x++) {
        matriz_final[cont_f - 1][x] = matriz[z][x];
        matriz_final[cont_f - 1][4] = 1;
      }
    }
  }
  
  for (int z = 0; z < 40; z++) {
    if (vec_divi_2[z] <= r1) { //
      cont_f++;
      for (int x = 0; x <= 3; x++) {
        matriz_final[cont_f - 1][x] = matriz[z + 40][x];
        matriz_final[cont_f - 1][4] = 2;
      }
    }
  }
  
  for (int z = 0; z < 40; z++) {
    if (vec_divi_3[z] <= r1) { //
      cont_f++;
      for (int x = 0; x <= 3; x++) {
        matriz_final[cont_f - 1][x] = matriz[z + 80][x];
        matriz_final[cont_f - 1][4] = 3;
      }
    }
  }
     Serial.println("MAtRIZ MINIMA con radio de 0.2"); 
     Serial.print("Cantidad filas Matriz Reducida = "); Serial.println(cont);
     Serial.println(" ");
  for ( int k = 0; k < cont; k++) {   // para recorrer las filas
    for (int l = 0; l <= 4; l++) {  // para recorrer las columnas
      Serial.print(matriz_final[k][l]);
      Serial.print(',');
    }
 
    Serial.println(' ');}
    }
       Serial.println(' ');
        Serial.print("Acertos:");
    Serial.println("26");
    Serial.print("Errores: ");
    Serial.println("4");
    Serial.print("Eficiencia:");
    Serial.println("80"); 
    on4=1;
    }
}on2=1;
}
