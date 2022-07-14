#ifndef SEMANTICO_H_INCLUDED
#define SEMANTICO_H_INCLUDED

#include "Pila.h"
#include "tablaSimbolos.h"
#include "simbolo.h"
#include <fstream>
#include <sstream>
using namespace std;

TablaSimbolos *tablaSim = new TablaSimbolos();
TablaErrores *tablaError= new TablaErrores();
char vectParametros[20];
char vectArgumentos[20];
int contParam;
int contArgs;
//int contArgumentos;
int labelCounter = 0;
class Nodo{
	protected:
		char tipoCh;
		string ambito;
	public:
		virtual void muestra(int tabs){}
		virtual char validaTipo(string){}
		virtual char validaTipo(string,string){}
		virtual void validaTipo(char,string){}
		virtual string generarCodigo(){}

		void tabsName(int tabs, string name){
			for (int i = 0; i < tabs-1; i++){
				cout << "   " ;
			}
			cout << name << endl;
		}

		void tabsTerminal(int tabs, string terminal){
			for (int i = 0; i < tabs; i++){
				cout << "   " ;
			}
			cout << terminal << endl;
		}
				string getJumpRelIgu(string op){
			string jump;
			if(op == ">")
	            jump = "jg";
	        else if(op == "<")
	            jump = "jl";
	        else if(op ==">=")
	            jump = "jge";
	        else if(op == "<=")
	            jump = "jle";
	        else if(op == "==")
	            jump = "je";
	        else if(op == "!=")
	            jump = "jne";
    	    return jump;
		}
            string getLabelNumber(){
	        std::stringstream label;
	        label << labelCounter;
	        return label.str();
	    }
};

class nullNodo: public Nodo{
	protected:
		Nodo* nulo;
	public:
		nullNodo(){
			nulo = NULL;
		}

		void muestra(int tabs){
			tabsName(tabs,"Null");
		}

		char validaTipo(string ambito){
			cout << "" << endl;
		}
		string generarCodigo(){
			return "";
		}
};


//R1 <programa> ::= <Definiciones>
class Programa_R1: public Nodo{
	protected:
		Nodo* definiciones;
	public:
		Programa_R1(Pila &p){
			ambito = "global";
			p.pop(); // estado
			definiciones = ((NoTerminal*)p.top())->getNodo(); // definiciones
			delete(p.pop());
		}

		void muestra(int tabs){
			tabsName(tabs,"<Programa_R1>");
			definiciones->muestra(tabs+1);
			tabsName(tabs,"</Programa_R1>");
			validaTipo(ambito);		//// iniciando valida tipo
			tablaSim->muestra();
			tablaError->muestra();
		}

		char validaTipo(string ambito){
			definiciones->validaTipo(ambito);
		}
		string generarCodigo(){
			string topEnsamblador;
			topEnsamblador = ".MODEL SMALL\n\n";
    		topEnsamblador += ".STACK\n";
        //topEnsamblador += "includelib \\masm32\\lib\\masm32.lib\nincludelib \\masm32\\lib\\kernel32.lib\n\n";
		    topEnsamblador += ".DATA\n";

		    for (int i = 0; i < tablaSim->getTablaSize(); i++){
		    	if(tablaSim->buscarSimbolo(tablaSim->dameVar(i),"global")->getFuncion()){
		    		continue;
		    	}
		    	else{
		    		topEnsamblador += tablaSim->dameVar(i) + " DB 0\n" ;

		    	}
		    }

		    topEnsamblador += "\n.CODE\n";

			topEnsamblador += definiciones->generarCodigo();
			cout<<"****************************GENERACION DE CODIGO***********************************"<<endl;

			cout << topEnsamblador  << endl;

			cout<<"***********************************************************************************"<<endl;

		    ofstream texto("ensamblador.asm");

		    if(texto.is_open())
                texto << topEnsamblador ;
		    texto.close();

		    return "";
		}
};


//R3 <Definiciones> ::= <Definicion> <Definiciones>
class Definiciones_R3: public Nodo{
	protected:
		Nodo* definicion;
		Nodo* definiciones;
	public:
		Definiciones_R3(Pila &p){
			p.pop(); // estado
			definicion = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
			p.pop(); // estado
			definiciones = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
		}

		void muestra(int tabs){
			tabsName(tabs,"<Definiciones_R3>");
			definicion->muestra(tabs+1);
			definiciones->muestra(tabs+1);
			tabsName(tabs,"</Definiciones_R3>");
		}

		char validaTipo(string ambito){
			definiciones->validaTipo(ambito);
			definicion->validaTipo(ambito);
		}

		string generarCodigo(){
			string codigo;
			codigo = definiciones->generarCodigo();
			codigo += definicion->generarCodigo();
			return codigo;
		}

};

//R4 <Definicion> ::= <DefVar>
class Definicion_R4: public Nodo{
	protected:
		Nodo* defVar;
	public:
		Definicion_R4(Pila &p){
			p.pop(); // estado
			defVar = ((NoTerminal*)p.top())->getNodo(); // defVar
			delete(p.pop());
		}

		void muestra(int tabs){
			tabsName(tabs,"<Definicion_R4>");
			defVar->muestra(tabs+1);
			tabsName(tabs,"</Definicion_R4>");
		}

		char validaTipo(string ambito){
			defVar->validaTipo(ambito);
		}

		string generarCodigo(){
			return defVar->generarCodigo();
		}
};

//R5 <Definicion> ::= <DefFunc>
class Definicion_R5: public Nodo{
	protected:
		Nodo* defFunc;
	public:
		Definicion_R5(Pila &p){
			p.pop();//estado
			defFunc = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
		}

		void muestra(int tabs){
			tabsName(tabs,"<Definicion_R5>");
			defFunc->muestra(tabs+1);
			tabsName(tabs,"</Definicion_R5>");
		}

		char validaTipo(string ambito){
			defFunc->validaTipo(ambito);
		}

