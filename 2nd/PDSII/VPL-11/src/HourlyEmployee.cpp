// HourlyEmployee.cpp
// Definições de função-membro da classe HourlyEmployee.
#include <iostream>
using std::cout;

#include "HourlyEmployee.hpp" // definição da classe HourlyEmployee

// construtor
HourlyEmployee::HourlyEmployee( const string &first, const string &last,
				const string &ssn, double hourlyWage, double hoursWorked )
 				: Employee( first, last, ssn ){
 	setWage(hourlyWage);
	setHours(hoursWorked);
} // fim do construtor HourlyEmployee

// configura a remuneração
void HourlyEmployee::setWage( double hourlyWage )
{
	this->wage = hourlyWage;
} // fim da função setWage

// retorna a remuneração
double HourlyEmployee::getWage() const
{
	return this->wage;
} // fim da função getWage

// configura as horas trabalhadas
void HourlyEmployee::setHours( double hoursWorked )
{
	this->hours = hoursWorked;
} // fim da função setHours

// retorna as horas trabalhadas
double HourlyEmployee::getHours() const
{
 	return this->hours;
} // fim da função getHours

// calcula os rendimentos;
// sobrescreve a função virtual pura earnings em Employee
double HourlyEmployee::earnings() const
{
	return (this->hours * this->wage);
} // fim da função earnings

// imprime informações do HourlyEmployee
void HourlyEmployee::print() const
{
	Employee::print();
	cout << "Wage: " << this->wage << std::endl;
	cout << "Hours Worked: " << this->hours << std::endl;
} // fim da função print