#include <iostream>
#include <string>
#include <iomanip>

int main(){

    //Variables generales
    int tipo_cliente, plazo, total = 0, monto = 0;
    double interes = 0;
    bool codeudor, aprobado = true;
    std::string motivo_rechazo;

    //Variables por cliente
    float tasa, por_tasa, descuento_ep = 0;;
    double limite_sin = 0, limite_con = 0, limite_real = 0;
    int plazo_max;


    //Ingreso de tipo de cliente
    std::cout << "--- SIMULADOR DE PRÉSTAMOS CLICKBANK ---" << std::endl;
    std::cout << "Tipo de cliente ingrese el número correspondiente (1. Estudiante, 2. Empleado, 3. Pensionado, 4. Desempleado): ";
    std::cin >> tipo_cliente;

    //Ingreso del monto solicitado
    std::cout << "Ingrese el monto solicitado: $";
    std::cin >> monto;
    
    //Ingreso del plazo del prestamo en meses
    std::cout << "Ingrese el plazo en meses: ";
    std::cin >> plazo;

    //Ingreso si tiene codeudor
    std::cout << "¿Tiene codeudor? (1 = Sí, 0 = No): ";
    std::cin >> codeudor;

    switch(tipo_cliente){
        case 1:
            tasa = 0.06;
	    por_tasa = 6;
            limite_sin = 2000000;
            limite_con = 5000000;
            plazo_max = (monto <= 2000000) ? 12 : 24;
        break;

        case 2:
        descuento_ep = (codeudor) ? 0.10: 0;
            tasa = (plazo > 36) ? 0.07+0.015: 0.07;
	    por_tasa = (plazo > 36) ? 7+1.5: 7;
            limite_sin = 5000000;
            limite_con = 10000000;
            plazo_max = (monto <= 5000000) ? 24 : 48;
        break;

        case 3:
		tasa = 0.04;
		por_tasa = 4;
            descuento_ep = (codeudor) ? 0.10: 0;
            limite_sin = 3000000;
            limite_con = 7000000;
            plazo_max = (monto <= 3000000) ? 24 : 36;
        break;

        case 4:
            tasa = 0.08;
	    por_tasa = 8;
            limite_sin = 0;
            limite_con = 2000000;
            plazo_max = 12;
        break;

        default:
            aprobado = false;
            motivo_rechazo = "Datos de entrada no validos";
        break;
    }

    if(aprobado){

        //Asigna el valor del limite si tiene o no deudor
        limite_real = (codeudor) ? limite_con : limite_sin;

        if(tipo_cliente == 4 && !codeudor){
            aprobado = false;
            motivo_rechazo = "Desempleados requieren obligatoriamente tener codeudor.";
        }else if(monto > limite_real && !codeudor){
            aprobado = false;
            motivo_rechazo = "El monto excede el limite sin codeudor.";
        }else if(monto > limite_real){
            aprobado = false;
            motivo_rechazo = "El monto excede el limite para su perfil.";
        }else if(plazo > plazo_max){
            aprobado = false;
            motivo_rechazo = "El plazo excede el maximo permitido para este monto.";

        }else if(monto <=  0 || plazo <= 0){
            aprobado = false;
            motivo_rechazo = "Datos de entrada no validos";
        } 

    }

    std::cout << "----------------------------------------" << std::endl;

    if(aprobado){
        
        //Formula para calcular el interes y sumarla al total
        interes = monto * tasa * plazo;
	interes = interes - (interes * descuento_ep);
        total = monto + interes;

        std::cout << std::fixed << std::setprecision(0);
        std::cout << "El préstamo solicitado por un monto de $" << monto << " a un plazo de " << plazo << " meses es APROBADO con una tasa del " << por_tasa << "% \nTotal a pagar: $" << total << std::endl;
    }else {
        std::cout << "RECHAZADO ";
        std::cout << motivo_rechazo << std::endl;
    }
    std::cout << "----------------------------------------" << std::endl;

    return 0;
}