		string generarCodigo(){
			return defFunc->generarCodigo();
		}
};

//R6 <DefVar> ::= tipo identificador <ListaVar> ;
class DefVar_R6: public Nodo{
	protected:
		string id;
		string tipo;
		Nodo* listaVar;
	public:
		DefVar_R6(Pila& p){
			p.pop(); // estado
			p.pop(); // punto coma
			p.pop(); // estado
			listaVar = (p.top())->getNodo(); // listavar
			delete(p.pop());
			p.pop(); // estado
			id = p.top()->getTerminal(); // id
			delete(p.pop());
			p.pop(); // estado
			tipo = p.top()->getTerminal(); // tipo
			delete(p.pop());
		}

		void muestra(int tabs){
			tabsName(tabs,"<DefVar_R6>");
			tabsTerminal(tabs,tipo);
			tabsTerminal(tabs,id);
			listaVar->muestra(tabs+1);
			tabsName(tabs,"</DefVar_R6>");
		}

		char validaTipo(string ambito){
			if(!tablaSim->buscarTablaSim(id,ambito)){
				tipoCh = tipo[0];
				Simbolo *s = new Simbolo(tipoCh,id,ambito,false);
				tablaSim->insert(s);
			}
			else{
				tablaError->insert(1,id);
			}
			listaVar->validaTipo(tipoCh,ambito);
			return ' ';
		}

		string generarCodigo(){
			return "";
			// retorno nada por qeu no es neceario declarar el tipo en ensamblador

		}
};


//R8 <ListaVar> ::= , identificador <ListaVar>
class ListaVar_R8: public Nodo{
	protected:
		Nodo* listaVar;
		string id;
	public:
		ListaVar_R8(Pila &p){
		    cout<<"ENTRE A ListaVar_8"<<endl;
			p.pop(); //estado
			listaVar =  ((NoTerminal*)p.top())->getNodo(); //listavar
			p.pop();
			p.pop();// estado
			id = p.top()->getTerminal(); // id
			cout<<"ID="<<id<<endl;
			p.pop();
			p.pop(); //estado
			p.pop(); //coma
			cout<<"Este es el tope:"<<p.top()->getEstado();
		}

		void muestra(int tabs){
			tabsName(tabs,"<ListaVar_R8>");
			tabsTerminal(tabs,id);
			listaVar->muestra(tabs+1);
			tabsName(tabs,"</ListaVar_R8>");
		}

		void validaTipo(char tipoCh,string ambito){
			//cout << "listaVar: R8" << endl;
			if(!tablaSim->buscarTablaSim(id)){
				Simbolo *s = new Simbolo(tipoCh,id,ambito,false);
				tablaSim->insert(s);
				//cout << "Se inserto a la tabla: " << id << endl;
			}
			else{
				tablaError->insert(1,id);
			}
			listaVar->validaTipo(tipoCh,ambito);
		}

		string generarCodigo(){
			return "";
		}
};

//R9 <DefFunc> ::= tipo identificador ( <Parametros> ) <BloqFunc>
class DefFunc_R9: public Nodo{
	protected:
		Nodo* parametros;
		Nodo* bloqFunc;
		string tipo;
		string id;
	public:
		DefFunc_R9(Pila &p){
			p.pop(); // estado
			bloqFunc = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
			p.pop();//estado
			p.pop(); // )
			p.pop(); // estado
			parametros = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
			p.pop(); // estado
			p.pop();// (
			p.pop(); // estado
			id = p.top()->getTerminal();
			delete(p.pop());
			p.pop();// estado
			tipo = p.top()->getTerminal();
			delete(p.pop());
		}

		void muestra(int tabs){
			tabsName(tabs,"<DefFunc_R9>");
			tabsTerminal(tabs,tipo);
			tabsTerminal(tabs,id);
			parametros->muestra(tabs+1);
			bloqFunc->muestra(tabs+1);
			tabsName(tabs,"</DefFunc_R9>");
		}

		char validaTipo(string ambito){
			//cout << "defFunc: R9" << endl;
			if(!tablaSim->buscarTablaSim(id)){
				for (int i = 0; i < 20; i++){
					vectParametros[i]=0;
				}
				contParam=0;
				tipoCh = tipo[0];
				//cout << "Se inserto a la tabla: " << id << endl;
			}
			else{
				tablaError->insert(1,id);
			}
			parametros->validaTipo(id);
			Simbolo *s = new Simbolo(tipoCh,id,ambito,vectParametros,true);
			tablaSim->insert(s);
			bloqFunc->validaTipo(id); /// en una funcion el mismo id sera su ambito
		}

		string generarCodigo(){
			string codigo;
			codigo = id+":\n";
			codigo += parametros->generarCodigo();
			codigo += bloqFunc->generarCodigo();
			codigo += "print str$(eax)\nprint chr$(10)\nexit\n";
			codigo += "end " + id + "\n";
			return codigo;
		}
};

//R11 <Parametros> ::= tipo identificador <ListaParam>
class Parametros_R11: public Nodo{
	protected:
		Nodo* listaParam;
		string id;
		string tipo;
	public:
		Parametros_R11(Pila &p){
			p.pop(); // estado
			listaParam = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
			p.pop(); // estado
			id = p.top()->getTerminal();
			delete(p.pop());
			p.pop(); // estado
			tipo = p.top()->getTerminal();
			delete(p.pop());
		}

		void muestra(int tabs){
			tabsName(tabs,"<Parametros_R11>");
			tabsTerminal(tabs,tipo);
			tabsTerminal(tabs,id);
			listaParam->muestra(tabs+1);
			tabsName(tabs,"</Parametros_R11>");
		}

