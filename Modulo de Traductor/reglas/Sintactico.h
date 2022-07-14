#ifndef SINTACTICO_H_INCLUDED
#define SINTACTICO_H_INCLUDED

#include <cstdlib>
#include <iostream>
#include <string>
#include<stdlib.h>
#include <list>
#include "lexico.h"
#include "pila.h"
#include<sstream>
#include "Semantico.h"

Lexico lexico;
Pila p;

void Sintactico(){
    int cont=0;
    string simbolo;
    int fila, columna, accion;
    bool aceptacion= false;
    simbolo = "$";

    p.push(new Terminal(simbolo));
    p.push(new Estado(0));

    lexico.entrada("entrada.txt");

    lexico.sigSimbolo();

    fila = p.top()->getEstado();
    columna = lexico.tipo;
    accion = matriz[fila][columna];
   while ( true ){
                  p.muestra();
                  cout<<endl<<"fila: "<<fila<<endl<<"columna: "<<columna<<endl<<"accion: "<<accion<<endl;
                  cout << "siguiente token: " << lexico.simbolo << endl<<endl;
                  int oldaccion = accion;
                  if(accion > 0){

                      cout<<"DESPLAZAMIENTO"<<endl;
                      simbolo =  lexico.simbolo; /// int to str
                      p.push(new Terminal(simbolo)); ///simb = string nombre de la regla
                      p.push(new Estado(accion));

                      lexico.sigSimbolo();

                      fila = p.top()->getEstado();
                      columna = lexico.tipo;
                      accion = matriz[fila][columna];
                  }
                else if(accion==-1){
                    cout << "ACEPTACION" << endl<<endl;
                    break;
                }
                else if(accion < 0){
                    cout<<"REDUCCION"<<endl;///reduccion

                    int opc = -(accion+2);
                    ///cout<<"OPC="<<opc<<endl;
                    Nodo* nuevoNodo;

                    switch(opc+1){
                        case 2: case 7: case 10: case 12: case 15: case 19: case 26: case 29: case 31: case 33:
                            nuevoNodo = new nullNodo();
                        break;
                        case 1:{
                            nuevoNodo = new Programa_R1(p);
                            nuevoNodo->muestra(1);
                            nuevoNodo->generarCodigo();
                        }

                        break;
                        case 3:
                            nuevoNodo = new Definiciones_R3(p);
                        break;
                        case 4:
                            nuevoNodo = new Definicion_R4(p);
                        break;
                        case 5:
                            nuevoNodo = new Definicion_R5(p);
                        break;
                        case 6:
                            nuevoNodo = new DefVar_R6(p);
                        break;
                        case 8:
                            nuevoNodo = new ListaVar_R8(p);
                        break;
                        case 9:
                            nuevoNodo = new DefFunc_R9(p);
                        break;
                        case 11:
                            nuevoNodo = new Parametros_R11(p);
                        break;
                        case 13:
                            nuevoNodo = new ListaParam_R13(p);
                        break;
                        case 14:
                            nuevoNodo = new BloqFunc_R14(p);
                        break;
                        case 16:
                            nuevoNodo = new DefLocales_R16(p);
                        break;
                        case 17:
                            nuevoNodo = new DefLocal_R17(p);
                        break;
                        case 18:
                            nuevoNodo = new DefLocal_R18(p);
                        break;
                        case 20:
                            nuevoNodo = new Sentencias_R20(p);
                        break;
                        case 21:
                            nuevoNodo = new Sentencia_R21(p);
                        break;
                        case 22:
                            nuevoNodo = new Sentencia_R22(p);
                        break;
                        case 23:
                            nuevoNodo = new Sentencia_R23(p);
                        break;
                        case 24:
                            nuevoNodo = new Sentencia_R24(p);
                        break;
                        case 25:
                            nuevoNodo = new Sentencia_R25(p);
                        break;
                        case 27:
                            nuevoNodo = new Otro_R27(p);
                        break;
                        case 28:
                            nuevoNodo = new Bloque_R28(p);
                        break;
                        case 30:
                            nuevoNodo = new ValorRegresa_R30(p);
                        break;
                        case 32:
                            nuevoNodo = new Argumentos_R32(p);
                        break;
                        case 34:
                            nuevoNodo = new ListaArgumentos_R34(p);
                        break;
                        case 35:
                            nuevoNodo = new Termino_R35(p);
                        break;
                        case 36:
                            nuevoNodo = new Termino_R36(p);
                        break;
                        case 37:
                            nuevoNodo = new Termino_R37(p);
                        break;
                        case 38:
                            nuevoNodo = new Termino_R38(p);
                        break;
                        case 39:
                            nuevoNodo = new Termino_R39(p);
                        break;
                        case 40:
                            nuevoNodo = new LlamadaFunc_R40(p);
                        break;
                        case 41:
                            nuevoNodo = new SentenciaBloque_R41(p);
                        break;
                        case 42:
                            nuevoNodo = new SentenciaBloque_R42(p);
                        break;
                        case 43:
                            nuevoNodo = new Expresion_R43(p);
                        break;
                        case 44:
                            nuevoNodo = new Expresion_R44(p);
                        break;
                        case 45:
                            nuevoNodo = new Expresion_R45(p);
                        break;
                        case 46:
                            nuevoNodo = new Expresion_R46(p);
                        break;
                        case 47:
                            nuevoNodo = new Expresion_R47(p);
                        break;
                        case 48:
                            nuevoNodo = new Expresion_R48(p);
                        break;
                        case 49:
                            nuevoNodo = new Expresion_R49(p);
                        break;
                        case 50:
                            nuevoNodo = new Expresion_R50(p);
                        break;
                        case 51:
                            nuevoNodo = new Expresion_R51(p);
                        break;
                        case 52:
                            nuevoNodo = new Expresion_R52(p);
                        break;

                    }
///********************************************************************mover de lugar******************************************
/*
                    ///aqui te dice cuantos eliminar
                    int absoluto = (abs(accion)-2 );/// * numElementos[0];
                    int i;
                    for(i = 0; i < (lonReglas[absoluto]*2); i++){
                        p.pop();
                    }*/
///******************************************************************mover de lugar**********************************************
                    fila = p.top()->getEstado();
                    columna = idReglas[abs(accion)-2];
                    oldaccion = accion;
                    accion = matriz[fila][columna];

                    simbolo = noTerminales[abs(oldaccion)-2];
                    p.push(new NoTerminal(simbolo,nuevoNodo )); ///simb = string nombre de la regla
                    p.push(new Estado(accion));

                    fila = p.top()->getEstado();
                    columna = lexico.tipo;
                    accion = matriz[fila][columna];



              }else{
                cout << "Error en aceptacion!" << endl;
                    break;
              }
/*

                ///lexico impresion: ----------------------------------
                if(lexico.simbolo.compare("$")==0){
                    cout <<endl<<endl<<lexico.simbolo << "\t\t" <<lexico.tipoAcad(lexico.tipo)<<endl<<endl<<"Fin de ejecucion!"<<endl<<endl;
                     break;
                }
                else {
                    cout <<  lexico.simbolo << "\t\t" << lexico.tipoAcad(lexico.tipo)<< "\t\t" << lexico.tipo<< endl;
                }
*/
    }
}


#endif // SINTACTICO_H_INCLUDED
