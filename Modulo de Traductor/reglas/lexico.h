#ifndef LEXICO_H_INCLUDED
#define LEXICO_H_INCLUDED
#include <iostream>
#include <string>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include <cstdlib>
#include <list>
#include <cstring>
#include <fstream>
using namespace std;

string lex="";
bool band = false;

class TipoSimbolo{ ///asignacion de valores a cada tipo
    public:
     static const int ERROR= -1;
     static const int IDENTIFICADOR= 0;
     static const int ENTERO= 1;
     static const int REAL= 2;
     static const int cadena=3;
     static const int RESERVADA_TIPO=4;
     static const int OPADIC= 5;
     static const int OPMULT= 6;
     static const int OPRELAC= 7;
     static const int OPOR= 8;
     static const int OPAND= 9;
     static const int OPNOT= 10;
     static const int OPIGUALDAD= 11;
     static const int PUNTOCOMA= 12;
     static const int COMA= 13;
     static const int PARENTESIS_ABRE= 14;
     static const int PARENTESIS_CIERRA= 15;
     static const int LLAVE_ABRE= 16;
     static const int LLAVE_CIERRA= 17;
     static const int ASIGNACION= 18;
     static const int IF= 19;
     static const int WHILE= 20;
     static const int RETURN= 21;
     static const int ELSE=22;
     static const int PESOS= 23;
};

class Lexico{
      private:
           string fuente;
           bool continua;
           char c;

           char Caracter();
           void sigEstado(int estado);
           void aceptacion(int estado);
           bool esLetra(char c);
           bool esDigito(char c);
           bool esEspacio(char c);
           void retroceso(); ///index decrementa

      public:
          int ind;
           string simbolo;
           int tipo;
           int estado;

           Lexico(string fuente){
                ind= 0;
                this->fuente= fuente;
                }
           Lexico(){
                ind = 0;
                }
           void entrada(string fuente);
           bool terminado(){
                return ind >= fuente.length();
                }
           string tipoAcad(int tipo);
           int sigSimbolo();

};
void Lexico::entrada(string archivo){
    ifstream file(archivo);
    char cadena[1000];

    if(!file.good()){
        cout << "Error al leer el archivo!!!" << endl;
    }else{
        file.getline((char*)&cadena,1000,file.eof());
        file.close();
    }

    ind= 0;
    this->fuente= (char*)cadena;
    cout<<"*************************Entrada.txt*******************************************"<<endl;
    cout << cadena << endl <<  endl;
    cout<<"*************************Entrada.txt*******************************************"<<endl;
}
char Lexico::Caracter(){
    if (terminado()) return '$';
    return fuente[ind++];
    }
void Lexico::retroceso(){
    if ( c!='$') ind--;
    continua= false;///sale del while y vuelve al main para imprimir y tomar el siguiente valor
    }
bool Lexico::esLetra(char c){
    return isalpha(c) || c=='_';
    }
bool Lexico::esDigito(char c){
    return isdigit(c);
    }
bool Lexico::esEspacio(char c){
    return c== ' ' || c== '\t';
    }