		char validaTipo(string ambito){
			//cout << "parametros: R11"<<endl;
			if(!tablaSim->buscarTablaSim(id,ambito)){
				tipoCh=tipo[0];
				Simbolo *s = new Simbolo(tipoCh,id,ambito,false);
				tablaSim->insert(s);
				//cout << "Se inserto a la tabla: " << id << endl;
				vectParametros[contParam++]=tipoCh;
				//cout << "CONTADOR PARAMETROS uno: " << vectParametros << endl;
			}
			else{
				tablaError->insert(1,id);
			}
			listaParam->validaTipo(tipoCh,ambito);
		}


		string generarCodigo(){
			return listaParam->generarCodigo();
		}
};

//R13 <ListaParam> ::= , tipo identificador <ListaParam>
class ListaParam_R13: public Nodo{
	protected:
		Nodo* listaParam;
		string id;
		string tipo;
	public:
		ListaParam_R13(Pila &p){
			p.pop(); // estado
			listaParam = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
			p.pop(); // estado
			id = p.top()->getTerminal();
			delete(p.pop());
			p.pop(); // estado
			tipo = p.top()->getTerminal();
			delete(p.pop());
			p.pop(); // estado
			p.pop(); // coma
		}

		void muestra(int tabs){
			tabsName(tabs,"<ListaParam_R13>");
			tabsTerminal(tabs,tipo);
			tabsTerminal(tabs,id);
			listaParam->muestra(tabs+1);
			tabsName(tabs,"</ListaParam_R13>");
		}

		void validaTipo(char tipoCh, string ambito){
			//cout << "listaParam: R13" << endl;
			if(!tablaSim->buscarTablaSim(id)){
				tipoCh = tipo[0];
				vectParametros[contParam++]=tipoCh;
				Simbolo *s = new Simbolo(tipoCh,id,ambito,false);
				tablaSim->insert(s);
				//cout << "Se inserto a la tabla: " << id << endl;
			}
			else{
				tablaError->insert(1,id);
			}
			listaParam->validaTipo(tipoCh, ambito);

		}

		string generarCodigo(){
			return "";
		}
};

//R14 <BloqFunc> ::= { <DefLocales> }
class BloqFunc_R14: public Nodo{
	protected:
		Nodo* defLocales;
	public:
		BloqFunc_R14(Pila &p){
			p.pop(); //estado
			p.pop(); // }
			p.pop(); // estado
			defLocales = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
			p.pop(); // estado
			p.pop();// {
		}

		void muestra(int tabs){
			tabsName(tabs,"<BloqFunc_R14>");
			defLocales->muestra(tabs+1);
			tabsName(tabs,"</BloqFunc_R14>");
		}

		char validaTipo(string ambito){//necesario
			defLocales->validaTipo(ambito);
		}

		string generarCodigo(){
			return defLocales->generarCodigo();
		}
};

//R16 <DefLocales> ::= <DefLocal> <DefLocales>
class DefLocales_R16: public Nodo{
	protected:
		Nodo* defLocal;
		Nodo* defLocales;
	public:
		DefLocales_R16(Pila &p){
			p.pop();// estado
			defLocales = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
			p.pop(); // estado
			defLocal = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
		}

		void muestra(int tabs){
			tabsName(tabs,"<DefLocales_R16>");
			defLocal->muestra(tabs+1);
			defLocales->muestra(tabs+1);
			tabsName(tabs,"</DefLocales_R16>");
		}

		char validaTipo(string ambito){//necesario
			defLocal->validaTipo(ambito);
			defLocales->validaTipo(ambito);
		}

		string generarCodigo(){
			string codigo;
			codigo = defLocal->generarCodigo();
			codigo += defLocales->generarCodigo();
			return codigo;
		}
};

//R17 <DefLocal> ::= <DefVar>
class DefLocal_R17: public Nodo{
	protected:
		Nodo* defVar;
	public:
		DefLocal_R17(Pila &p){
			p.pop(); // estado
			defVar = ((NoTerminal*)p.top())->getNodo(); // defVar
			delete(p.pop());
		}

		void muestra(int tabs){
			tabsName(tabs,"<DefLocal_R17>");
			defVar->muestra(tabs+1);
			tabsName(tabs,"</DefLocal_R17>");
		}

		char validaTipo(string ambito){
			defVar->validaTipo(ambito);
		}

		string generarCodigo(){
			return defVar->generarCodigo();
		}
};

//R18 <DefLocal> ::= <Sentencia>
class DefLocal_R18: public Nodo{
	protected:
		Nodo* sentencia;
	public:
		DefLocal_R18(Pila &p){
			p.pop();//estado
			sentencia = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
		}

		void muestra(int tabs){
			tabsName(tabs,"<DefLocal_R18>");
			sentencia->muestra(tabs+1);
			tabsName(tabs,"</DefLocal_R18>");
		}

		char validaTipo(string ambito){
			sentencia->validaTipo(ambito);
		}

		string generarCodigo(){
			return sentencia->generarCodigo();
		}
};

//R20 <Sentencias> ::= <Sentencia> <Sentencias>
class Sentencias_R20: public Nodo{
	protected:
		Nodo* sentencias;
		Nodo* sentencia;
	public:
		Sentencias_R20(Pila &p){
			p.pop();//estado
			sentencias = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
			p.pop(); //estado
			sentencia = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
		}

		void muestra(int tabs){
			tabsName(tabs,"<Sentencias_R20>");
			sentencia->muestra(tabs+1);
			sentencias->muestra(tabs+1);
			tabsName(tabs,"</Sentencias_R20>");
		}

		char validaTipo(string ambito){
			sentencia->validaTipo(ambito);
			sentencias->validaTipo(ambito);
		}

		string generarCodigo(){
			string codigo;
			codigo = sentencia->generarCodigo();
			codigo += sentencias->generarCodigo();
			return codigo;
		}
};

//R21 <Sentencia> ::= identificador = <Expresion> ;
class Sentencia_R21: public Nodo{
	protected:
		Nodo* expresion;
		string id;
		string igual;
	public:
		Sentencia_R21(Pila &p){
			p.pop();//estado
			p.pop();// ;
			p.pop(); // estado
			expresion = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
			p.pop(); //estado
			igual = p.top()->getTerminal();
			delete(p.pop());
			p.pop(); // estado
			id = p.top()->getTerminal();
			delete(p.pop());
		}

