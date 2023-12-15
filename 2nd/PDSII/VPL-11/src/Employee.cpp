//Employee.cpp

// Definições de função-membro da classe básica abstrata Employee.
// Nota: Nenhuma definição recebe funções virtuais puras.
#include <iostream>
using std::cout;
using std::endl;

#include "Employee.hpp" // Definição da classe Employee

// construtor
Employee::Employee( const string &first, const string &last, const string &ssn )
			: firstName( first ), lastName( last ), socialSecurityNumber( ssn ){
			// corpo vazio
} // fim do construtor Employee

//configura o nome
void Employee::setFirstName(const string &first){
	this->firstName = first;
}

//retorna o nome
string Employee::getFirstName() const{
	return this->firstName;
} 

// configura o sobrenome
void Employee::setLastName( const string &last )
{
	this->lastName = last;

} // fim da função setLastName

// retorna o sobrenome
string Employee::getLastName() const{
	return this->lastName;
} // fim da função getLastName

// configura o SSN
void Employee::setSocialSecurityNumber( const string &ssn )
{
	this->socialSecurityNumber = ssn;
} // fim da função setSocialSecurityNumber

// retorna o SSN
string Employee::getSocialSecurityNumber() const
{
	return this->socialSecurityNumber;
} // fim da função getSocialSecurityNumber

// imprime informações de Employee (virtual, mas não virtual pura)
void Employee::print() const
{
	cout << "Name: " << this->firstName << " " << this->lastName << endl;
	cout << "SSN: " << this->socialSecurityNumber << endl;
} // fim da função print