string Lexico::tipoAcad(int tipo){
    string cadena= "";

     switch (tipo){
       case TipoSimbolo::IDENTIFICADOR:
            cadena= "Identificador";
            break;
       case TipoSimbolo::ENTERO:
            cadena= "Entero";
            break;
       case TipoSimbolo::REAL:
            cadena= "Real";
            break;
       case TipoSimbolo::cadena:
            cadena="Cadena";
            break;
       case TipoSimbolo::RESERVADA_TIPO:
            cadena="Tipo";
            break;
       case TipoSimbolo::OPADIC:
            cadena= "OpAdicion";
            break;
       case TipoSimbolo::OPMULT:
            cadena= "OpMul";
            break;
       case TipoSimbolo::OPRELAC:
            cadena= "OpRelac";
            break;
       case TipoSimbolo::OPOR:
            cadena= "OpOR";
            break;
       case TipoSimbolo::OPAND:
            cadena= "OpAND";
            break;
       case TipoSimbolo::OPNOT:
            cadena= "OpNOT";
            break;
       case TipoSimbolo::OPIGUALDAD:
            cadena= "OpIGUALDAD";
            break;
       case TipoSimbolo::ASIGNACION:
            cadena= "Asignacion";
            break;
       case TipoSimbolo::PUNTOCOMA:
            cadena="PuntoYcomo";
            break;
       case TipoSimbolo::COMA:
            cadena="COMA";
            break;
       case TipoSimbolo::PARENTESIS_ABRE:
            cadena="Parentesis_abre";
            break;
       case TipoSimbolo::PARENTESIS_CIERRA:
            cadena="Parentesis_cierra";
            break;
       case TipoSimbolo::LLAVE_ABRE:
            cadena="Llave_abre";
            break;
       case TipoSimbolo::LLAVE_CIERRA:
            cadena="Llave_cierra";
            break;
       case TipoSimbolo::IF:
            cadena="IF-Sentence";
            break;
       case TipoSimbolo::WHILE:
            cadena="While-SENTENCE";
            break;
       case TipoSimbolo::RETURN:
            cadena="Return";
            break;
       case TipoSimbolo::ELSE:
            cadena="Else-SENTENCE";
            break;
       case TipoSimbolo::ERROR:
            cadena= "Error";
            break;
       case TipoSimbolo::PESOS:
            cadena= "PESOS";
            break;
     }
    return cadena;
}
void Lexico::aceptacion(int estado){
    sigEstado(estado);
    continua= false; ///sale del while y vuelve al main para imprimir y tomar el siguiente valor
    }
void Lexico::sigEstado(int estado){
   this->estado= estado;
   simbolo = lex;
   //cout<<"\nsimbolo: " << simbolo;
   if(estado==0 || estado == 1 || estado == 2 || estado == (-1) || estado == 7 || estado == 10 || estado == 18
      || estado == 23) ///iden - entero - real - <><=>=
        retroceso();
  }

///-----------------------------------------------------------------------------------