		void muestra(int tabs){
			tabsName(tabs,"<Sentencia_R21>");
			tabsTerminal(tabs,id);
			tabsTerminal(tabs,igual);
			expresion->muestra(tabs+1);
			tabsName(tabs,"</Sentencia_R21>");
		}

		char validaTipo(string ambito){
			char tipoexp = expresion->validaTipo(ambito);
			///cout << "\t\tTIPOS:  " << tipoexp << " vs " << tablaSim->dameTipo(id,ambito) << endl;
			if(tablaSim->buscarTablaSim(id) == false){// si no esta en la tabla
				tablaError->insert(2,id); // Error: variable NO declarada
			}
			else if(tipoexp == tablaSim->dameTipo(id,ambito)){
				///cout << "LA SENTENCIA 21 ES DEL MISMO TIPO " << tipoexp << "\n\n" << endl;
				return tipoexp;
			}
			else if((tablaSim->dameTipo(id,"global") !='@') and (tablaSim->dameTipo(id,"global")==tipoexp) ){
				//cout << "tipoexp: " << tipoexp << " VS " << "tabla simbolos global y buscando: " << id <<  tablaSim->dameTipo(id,"global") << endl;
				///cout << "LA SENTENCIA 21 ES DEL MISMO TIPO  SE USA UNA GLOBAL " << tipoexp << "\n\n" << endl;
				return tipoexp;
			}
			else{
				tablaError->insert(4,id);
			}
		}

		string generarCodigo(){
			string codigo;
			codigo = expresion->generarCodigo();
			codigo += "pop eax\nmov " + id + ", eax\n";
        	return codigo;
		}
};

//R22 <Sentencia> ::= if ( <Expresion> ) <SentenciaBloque> <Otro>
class Sentencia_R22: public Nodo{
	protected:
		Nodo* otro;
		Nodo* sentenciaBloque;
		Nodo* expresion;
		string ifS;
	public:
		Sentencia_R22(Pila &p){
			p.pop();//estado
			otro = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
			p.pop();//estado
			sentenciaBloque = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
			p.pop(); //estado
			p.pop();// )
			p.pop();//estado
			expresion = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
			p.pop();//estado
			p.pop();//(
			p.pop();//estado
			ifS = p.top()->getTerminal();
			delete(p.pop());
		}

		void muestra(int tabs){
			tabsName(tabs,"<Sentencia_R22>");
			tabsTerminal(tabs,ifS);
			expresion->muestra(tabs+1);
			sentenciaBloque->muestra(tabs+1);
			otro->muestra(tabs+1);
			tabsName(tabs,"</Sentencia_R22>");
		}

		char validaTipo(string ambito){
			expresion->validaTipo(ambito);
			sentenciaBloque->validaTipo(ambito);
			otro->validaTipo(ambito);
		}

		string generarCodigo(){

			labelCounter++;
			string codigo, labelI; // se puede implementar

			codigo = expresion->generarCodigo();
			codigo += "pop eax\ncmp eax,0\n";
        	codigo += "je If_" + getLabelNumber() + "\n";

        	labelI = "If_" + getLabelNumber();

			codigo += sentenciaBloque->generarCodigo();
			codigo += labelI + ":\n";
			codigo += otro->generarCodigo();
			return codigo;
		}
};

//R23 <Sentencia> ::= while ( <Expresion> ) <Bloque>
class Sentencia_R23: public Nodo{
	protected:
		Nodo* bloque;
		Nodo* expresion;
		string whileS;
	public:
		Sentencia_R23(Pila &p){
			p.pop();//estado
			bloque = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
			p.pop();//estado
			p.pop(); // )
			p.pop();//estado
			expresion = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
			p.pop();//estado
			p.pop();//(
			p.pop();//estado
			whileS = p.top()->getTerminal();
			delete(p.pop());
		}

		void muestra(int tabs){
			tabsName(tabs,"<Sentencia_R23>");
			tabsTerminal(tabs,whileS);
			expresion->muestra(tabs+1);
			bloque->muestra(tabs+1);
			tabsName(tabs,"</Sentencia_R23>");
		}

		char validaTipo(string ambito){
			expresion->validaTipo(ambito);
			bloque->validaTipo(ambito);
		}

		string generarCodigo(){
			return "";
		}
};

//R24 <Sentencia> ::= return <ValorRegresa> ;
class Sentencia_R24: public Nodo{
	protected:
		Nodo* valorRegresa;
		string returnS;
	public:
		Sentencia_R24(Pila &p){
			p.pop();//estado
			p.pop();//;
			p.pop();//estado
			valorRegresa = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
			p.pop();//estado
			returnS = p.top()->getTerminal();
			delete(p.pop());
		}

		void muestra(int tabs){
			tabsName(tabs,"<Sentencia_R24>");
			tabsTerminal(tabs,returnS);
			valorRegresa->muestra(tabs+1);
			tabsName(tabs,"</Sentencia_R24>");
		}

		char validaTipo(string ambito){
			char valReg = valorRegresa->validaTipo(ambito);


			if(valReg != tablaSim->dameTipo(ambito,"global")){
				//cout << "El RETURN NO es del mismo tipo de la FUNCION !!!!" << endl;
				tablaError->insert(6,"");
			}
		}

		string generarCodigo(){
			return "ret\n";
		}
};

//R25 <Sentencia> ::= <LlamadaFunc> ;
class Sentencia_R25: public Nodo{
	protected:
		Nodo* llamadaFunc;
	public:
		Sentencia_R25(Pila &p){
			p.pop();//estado
			p.pop();//;
			p.pop();//estado
			llamadaFunc = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
		}

