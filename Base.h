#ifndef __Base_H_
#define __Base_H_

#include <string>
#include <iostream>

class Printable{
public:
	virtual void Print() const = 0;

};

class Named : virtual public Printable{
public:
	explicit Named( std::string iName ){ m_name = iName; }
	void Print() const { std::cout << m_name << std::endl; }
private:
	std::string m_name;
};

#endif // __Container_H_