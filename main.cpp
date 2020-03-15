//
//  hospital.cpp
//  hospital
//
//  Created by Giselle Medina on 05/03/20.
//  Copyright © 2020 Giselle Medina. All rights reserved.
//

/*Programa que añade, busca, consulta y elimina a los pacientes de un hospital
*/

#include <iostream>
#include <stdlib.h>
using namespace std;

struct pacient{ //Struct "Paciente"
    int id; //Variable de tipo int para almacenar el número de seguro
    string name; //Variable de tipo string para almacenar el nombre del paciente
    int age; //Variable de tipo int para almacenar la edad
    string address; //Variable de tipo string para almacenar la dirección
    char sex; //Variable de tipo char para almacenar el sexo
    string sickness; //Variable de tipo string para almacenar la enfermedad
    int dayA; //Variable de tipo int para almacenar el día que ingresó el paciente
    int monthA; //Variable de tipo int para almacenar el mes que ingresó el paciente
    int yearA; //Variable de tipo int para almacenar el año que ingresó el paciente
    int daysP; //Variable de tipo int para almacenar los días que estuvo internado el paciente
    float eprice; //Variable de tipo float para almacenar el precio de la enfermedad
    pacient *siguiente; //Nueva Struct llamada "siguiente"
};

void altaPaciente(pacient *&, int,string,int,string,char,string,float,int,int,int); // Función para registrar a pacientes
void consultaPacientes(pacient *); // Función para consultar a todos los pacientes
void buscarPaciente(pacient *, int); // Función para  buscar a un paciente
void totalPagar(pacient *, int, int); //Función para calcular el total a pagar
void bajaPaciente(pacient *&, int); // Función para dar de baja a un paciente
void validarFecha(pacient *paciente, int d, int m, int a);

int main(int argc, const char * argv[]) { //Main
    pacient *paciente=NULL; //nueva variable de tipo "pacient"
    int opc,numid,edad,aux,di,mi,ai,diasTrans; //variables de tipo entero
    float precioEnf = 0.0; //variables de tipo real
    string nom,dir,enfermedad; //variables de tipo cadena de texto
    char r,s; //variables de tipo caracter
    cout << "¡Bienvenido!\n";
    do{ //inicio do-while 1
        cout<<"Menú Principal"<<endl;
        cout<<"1) Alta de Pacientes"<<endl;
        cout<<"2) Búsqueda de Paciente"<<endl;
        cout<<"3) Consulta de pacientes"<<endl;
        cout<<"4) Baja de Paciente"<<endl;
        cout<<"5) Salir"<<endl;
        cout<<"Elija una opción: "<<endl;
        cin>>opc;
        switch (opc) { //inicio switch 1
            case 1:
                do{ //inicio do-while 2
                    cout<<"Número de seguro social: "<<endl;
                    cin>>numid;
                    cout<<"Nombre: "<<endl;
                    cin>>nom;
                    cout<<"Edad: "<<endl;
                    cin>>edad;
                    cout<<"Municipio: "<<endl;
                    cin>>dir;
                    cout<<"Sexo: (M/F)"<<endl;
                    cin>>s;
                    cout<<"¿Qué enfermedad tiene?"<<endl;
                    cout<<"1) Neumonia"<<endl;
                    cout<<"2) Sinusitis"<<endl;
                    cout<<"3) Laberintitis"<<endl;
                    cout<<"4) Insuficiencia renal"<<endl;
                    cin>>aux;
                    switch (aux) { //inicio switch 2
                        case 1:
                            enfermedad="Neumonia";
                            precioEnf=350;
                            break;
                        case 2:
                            enfermedad="Sinusitis";
                            precioEnf=425.8;
                            break;
                        case 3:
                            enfermedad="Laberintitis";
                            precioEnf=796.4;
                            break;
                        case 4:
                            enfermedad="Insuficiencia renal";
                            precioEnf=1610.1;
                            break;
                        default:
                            cout<<"Opción incorrecta"<<endl;
                            break;
                            } //fin switch 2
                    cout<<"Ingrese fecha de ingreso\nDía: "<<endl;
                    cin>>di;
                    cout<<"Mes: "<<endl;
                    cin>>mi;
                    cout<<"Año: "<<endl;
                    cin>>ai;
                    altaPaciente(paciente, numid, nom, edad, dir, s, enfermedad, precioEnf,di, mi, ai);
                    validarFecha(paciente, di, mi, ai);
                    cout<<"¿Desea agregar a otro paciente? (s/n)"<<endl;
                    cin>>r;
                }
                while(r=='s'); //fin do-while 2
                break;
            case 2:
                if(paciente==NULL){ //inicio if
                    cout<<"No ha ingresado a ningún paciente"<<endl;
                }//fin if
                else{ //inicio else
                    cout<<"Ingrese el número de seguro del paciente: "<<endl;
                    cin>>numid;
                    buscarPaciente(paciente, numid);
                } //fin else
                break;
            case 3:
                if(paciente==NULL){ //inicio if
                    cout<<"No ha ingresado a ningún paciente"<<endl;
                }//fin if
                else{ //inicio else
                    consultaPacientes(paciente);
                           } //fin else
                break;
            case 4:
                cout<<"Ingrese el número de seguro social del paciente"<<endl;
                cin>>numid;
                cout<<"Ingrese la cantidad de días que el paciente estuvo internado: "<<endl;
                cin>>diasTrans;
                totalPagar(paciente,numid,diasTrans);
                bajaPaciente(paciente, numid);
                break;
            case 5:
                exit(5);
                return 5;
                break;
            default:
                cout<<"Opcion incorrecta"<<endl;
                break;
        }
        cout<<"¿Desea elegir otra opción? (s/n)"<<endl;
        cin>>r;
    } while(r=='s'); //fin do-while 1

}
//inicio de funcion altaPaciente
void altaPaciente(pacient *&paciente, int numss, string nombre, int edad, string dir, char sexo, string enf, float precioEnf,int di, int mi, int ai){
    pacient *nPacient=new pacient;
    nPacient->id=numss;
    nPacient->name=nombre;
    nPacient->age=edad;
    nPacient->address=dir;
    nPacient->sex=sexo;
    nPacient->sickness=enf;
    nPacient->eprice=precioEnf;
    nPacient->dayA=di;
    nPacient->monthA=mi;
    nPacient->yearA=ai;
    pacient *aux1=paciente;
    pacient *aux2;
        while ((aux1!=NULL)&&(aux1->id<numss)){ //inicio while
            aux2=aux1;
            aux1=aux1->siguiente;
        } //fin while
        if (paciente==aux1){//inicio if
            paciente = nPacient;
        } //fin if
        else{//inicio else
            aux2->siguiente=nPacient;
        }//fin else
        nPacient->siguiente=aux1;
        cout<<"\tEl paciente "<<nombre<<" con el número social: "<<numss<<" ha sido insertado a la lista correctamente"<<endl;
    }