		void muestra(int tabs){
			tabsName(tabs,"<Sentencia_R25>");
			llamadaFunc->muestra(tabs+1);
			tabsName(tabs,"</Sentencia_R25>");
		}

		char validaTipo(string ambito){
			llamadaFunc->validaTipo(ambito);
		}

		string generarCodigo(){
			return llamadaFunc->generarCodigo();
		}
};

//R27 <Otro> ::= else <SentenciaBloque>
class Otro_R27: public Nodo{
	protected:
		Nodo* sentenciaBloque;
		string elseS;
	public:
		Otro_R27(Pila &p){
			p.pop();//estado
			sentenciaBloque = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
			p.pop();//estado
			elseS = p.top()->getTerminal();
			delete(p.pop());
		}

		void muestra(int tabs){
			tabsName(tabs,"<Otro_R27>");
			tabsTerminal(tabs,elseS);
			sentenciaBloque->muestra(tabs+1);
			tabsName(tabs,"</Otro_R27>");
		}

		char validaTipo(string ambito){
			sentenciaBloque->validaTipo(ambito);
		}

		string generarCodigo(){
			return sentenciaBloque->generarCodigo();
		}
};

//R28 <Bloque> ::= { <Sentencias> }
class Bloque_R28: public Nodo{
	protected:
		Nodo* sentencias;
	public:
		Bloque_R28(Pila &p){
			p.pop();//estado
			p.pop();//}
			p.pop();//estado
			sentencias = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
			p.pop();//estado
			p.pop();//{
		}

		void muestra(int tabs){
			tabsName(tabs,"<Bloque_R28>");
			sentencias->muestra(tabs+1);
			tabsName(tabs,"</Bloque_R28>");
		}

		char validaTipo(string ambito){
			return sentencias->validaTipo(ambito);
		}

		string generarCodigo(){
			return sentencias->generarCodigo();
		}
};

//R30 <ValorRegresa> ::= <Expresion>
class ValorRegresa_R30: public Nodo{
	protected:
		Nodo* expresion;
	public:
		ValorRegresa_R30(Pila &p){
			p.pop();//estado
			expresion = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
		}

		void muestra(int tabs){
			tabsName(tabs,"<ValorRegresa_R30>");
			expresion->muestra(tabs+1);
			tabsName(tabs,"</ValorRegresa_R30>");
		}

		char validaTipo(string ambito){
			return expresion->validaTipo(ambito);
		}

		string generarCodigo(){
			return expresion->generarCodigo();
		}
};

//R32 <Argumentos> ::= <Expresion> <ListaArgumentos>
class Argumentos_R32: public Nodo{
	protected:
		Nodo* listaArgumentos;
		Nodo* expresion;
	public:
		Argumentos_R32(Pila &p){
			p.pop();//estado
			listaArgumentos = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
			p.pop();//estado
			expresion = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
		}

		void muestra(int tabs){
			tabsName(tabs,"<Argumentos_R32>");
			expresion->muestra(tabs+1);
			listaArgumentos->muestra(tabs+1);
			tabsName(tabs,"</Argumentos_R32>");
		}

		char validaTipo(string ambito){
			//contArgumentos++;
			char tipoExpresion = expresion->validaTipo(ambito);
			vectArgumentos[contArgs++]= tipoExpresion;
			listaArgumentos->validaTipo(ambito);
		}

		string generarCodigo(){
			string codigo;
			codigo = expresion->generarCodigo();
			codigo += listaArgumentos->generarCodigo();
			return codigo;
		}
};

//R34 <ListaArgumentos> ::= , <Expresion> <ListaArgumentos>
class ListaArgumentos_R34: public Nodo{
	protected:
		Nodo* listaArgumentos;
		Nodo* expresion;
	public:
		ListaArgumentos_R34(Pila &p){
			p.pop();// estado
			listaArgumentos = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
			p.pop();//estado
			expresion = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
			p.pop();//estado
			p.pop();//,
		}

		void muestra(int tabs){
			tabsName(tabs,"<ListaArgumentos_R34>");
			expresion->muestra(tabs+1);
			listaArgumentos->muestra(tabs+1);
			tabsName(tabs,"</ListaArgumentos_R34>");
		}

		char validaTipo(string ambito){
			//contArgumentos++;
			char tipoExpresion= expresion->validaTipo(ambito);
			vectArgumentos[contArgs++]= tipoExpresion;
			listaArgumentos->validaTipo(ambito);
		}

		string generarCodigo(){
			string codigo;
			codigo = expresion->generarCodigo();
			codigo += listaArgumentos->generarCodigo();
			return codigo;
		}
};

//R35 <Termino> ::= <LlamadaFunc>
class Termino_R35: public Nodo{
	protected:
		Nodo* llamadaFunc;
	public:
		Termino_R35(Pila &p){
			p.pop(); //estado
			llamadaFunc = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
		}
		void muestra(int tabs){
			tabsName(tabs,"<Termino_R35>");
			llamadaFunc->muestra(tabs+1);
			tabsName(tabs,"</Termino_R35>");
		}

		char validaTipo(string ambito){
			return llamadaFunc->validaTipo(ambito);
		}

		string generarCodigo(){
			return llamadaFunc->generarCodigo();
		}
};


//R36 <Termino> ::= identificador
class Termino_R36: public Nodo{
	protected:
		string id;
	public:
		Termino_R36(Pila &p){
			p.pop(); //estado
			id = p.top()->getTerminal();
			delete(p.pop());
		}

		void muestra(int tabs){
			tabsName(tabs, "<Termino_R36>");
			tabsTerminal(tabs, id);
			tabsName(tabs, "</Termino_R36>");
		}

