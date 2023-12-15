// BasePlusCommissionEmployee.cpp
// Definições de função-membro BasePlusCommissionEmployee.
#include <iostream>
using std::cout;

// definição da classe BasePlusCommissionEmployee
#include "BasePlusComissionEmployee.hpp"

// construtor
BasePlusCommissionEmployee::BasePlusCommissionEmployee(
const string &first, const string &last, const string &ssn,
double sales, double rate, double salary )
: CommissionEmployee( first, last, ssn, sales, rate )
{
	setBaseSalary(salary);
} // fim do construtor BasePlusCommissionEmployee

// configura o salário-base
void BasePlusCommissionEmployee::setBaseSalary( double salary )
{
	this->baseSalary = salary;
} // fim da função setBaseSalary

// retorna o salário-base
double BasePlusCommissionEmployee::getBaseSalary() const
{
	return this->baseSalary;
} // fim da função getBaseSalary

// calcula os rendimentos;
// sobrescreve a função virtual pura earnings em Employee
double BasePlusCommissionEmployee::earnings() const
{
	return ((this->baseSalary * 1.1) + (CommissionEmployee::earnings()));
} // fim da função earnings

 // imprime informações de BasePlusCommissionEmployee
void BasePlusCommissionEmployee::print() const
{
	CommissionEmployee::print();
	cout << "Base Salary: " << this->baseSalary << std::endl;
} // fim da função print