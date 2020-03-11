//
//  hospital.cpp
//  hospital
//
//  Created by Giselle Medina on 05/03/20.
//  Copyright © 2020 Giselle Medina. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
using namespace std;

struct pacient{
    int id;
    string name;
    int age;
    string address;
    char sex;
    string sickness;
    int dayA;
    int monthA;
    int yearA;
    int daysP;
    float eprice;
    float total;
    pacient *siguiente;
};

void altaPaciente(pacient *&, int,string,int,string,char,string,float,int,int,int);
void consultaPacientes(pacient *);
void buscarPaciente(pacient *, int);
void totalPagar(pacient *, int, int);
void bajaPaciente(pacient *, int);

int main(int argc, const char * argv[]) {
    pacient *paciente=NULL;
    int opc,numid,edad,aux,di,mi,ai,diasTrans;
    float precioEnf = 0.0,total;
    string nom,dir,enfermedad;
    char r,s;
    cout << "¡Bienvenido!\n";
    do{
        cout<<"Menú Principal"<<endl;
        cout<<"1) Alta de Pacientes"<<endl;
        cout<<"2) Búsqueda de Paciente"<<endl;
        cout<<"3) Consulta de pacientes"<<endl;
        cout<<"4) Baja de Paciente"<<endl;
        cout<<"5) Salir"<<endl;
        cout<<"Elija una opción: "<<endl;
        cin>>opc;
        switch (opc) {
            case 1:
                do{
                    cout<<"Número de seguro social: "<<endl;
                    cin>>numid;
                    cout<<"Nombre: "<<endl;
                    cin>>nom;
                    cout<<"Edad: "<<endl;
                    cin>>edad;
                    cout<<"Municipio: "<<endl;
                    cin>>dir;
                    cout<<"Sexo: "<<endl;
                    cin>>s;
                    cout<<"¿Qué enfermedad tiene?"<<endl;
                    cout<<"1) Neumonia"<<endl;
                    cout<<"2) Sinusitis"<<endl;
                    cout<<"3) Laberintitis"<<endl;
                    cout<<"4) Insuficiencia renal"<<endl;
                    cin>>aux;
                    switch (aux) {
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
                            }
                    cout<<"Ingrese fecha de ingreso\nDía: "<<endl;
                    cin>>di;
                    cout<<"Mes: "<<endl;
                    cin>>mi;
                    cout<<"Año: "<<endl;
                    cin>>ai;
                    altaPaciente(paciente, numid, nom, edad, dir, s, enfermedad, precioEnf,di, mi, ai);
                    cout<<"¿Desea agregar a otro paciente? (s/n)"<<endl;
                    cin>>r;
                }
                while(r=='s');
                break;
            case 2:
                if(paciente==NULL){
                    cout<<"No ha ingresado a ningún paciente"<<endl;
                } else{
                    cout<<"Ingrese el número de seguro del paciente"<<endl;
                    cin>>numid;
                    buscarPaciente(paciente, numid);
                }
                break;
            case 3:
                consultaPacientes(paciente);
                break;
            case 4:
                cout<<"Ingrese el número de seguro social del paciente"<<endl;
                cin>>numid;
                cout<<"Ingrese la cantidad de días que el paciente estuvo internado: "<<endl;
                cin>>diasTrans;
                totalPagar(paciente,numid,diasTrans);
                cout<<"El total a pagar es de: $"<<total;
                bajaPaciente(paciente, numid);
                break;
            case 5:
                exit(5);
                return 5;
                break;
            default:
                break;
        }
        cout<<"¿Desea elegir otra opción? (s/n)"<<endl;
        cin>>r;
    }while(r=='s');

}
void altaPaciente(pacient *&paciente, int numss, string nombre, int edad, string dir, char sexo, string enf, float precioEnf,int di, int mi, int ai){
    pacient *nPacient=new pacient;
    nPacient->id=numss;
    nPacient->name=nombre;
    nPacient->age=edad;
    nPacient->address=dir;
    nPacient->sex=sexo;
    nPacient->sickness=enf;
    nPacient->dayA=di;
    nPacient->monthA=mi;
    nPacient->yearA=ai;
    nPacient->eprice=precioEnf;
    pacient *aux1=paciente;
    pacient *aux2;
        while ((aux1!=NULL)&&(aux1->id<numss)){
            aux2=aux1;
            aux1=aux1->siguiente;
        }
        if (paciente==aux1){
            paciente = nPacient;
        }
        else{
            aux2->siguiente=nPacient;
        }
        nPacient->siguiente=aux1;
        cout<<"\tEl paciente "<<nombre<<" con el número social: "<<numss<<" ha sido insertado a la lista correctamente"<<endl;
    }