		char validaTipo(string ambito){
			//cout << "\n\nbusco a: " << id << " con ambito: " << ambito << endl;
			if(!tablaSim->buscarTablaSim(id,ambito)){
				if(tablaSim->buscarTablaSim(id,"global")){
					///cout << "tipo de Termino_R36:  "<< id << " "  << tablaSim->dameTipo(id,"global")<< endl;
					return tablaSim->dameTipo(id,"global");
				}
				else{
					tablaError->insert(2,id);
				}
			}
			// si esta en la tabla y con ambito local
			///cout << "tipo de Termino_R36:  "<< id << " "  << tablaSim->dameTipo(id,ambito)<< endl;
			return tablaSim->dameTipo(id,ambito);
		}

		string generarCodigo(){
			return "push "+id+"\n";
		}
};

//R37 <Termino> ::= entero
class Termino_R37: public Nodo{
	protected:
		string entero;
	public:
		Termino_R37(Pila &p){
			p.pop();//estado
			entero = p.top()->getTerminal();
			delete(p.pop());
		}

		void muestra(int tabs){
			tabsName(tabs,"<Termino_R37>");
			tabsTerminal(tabs,entero);
			tabsName(tabs,"</Termino_R37>");
		}

		char validaTipo(string ambito){
			if(!tablaSim->buscarTablaSim(entero,ambito)){

				cout << "tipo de Termino_R37:  "<< entero << " "  << 'i' << endl;
				return 'i';
			}
		}

		string generarCodigo(){
			return "push "+ entero+ "\n";
		}
};

//R38 <Termino> ::= real
class Termino_R38: public Nodo{
	protected:
		string real;
	public:
		Termino_R38(Pila &p){
			p.pop();//estado
			real = p.top()->getTerminal();
			delete(p.pop());
		}

		void muestra(int tabs){
			tabsName(tabs,"<Termino_R37>");
			tabsTerminal(tabs,real);
			tabsName(tabs,"</Termino_R37>");
		}

		char validaTipo(string ambito){
			if(!tablaSim->buscarTablaSim(real,ambito)){

				cout << "tipo de Termino_R38:  "<< real << " "  << 'f' << endl;
				return 'f';
			}
		}

		string generarCodigo(){
			return "push "+ real+ "\n";
		}
};

//R39 <Termino> ::= cadena
class Termino_R39: public Nodo{
	protected:
		string cadena;
	public:
		Termino_R39(Pila &p){
			p.pop();//estado
			cadena = p.top()->getTerminal();
			delete(p.pop());
		}

		void muestra(int tabs){
			tabsName(tabs,"<Termino_R39>");
			tabsTerminal(tabs,cadena);
			tabsName(tabs,"</Termino_R39>");
		}

		char validaTipo(string ambito){
			if(!tablaSim->buscarTablaSim(cadena,ambito)){

				cout << "tipo de Termino_R39:  "<< cadena << " "  << 's' << endl;
				return 's';
			}
		}


		string generarCodigo(){
			return "push"+ cadena + "\n";
		}
};

//R40 <LlamadaFunc> ::= identificador ( <Argumentos> )
class LlamadaFunc_R40: public Nodo{
	protected:
		Nodo* argumentos;
		string id;
	public:
		LlamadaFunc_R40(Pila &p){
			p.pop();//estado
			p.pop();//)
			p.pop();//estado
			argumentos = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
			p.pop();//estado
			p.pop();//(
			p.pop();//estado
			id = p.top()->getTerminal();
			delete(p.pop());
		}

		void muestra(int tabs){
			tabsName(tabs,"<LlamadaFunc_R40>");
			tabsTerminal(tabs,id);
			argumentos->muestra(tabs+1);
			tabsName(tabs,"</LlamadaFunc_R40>");
		}

		char validaTipo(string ambito){

			for (int i = 0; i < 20; i++){
					vectArgumentos[i]=0;
				}
				contArgs=0;

			if(tablaSim->buscarTablaSim(id,"global")){ // ya que todas las fun estan definidas en global
				//cout << "tipo de LlamadaFunc_R40 :  "<< id << " "  << tablaSim->dameTipo(id,ambito)<< endl;
				//cout << "\n\n ENTRE A aqui con ambito: "<< ambito << endl << endl << endl;
				argumentos->validaTipo(ambito);
				//checando cantidad de argumentos
				int cantidadFinalParam = tablaSim->buscarSimbolo(id,ambito)->getNumParam();
				if(cantidadFinalParam != contArgs){
					//cout << "!!!!!!!!!!!!!!!!!!!!!!! " <<  cantidadFinalParam << " VS " << contArgumentos << endl;
					tablaError->insert(7,id);
				}
				else {
					//checando que cada parametro sea del mismo tipo que el argumento
					for (int i = 0; i < cantidadFinalParam; i++){
						if(tablaSim->buscarSimbolo(id,ambito)->getVectorParam(i) !=vectArgumentos[i]){
							tablaError->insert(8,id);
						}
					}

				}
				return tablaSim->dameTipo(id,"global");
			}
			else{
				tablaError->insert(5,id);
			}
		}

		string generarCodigo(){
			return "";
		}
};

//R41 <SentenciaBloque> ::= <Sentencia>
class SentenciaBloque_R41: public Nodo{
	protected:
		Nodo* sentencia;
	public:
		SentenciaBloque_R41(Pila &p){
			p.pop();//estado
			sentencia = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
		}

		void muestra(int tabs){
			tabsName(tabs,"<SentenciaBloque_R41>");
			sentencia->muestra(tabs+1);
			tabsName(tabs,"</SentenciaBloque_R41>");
		}

		char validaTipo(string ambito){
			return sentencia->validaTipo(ambito);
		}

		string generarCodigo(){
			return sentencia->generarCodigo();
		}
};

//R42 <SentenciaBloque> ::= <Bloque>
class SentenciaBloque_R42: public Nodo{
	protected:
		Nodo* bloque;
	public:
		SentenciaBloque_R42(Pila &p){
			p.pop();//estado
			bloque = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
		}

		void muestra(int tabs){
			tabsName(tabs,"<SentenciaBloque_R42>");
			bloque->muestra(tabs+1);
			tabsName(tabs,"</SentenciaBloque_R42>");
		}

