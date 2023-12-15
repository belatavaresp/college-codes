// CommissionEmployee.cpp
// Definições de função-membro da classe CommissionEmployee.
#include <iostream>
using std::cout;

#include "ComissionEmployee.hpp" // definição da classe CommissionEmployee

// construtor
	CommissionEmployee::CommissionEmployee( const string &first,
	const string &last, const string &ssn, double sales, double rate )
	: Employee( first, last, ssn ){
	
	setGrossSales(sales);
	setCommissionRate(rate);

} // fim do construtor CommissionEmployee

void CommissionEmployee::setCommissionRate(double rate) {
	this->commissionRate = rate;
} // fim da função getCommissionRate

// retorna a taxa de comissão
double CommissionEmployee::getCommissionRate() const{
	return this->commissionRate;
} // fim da função getCommissionRate

// configura a quantidade de vendas brutas
void CommissionEmployee::setGrossSales( double sales )
{
	this->grossSales = sales;
} // fim da função setGrossSales

// retorna a quantidade de vendas brutas
double CommissionEmployee::getGrossSales() const
{
	return this->grossSales;
} // fim da função getGrossSales

// calcula os rendimentos;
// sobrescreve a função virtual pura earnings em Employee
double CommissionEmployee::earnings() const
{
	return (this->grossSales * this->commissionRate);
} // fim da função earnings

// imprime informações do CommissionEmployee
void CommissionEmployee::print() const
{
	Employee::print();
	cout << "Gross sales: " << this->grossSales << std::endl;
	cout << "Commission rate: " << this->commissionRate << std::endl;
} // fim da função print