//fin funcion altaPacient

//inicio funcion buscarPaciente
void buscarPaciente(pacient *paciente, int n){
    bool band =false;
    pacient *actual =new pacient();
    pacient *aux=new pacient();
    actual=paciente;
    while ((actual!=NULL)&&(actual->id<=n)) {//inicio while
        if (actual->id==n) {//inicio if
            band=true;
        }//fin if
        actual=actual->siguiente;
    }//fin while
    if (band==true) {//inicio if
        aux=actual;
        cout<<"\nEl paciente con el número de seguro "<<n<<"\n tiene los siguientes datos: "<<endl;
        cout<<"\nNombre: "<<aux->name<<endl;
        cout<<"Edad: "<<aux->age<<endl;
        cout<<"Dirección: "<<aux->address<<endl;
        cout<<"Sexo: "<<aux->sex<<endl;
        cout<<"Enfermedad"<<aux->sickness<<endl;
        cout<<"Fecha que ingresó"<<aux->dayA<<"/"<<actual->monthA<<"/"<<actual->yearA<<endl;
    }//fin if
    else{//inicio else
        cout<<"El paciente con el número de seguro  "<<n<<"\t NO ha sido encontrado en la lista"<<endl;
    }//fin else
}
//fin funcion buscarPaciente

//inicio funcion consultaPacientes
void consultaPacientes(pacient *paciente){
    pacient *actual=new pacient();
       actual=paciente;
       while (actual!=NULL){//inicio while
           cout<<"\nEl paciente tiene los siguientes datos:"<<endl;
           cout<<"\nNúmero de seguro: "<<actual->id<<endl;
           cout<<"Nombre: "<<actual->name<<endl;
           cout<<"Edad: "<<actual->age<<endl;
           cout<<"Municipio: "<<actual->address<<endl;
           cout<<"Sexo: "<<actual->sex<<endl;
           cout<<"Enfermedad: "<<actual->sickness<<endl;
           cout<<"Fecha que ingresó: "<<actual->dayA<<"/"<<actual->monthA<<"/"<<actual->yearA<<endl;
           actual=actual->siguiente;
       }//fin while
}
//fin funcion consultaPacientes

//inicio funcion totalPagar
void totalPagar(pacient *paciente, int id,int n){
    pacient *p=new pacient;
    p=paciente;
    float total=0;
    bool band=false;
    while((paciente!=NULL)&&(paciente->id<=id)){//inicio while
        if (paciente->id==id) {//inicio if
            band=true;
            total=paciente->eprice;
            total=total*n;
              }//fin if
              paciente=paciente->siguiente;
          }//fin while
          if (band==true) {//inicio if
              cout<<"El total a pagar es de: $"<<total<<endl;
    }//fin if
          else{//inicio else
           cout<<"El paciente con el número de seguro  "<<id<<"\t NO ha sido encontrado en la lista"<<endl;
       }//fin else
}
//fin funcion totalPagar

//inicio funcion bajaPaciente
void bajaPaciente(pacient *&paciente, int n){
    pacient *aux=paciente;
    n=aux->id;
    paciente=aux->siguiente;
    delete aux;
    cout<<"El paciente se ha dado de alta"<<endl;
}
//fin funcion bajaPaciente

//inicio validarFecha
void validarFecha(pacient *paciente, int d, int m, int a){
    d=paciente->dayA;
    m=paciente->monthA;
    a=paciente->yearA;
    if(d > 0 && d < 32) {
        if(m>0&&m<13){
            if (a>=1900&&a<=2050){
                cout<<"La fecha es válida"<<endl;
            }else{
            cout<<"La fecha no es válida"<<endl;
                   }
        }else{
        cout<<"La fecha no es válida"<<endl;
               }
    } else{
    cout<<"La fecha no es válida"<<endl;
           }
}
//fin validarFecha