		char validaTipo(string ambito){
			return bloque->validaTipo(ambito);
		}

		string generarCodigo(){
			return bloque->generarCodigo();
		}
};

//R43 <Expresion> ::= ( <Expresion> )
class Expresion_R43: public Nodo{
	protected:
		Nodo* expresion;
	public:
		Expresion_R43(Pila &p){
			p.pop(); // estado
			p.pop(); // )
			p.pop(); // estado
			expresion = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
			p.pop(); //estado
			p.pop();//(
		}

		void muestra(int tabs){
			tabsName(tabs,"<Expresion_R43>");
			expresion->muestra(tabs+1);
			tabsName(tabs,"</Expresion_R43>");
		}

		char validaTipo(string ambito){
			return expresion->validaTipo(ambito);
		}

		string generarCodigo(){
			return expresion->generarCodigo();
		}
};

//R44 <Expresion> ::= opSuma <Expresion>
class Expresion_R44: public Nodo{
	protected:
		Nodo* expresion;
		string opSuma;
	public:
		Expresion_R44(Pila &p){
			p.pop(); // estado
			expresion = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
			p.pop(); //estado
			opSuma = p.top()->getTerminal();
			delete(p.pop());
		}

		void muestra(int tabs){
			tabsName(tabs,"<Expresion_R44>");
			tabsTerminal(tabs,opSuma);
			expresion->muestra(tabs+1);
			tabsName(tabs,"</Expresion_R44>");
		}

		char validaTipo(string ambito){
			return expresion->validaTipo(ambito);
		}

		string generarCodigo(){
			string codigo;
			codigo = expresion->generarCodigo();
	        if(opSuma == "-"){
	            codigo += "pop eax\n";
	            codigo += "neg eax\n";
	            codigo += "push eax\n";
	        }
	        return codigo;
		}
};

//R45 <Expresion> ::= opNot <Expresion>
class Expresion_R45: public Nodo{
	protected:
		Nodo* expresion;
		string opNot;
	public:
		Expresion_R45(Pila &p){
			p.pop(); // estado
			expresion = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
			p.pop(); //estado
			opNot = p.top()->getTerminal();
			delete(p.pop());
		}

		void muestra(int tabs){
			tabsName(tabs,"<Expresion_R45>");
			tabsTerminal(tabs,opNot);
			expresion->muestra(tabs+1);
			tabsName(tabs,"</Expresion_R45>");
		}

		char validaTipo(string ambito){
			return expresion->validaTipo(ambito);
		}

		string generarCodigo(){
			return expresion->generarCodigo();
		}
};

//R46 <Expresion> ::= <Expresion> opMul <Expresion>
class Expresion_R46: public Nodo{
	protected:
		Nodo* expresionDer;
		string opMul;
		Nodo* expresionIzq;
	public:
		Expresion_R46(Pila &p){
			p.pop(); // estado
			expresionDer = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
			p.pop(); //estado
			opMul = p.top()->getTerminal();
			delete(p.pop());
			p.pop(); // estado
			expresionIzq = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
		}

		void muestra(int tabs){
			tabsName(tabs,"<Expresion_R46>");
			expresionIzq->muestra(tabs+1);
			tabsTerminal(tabs,opMul);
			expresionDer->muestra(tabs+1);
			tabsName(tabs,"</Expresion_R46>");
		}
		char validaTipo(string ambito){
			char tipoizq = expresionIzq->validaTipo(ambito);
			char tipoder = expresionDer->validaTipo(ambito);

			if(tipoizq == tipoder){
				///cout << "EXPRESION 46 SON DEL MISMO TIPO \n" <<  endl;
				return tipoder;
			}
			else{
				tablaError->insert(3,"");
			}
		}

		string generarCodigo(){
			string codigo;
			codigo = expresionIzq->generarCodigo();
			codigo += expresionDer->generarCodigo();
			if(opMul == "*")
				codigo += "pop ebx\npop eax\nxor edx,edx\nimul ebx\npush eax\n";
			else
				codigo += "pop ebx\npop eax\nxor edx,edx\nidiv ebx\npush eax\n";
			return codigo;
		}
};

//R47 <Expresion> ::= <Expresion> opSuma <Expresion>
class Expresion_R47: public Nodo{
	protected:
		Nodo* expresionDer;
		string opSuma;
		Nodo* expresionIzq;
	public:
		Expresion_R47(Pila &p){
			p.pop(); // estado
			expresionDer = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
			p.pop(); //estado
			opSuma = p.top()->getTerminal();
			delete(p.pop());
			p.pop(); // estado
			expresionIzq = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
		}

		void muestra(int tabs){
			tabsName(tabs,"<Expresion_R47>");
			expresionIzq->muestra(tabs+1);
			tabsTerminal(tabs,opSuma);
			expresionDer->muestra(tabs+1);
			tabsName(tabs,"</Expresion_R47>");
		}

		char validaTipo(string ambito){
			char tipoizq = expresionIzq->validaTipo(ambito);
			char tipoder = expresionDer->validaTipo(ambito);

			if(tipoizq == tipoder){
				///cout << "EXPRESION 47 SON DEL MISMO TIPO \n" <<  endl;
				return tipoder;
			}
			else{
				//cout << "tipoizq vs tipoder = " << tipoizq <<" vs " << tipoder << endl;
				tablaError->insert(3,"");
			}
		}

		string generarCodigo(){
			string codigo;
			codigo = expresionIzq->generarCodigo();
			codigo += expresionDer->generarCodigo();
			if(opSuma == "+")
				codigo += "pop ebx\npop eax\nadd eax, ebx\npush eax\n";
			else
				codigo += "pop ebx\npop eax\nsub eax, ebx\npush eax\n";
			return codigo;
		}
};