void buscarPaciente(pacient *paciente, int n){
    bool band =false;
    pacient *actual =new pacient();
    pacient *aux=new pacient();
    actual=paciente;
    while ((actual!=NULL)&&(actual->id<=n)) {
        if (actual->id==n) {
            band=true;
        }
        actual=actual->siguiente;
    }
    if (band==true) {
        aux=actual;
        cout<<"\nEl paciente con el número de seguro "<<n<<"\n tiene los siguientes datos: "<<endl;
        cout<<"\nNombre: "<<aux->name<<endl;
        cout<<"Edad: "<<aux->age<<endl;
        cout<<"Dirección: "<<aux->address<<endl;
        cout<<"Sexo: "<<aux->sex<<endl;
        cout<<"Enfermedad"<<aux->sickness<<endl;
        cout<<"Fecha que ingresó"<<aux->dayA<<"/"<<actual->monthA<<"/"<<actual->yearA<<endl;
    } else{
        cout<<"El paciente con el número de seguro  "<<n<<"\t NO ha sido encontrado en la lista"<<endl;
    }
}

void consultaPacientes(pacient *paciente){
    pacient *actual=new pacient();
       actual=paciente;
       while (actual!=NULL){
           cout<<"\nEl paciente tiene los siguientes datos:"<<endl;
           cout<<"\nNúmero de seguro: "<<actual->id<<endl;
           cout<<"Nombre: "<<actual->name<<endl;
           cout<<"Edad: "<<actual->age<<endl;
           cout<<"Municipio: "<<actual->address<<endl;
           cout<<"Sexo: "<<actual->sex<<endl;
           cout<<"Enfermedad: "<<actual->sickness<<endl;
           cout<<"Fecha que ingresó: "<<actual->dayA<<"/"<<actual->monthA<<"/"<<actual->yearA<<endl;
           actual=actual->siguiente;
       }
}
void totalPagar(pacient *paciente, int id,int n){
    float total=0;
    bool band=false;
    while((paciente!=NULL)&&(paciente->id<=id)){
        if (paciente->id==id) {
                  band=true;
              }
              paciente=paciente->siguiente;
          }
          if (band==true) {
        total=paciente->eprice;
    } else{
           cout<<"El paciente con el número de seguro  "<<id<<"\t NO ha sido encontrado en la lista"<<endl;
       }
    total=total*n;
    cout<<"El total a pagar es de: $"<<total;
}
void bajaPaciente(pacient *paciente, int n){
    if(paciente!=NULL){
         pacient *aux_borrar;
         pacient *anterior=NULL;
         aux_borrar=paciente;
         while((aux_borrar!=NULL)&&(aux_borrar->id!=n)){
         anterior=aux_borrar;
         aux_borrar = aux_borrar -> siguiente;
          }
         if(aux_borrar==NULL){
                cout<<"El paciente no existe";
         }
         else if (anterior==NULL){
         paciente=paciente->siguiente;
         delete aux_borrar;
          }
         else{
         anterior->siguiente=aux_borrar->siguiente;
         delete aux_borrar;
         cout<<"El paciente ha sido dado de alto";
         }
      }
}