int Lexico::sigSimbolo(){

    estado=0;
    bool band_real=false;
    bool salir = false;
    continua= true;
    ///simbolo= "";
    //Inicio del Automata
    lex = "";
    while(continua){
        c = Caracter(); ///fuente[index 1]
        if ( c=='+' || c=='-'){
            lex+=c;
            aceptacion(5);
        }  ///1 opeAdicion
        if(  c=='*' || c=='/'){
            lex+=c;
            aceptacion(6); /// 6 ope mul
        }
        if(c=='_'){
           lex+=c;
           c=Caracter();
           aceptacion(-1);
        }
        if(c=='"'){
                lex+=c;
                c=Caracter();
                while(c!='"'){  //c= "
                    lex+=c;
                    c=Caracter();
                    if(c=='"') lex+=c; ///agregando el cierre "
                }
                aceptacion(3);
        break;
        }
        if(esLetra(c)){
                //lex+=c;
                //c=Caracter();
                while(esLetra(c) || esDigito(c)){
                    lex+=c;
                    c=Caracter();
                }
                if(lex=="if" || lex=="while"|| lex=="return" || lex=="else"){
                    if(lex=="if") aceptacion(19);
                    if(lex=="while") aceptacion(20);
                    if(lex=="return") aceptacion(21);
                    if(lex=="else") aceptacion(22);
                    }else if(lex=="int" || lex=="float" || lex=="void")
                        aceptacion(4); /// 4 TIPO
                        else aceptacion(0); ///0 IDENTIFICADOR
        break;
        }
        if(c=='.'){
            lex+=c;
            c=Caracter();
            while(esEspacio(c) != true){
                lex+=c;
                c=Caracter();
            }
            aceptacion(-1);
        break;
        }
        if(esDigito(c)){
                while(esDigito(c)){
                    lex+=c;
                    c=Caracter();
                }
                if(c != '.') aceptacion(1); ///es entero
                else if (c == '.' && esEspacio(c)==false){ ///es real
                    lex+=c;
                    c=Caracter();
                    if(esDigito(c) == false )
                        aceptacion(-1);
                    while(esDigito(c)){
                        lex+=c;
                        c=Caracter();
                        if(esDigito(c)== false)
                            aceptacion(2);
                    }
                }
                break;
        }
        if(c=='<'||c=='>'){
                lex+=c;
                c=Caracter();
                if(c == '='){
                    lex+=c;
                    c=Caracter();
                }
                aceptacion(7);
                break;
        }
        if(c=='|'){
                lex=lex+c;
                c=Caracter();
                if(c!='|') aceptacion(-1);
                else {
                        lex+=c;
                        aceptacion(8);
                }

                break;
        }
        if(c=='&'){
                lex=lex+c;
                c=Caracter();
                if(c!='&') aceptacion(-1);
                else {
                        lex+=c;
                        aceptacion(9);
                }

                break;
        }
        if(c=='!' || c=='='){
                lex=lex+c;
                c=Caracter();
                if(c == '='){
                 lex+=c;
                 aceptacion(11);///opeIgualdad
                 break;
                }
                if(lex=="!") aceptacion(10);
                if(lex=="=") aceptacion(18);
              break;
        }
        if(c==';'){
                lex+=c;
                aceptacion(12);
                break;
            }
        if(c==','){
            lex+=c;
            aceptacion(13);
            break;
        }
        if(c=='('){
           lex+=c;
            aceptacion(14);
            break;
           }
        if(c==')'){
            lex+=c;
            aceptacion(15);
            break;
        }
        if(c=='{'){
            lex+=c;
            aceptacion(16);
            break;
        }
        if(c=='}'){
                lex+=c;
            aceptacion(17);
            break;
        }else
              if ( c=='$' ){
                lex+=c;
                aceptacion(23);
                break;
              }
    }
    switch (estado){

          case 0: tipo=TipoSimbolo::IDENTIFICADOR;
          break;
          case 1: tipo=TipoSimbolo::ENTERO;
          break;
          case 2: tipo=TipoSimbolo::REAL;
          break;
          case 3: tipo=TipoSimbolo::cadena;
          break;
          case 4: tipo=TipoSimbolo::RESERVADA_TIPO;
          break;
          case 5: tipo= TipoSimbolo::OPADIC;
          break;
          case 6: tipo = TipoSimbolo::OPMULT;
          break;
          case 7: tipo= TipoSimbolo::OPRELAC;
          break;
          case 8: tipo= TipoSimbolo::OPOR;
          break;
          case 9: tipo= TipoSimbolo::OPAND;
          break;
          case 10: tipo= TipoSimbolo::OPNOT;
          break;
          case 11: tipo= TipoSimbolo::OPIGUALDAD;
          break;
          case 12: tipo= TipoSimbolo::PUNTOCOMA;
          break;
          case 13: tipo= TipoSimbolo::COMA;
          break;
          case 14: tipo= TipoSimbolo::PARENTESIS_ABRE;
          break;
          case 15: tipo= TipoSimbolo::PARENTESIS_CIERRA;
          break;
          case 16: tipo= TipoSimbolo::LLAVE_ABRE;
          break;
          case 17: tipo= TipoSimbolo::LLAVE_CIERRA;
          break;
          case 18: tipo= TipoSimbolo::ASIGNACION;
          break;
          case 19: tipo= TipoSimbolo::IF;
          break;
          case 20: tipo= TipoSimbolo::WHILE;
          break;
          case 21: tipo= TipoSimbolo::RETURN;
          break;
          case 22: tipo= TipoSimbolo::ELSE;
          break;
          case 23: tipo = TipoSimbolo::PESOS;
          break;
          default:
              tipo= TipoSimbolo::ERROR;
      }

    return 0;
}///cierre sigSimbolo

#endif // LEXICO_H_INCLUDED