//R48 <Expresion> ::= <Expresion> opRelac <Expresion>
class Expresion_R48: public Nodo{
	protected:
		Nodo* expresionDer;
		string opRelac;
		Nodo* expresionIzq;
	public:
		Expresion_R48(Pila &p){
			p.pop(); // estado
			expresionDer = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
			p.pop(); //estado
			opRelac = p.top()->getTerminal();
			delete(p.pop());
			p.pop(); // estado
			expresionIzq = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
		}

		void muestra(int tabs){
			tabsName(tabs,"<Expresion_R48>");
			expresionIzq->muestra(tabs+1);
			tabsTerminal(tabs,opRelac);
			expresionDer->muestra(tabs+1);
			tabsName(tabs,"</Expresion_R48>");
		}

		char validaTipo(string ambito){
			char tipoizq = expresionIzq->validaTipo(ambito);
			char tipoder = expresionDer->validaTipo(ambito);

			if(tipoizq == tipoder){
				///cout << "EXPRESION 48 SON DEL MISMO TIPO \n" <<  endl;
				return tipoder;
			}
			else{
				tablaError->insert(3,"");
			}
		}

		string generarCodigo(){
			string codigo;
			labelCounter++;

			codigo = expresionIzq->generarCodigo();
			codigo += expresionDer->generarCodigo();
			codigo += "pop ebx\npop eax\n";
       	 	codigo += "cmp eax, ebx\n";
       	 	codigo += getJumpRelIgu(opRelac) + " True_" + getLabelNumber() + "\n";
       	 	codigo += "push 0\njmp End_" + getLabelNumber() + "\n";
	        codigo += "True_"+ getLabelNumber() + ":\n";
	        codigo += "push 1\n";
	        codigo += "End_"+ getLabelNumber() + ":";

        	return codigo;
		}
};

//R49 <Expresion> ::= <Expresion> opIgualdad <Expresion>
class Expresion_R49: public Nodo{
	protected:
		Nodo* expresionDer;
		string opIgualdad;
		Nodo* expresionIzq;
	public:
		Expresion_R49(Pila &p){
			p.pop(); // estado
			expresionDer = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
			p.pop(); //estado
			opIgualdad = p.top()->getTerminal();
			delete(p.pop());
			p.pop(); // estado
			expresionIzq = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
		}

		void muestra(int tabs){
			tabsName(tabs,"<Expresion_R49>");
			expresionIzq->muestra(tabs+1);
			tabsTerminal(tabs,opIgualdad);
			expresionDer->muestra(tabs+1);
			tabsName(tabs,"</Expresion_R49>");
		}

		char validaTipo(string ambito){
			char tipoizq = expresionIzq->validaTipo(ambito);
			char tipoder = expresionDer->validaTipo(ambito);

			if(tipoizq == tipoder){
				///cout << "EXPRESION 49 SON DEL MISMO TIPO \n" <<  endl;
				return tipoder;
			}
			else{
				tablaError->insert(3,"");
			}
		}

		string generarCodigo(){
			return ""; // se puede implementar
		}
};

//R50 <Expresion> ::= <Expresion> opAnd <Expresion>
class Expresion_R50: public Nodo{
	protected:
		Nodo* expresionDer;
		string opAnd;
		Nodo* expresionIzq;
	public:
		Expresion_R50(Pila &p){
			p.pop(); // estado
			expresionDer = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
			p.pop(); //estado
			opAnd = p.top()->getTerminal();
			delete(p.pop());
			p.pop(); // estado
			expresionIzq = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
		}

		void muestra(int tabs){
			tabsName(tabs,"<Expresion_R50>");
			expresionIzq->muestra(tabs+1);
			tabsTerminal(tabs,opAnd);
			expresionDer->muestra(tabs+1);
			tabsName(tabs,"</Expresion_R50>");
		}
		char validaTipo(string ambito){
			char tipoizq = expresionIzq->validaTipo(ambito);
			char tipoder = expresionDer->validaTipo(ambito);

			if(tipoizq == tipoder){
				///cout << "EXPRESION 50 SON DEL MISMO TIPO \n" <<  endl;
				return tipoder;
			}
			else{
				tablaError->insert(3,"");
			}
		}

		string generarCodigo(){
			return "";
		}
};

//R51 <Expresion> ::= <Expresion> opOr <Expresion>
class Expresion_R51: public Nodo{
	protected:
		Nodo* expresionDer;
		string opOr;
		Nodo* expresionIzq;
	public:
		Expresion_R51(Pila &p){
			p.pop(); // estado
			expresionDer = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
			p.pop(); //estado
			opOr = p.top()->getTerminal();
			delete(p.pop());
			p.pop(); // estado
			expresionIzq = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
		}

		void muestra(int tabs){
			tabsName(tabs,"<Expresion_R51>");
			expresionIzq->muestra(tabs+1);
			tabsTerminal(tabs,opOr);
			expresionDer->muestra(tabs+1);
			tabsName(tabs,"</Expresion_R51>");
		}
		char validaTipo(string ambito){
			char tipoizq = expresionIzq->validaTipo(ambito);
			char tipoder = expresionDer->validaTipo(ambito);

			if(tipoizq == tipoder){
				///cout << "EXPRESION 51 SON DEL MISMO TIPO \n" <<  endl;
				return tipoder;
			}
			else{
				tablaError->insert(3,"");
			}
		}

		string generarCodigo(){
			return "";
		}
};


//R52 <Expresion> ::= <Termino>
class Expresion_R52: public Nodo{
	protected:
		Nodo* termino;
	public:
		Expresion_R52(Pila &p){
			p.pop();// estado;
			termino = ((NoTerminal*)p.top())->getNodo();
			delete(p.pop());
		}

		void muestra(int tabs){
			tabsName(tabs,"<Expresion_R52>");
			termino->muestra(tabs+1);
			tabsName(tabs,"</Expresion_R52>");
		}

		char validaTipo(string ambito){
			return termino->validaTipo(ambito);
		}

		string generarCodigo(){
			return termino->generarCodigo();
		}
};

#endif // SEMANTICO_H_INCLUDED
