#pragma once
#include <iostream>
#include <math.h>
#include "RadianyStopnie.h"

using namespace std;

template <int n>
class Wektor
{
private:
	float x; float y; float z; float w;
public:
	Wektor();
	Wektor(float x);
	Wektor(float x, float y, float z);
	Wektor(float x, float y, float z, float w);
	Wektor(float array[n]);

	/*W przypadku, gdy wystepuje & przed 'operator', to nie jest zwracana nowa zmieanna tylko
	modyfikowany jest pierwszy argument, a zwracany jest wskaźnik na niego. */
	Wektor<n>& operator = (const Wektor<n>& w);
	Wektor<n> operator + (const Wektor<n> & w);
	Wektor<n>& operator += (const Wektor<n> & w);
	Wektor<n> operator - (const Wektor<n> & w);
	Wektor<n>& operator -= (const Wektor<n> & w);
	Wektor<n> operator * (const int & skalar);
	Wektor<n>& operator *= (const int & skalar);

	template<int u>
	friend std::ostream& operator<< (std::ostream&, Wektor<u> const&);

	float getX();
	float getY();
	float getZ();
	float getW();
	void setX(float);
	void setY(float);
	void setZ(float);
	void setW(float);

	void normalizacjaWektora();
	float iloczynSkalarny(Wektor<n>& w1, Wektor<n>& w2);
	Wektor<n>& iloczynWektorowy(Wektor<n>& w1, Wektor<n>& w2);
	float liczDlugoscWektora();
	bool walidujRozmiarWektora();
};

//3.1 Ustawianie i zwracanie x, y, z, w (setters, getters).
template<int n>
float Wektor<n>::getX(){
	return this->x;
}

template<int n>
void Wektor<n>::setX(float x) {
	this->x = x;
}

template<int n>
float Wektor<n>::getY(){
	return this->y;
}

template<int n>
void Wektor<n>::setY(float y) {
	this->y = y;
}

template<int n>
float Wektor<n>::getZ(){
	return this->z;
}

template<int n>
void Wektor<n>::setZ(float z) {
	this->z = z;
}

template<int n>
float Wektor<n>::getW(){
	return this->w;
}

template<int n>
void Wektor<n>::setW(float w){
	this->w = w;
}

template <int n>
bool Wektor<n>::walidujRozmiarWektora()
{
	if (n != 3 && n != 4){
		cout << "Wielkosc wektora moze byc tylko 3 lub 4." << endl;
		return false;
	}
	return true;
}

//1. Stworzyć konstruktory:
//1.1 Bez parametrów
template <int n>
inline Wektor<n>::Wektor(){
	if(walidujRozmiarWektora()) {
		if (n == 4){
			this->x = 0;
			this->y = 0;
			this->z = 0;
			this->w = 0;
		}
		else if (n == 3){
			this->x = 0;
			this->y = 0;
			this->z = 0;
		}
	}

}

//1.2 Z jednym, trzema i czterema parametrami typu float. 
template <int n>
inline Wektor<n>::Wektor(float x)
{
	if (walidujRozmiarWektora()) {
		if (n == 4) {
			this->setX(x);
			this->setY(x);
			this->setZ(x);
			this->setW(x);
		}
		else if (n == 3){
			this->setX(x);
			this->setY(x);
			this->setZ(x);
		}
	}

}

template <int n>
inline Wektor<n>::Wektor(float x, float y, float z)
{
	this->setX(x);
	this->setY(y);
	this->setZ(z);
	
}

template <int n>
inline Wektor<n>::Wektor(float x, float y, float z, float w)
{
	this->setX(x);
	this->setY(y);
	this->setZ(z);
	this->setW(w);
}

//1.3 Przyjmujący jako argument tablicę elementów typu float. 
template<int n>
inline Wektor<n>::Wektor(float tablicaWektor[n])
{
	if (n == 4){
		this->x = tablicaWektor[0];
		this->y = tablicaWektor[1];
		this->z = tablicaWektor[2];
		this->w = tablicaWektor[3];
	}
	else if (n == 3){
		this->x = tablicaWektor[0];
		this->y = tablicaWektor[1];
		this->z = tablicaWektor[2];
	}
}

//2. Przeciążyć operatory:
//2.1 Przypisania =
template<int n>
inline Wektor<n>& Wektor<n>::operator = (const Wektor<n>& w)
{
	Wektor<n> w2 = Wektor<n>();
	w2.setX(this->x + w.x);
	w2.setY(this->y + w.y);
	w2.setZ(this->z + w.z);

	if(n == 4){
		this->setW(w.w);
	}

	return *this;
}


//2.2 Dodawania +
template<int n>
inline Wektor<n> Wektor<n>::operator+(const Wektor<n>& w1)
{
	Wektor<n> w2 = Wektor<n>();
	w2.setX(this->x + w1.x);
	w2.setY(this->y + w1.y);
	w2.setZ(this->z + w1.z);

	if (n == 4){
		w2.setW(this->w + w1.w);
	}
	return w2;
}


//2.3 Dodawania z przypisaniem +=

template<int n>
inline Wektor<n>& Wektor<n>::operator+=(const Wektor<n>& w1)
{
	
	this->setX(this->getX() + w1.x);
	this->setY(this->getY() + w1.y);
	this->setZ(this->getZ() + w1.z);
	
	if(n == 4){
		this->setW(this->getW() + w1.w);
	}
	return *this;
}

//2.4 Odejmowania -
template<int n>
inline Wektor<n> Wektor<n>::operator-(const Wektor<n>& w1)
{
	Wektor<n> w2 = Wektor<n>();
	w2.setX(this->getX() - w1.x);
	w2.setY(this->getY() - w1.y);
	w2.setZ(this->getZ() - w1.z);
	
	if(n == 4){
		w2.setW(this->getW() - w1.w);
	}
	return w2;
}

//2.5 Odejmowania z przypisaniem -=
template<int n>
inline Wektor<n>& Wektor<n>::operator-=(const Wektor<n>& w1)
{
	this->setX(this->getX() - w1.x);
	this->setY(this->getY() - w1.y);
	this->setZ(this->getZ() - w1.z);

	if(n == 4){
		this->setW(this->getW() + w1.w);
	}
	return *this;
}

//2.6 Mnożenia * (przez liczbę całkowitą)
template<int n>
inline Wektor<n> Wektor<n>::operator*(const int& skalar)
{

	Wektor<n> w2 = Wektor<n>();
	w2.setX(this->getX() * skalar);
	w2.setY(this->getY() * skalar);
	w2.setZ(this->getZ() * skalar);
	
	if(n == 4){
		this->setW(this->getW() * skalar);
	}
	return w2;
}

//2.7 Mnożenia z przypisaniem *= (przez liczbę całkowitą)
template<int n>
inline Wektor<n>& Wektor<n>::operator*=(const int& skalar)
{
	this->setX(this->getX() * skalar);
	this->setY(this->getY() * skalar);
	this->setZ(this->getZ() * skalar);
	
	if(n == 4){
		this->setW(this->getW() * skalar);
	}
	return *this;
}

//2.8 Wysyłania do strumienia <<
template<int n>
inline ostream& operator << (ostream& out, Wektor<n> const& w)
{
	if (n == 3){
		out << "(x: " << w.x << ", y: " << w.y << ", z: " << w.z << ")";
	}
	else if (n == 4){
		out << "(x: " << w.x << ", y: " << w.y << ", z: " << w.z << ", w: " << w.w << ")";
	}
	return out;
}

//Metoda liczenia dlugosc wektora porzebna do normalizacji wektora
template<int n>
float Wektor<n>::liczDlugoscWektora()
{
	if (n == 3){
		return sqrt(this->getX() * this->getX() + this->getY() * this->getY() + this->getZ() * this->getZ());
	}
	else if (n == 4){
		return sqrt(this->getX() * this->getX() + this->getY() * this->getY() + this->getZ() * this->getZ() + this->getW() * this->getW());
	}
}

//3. Dodać metody realizujące:
//3.2 Normalizację wektora.
template<int n>
void Wektor<n>::normalizacjaWektora()
{ 
	float dlugoscWektora = liczDlugoscWektora();
	if (n == 3){
		this->setX(this->getX() / dlugoscWektora);
		this->setY(this->getY() / dlugoscWektora);
		this->setZ(this->getZ() / dlugoscWektora);
	}
	else if (n == 4){
		this->setX(this->getX() / dlugoscWektora);
		this->setY(this->getY() / dlugoscWektora);
		this->setZ(this->getZ() / dlugoscWektora);
		this->setW(this->getW() / dlugoscWektora);
	}
}

//3.3 Iloczyn skalarny.
template<int n>
float Wektor<n>::iloczynSkalarny(Wektor<n>& w1, Wektor<n>& w2)
{
	if (n == 3){
		return w1.x * w2.x + w1.y * w2.y + w1.z * w2.z;
	}
	else if (n == 4){
		return w1.x * w2.x + w1.y * w2.y + w1.z * w2.z + w1.w * w2.w;
	}
}

//3.4 Iloczyn wektorowy
//x,y,z,w
template<int n>
inline Wektor<n>& Wektor<n>::iloczynWektorowy(Wektor<n>& w1, Wektor<n>& w2)
{
	Wektor w3 = Wektor<n>();
	if (n == 3){
		w3.setX(w1.getY() * w2.getZ() - w1.getZ() * w2.getY());
		w3.setY(w1.getZ() * w2.getX() - w1.getX() * w2.getZ());
		w3.setZ(w1.getX() * w2.getY() - w1.getY() * w2.getX());
	}
	else if (n == 4){
		w3.setX(w1.getZ() * w2.getW() - w1.getW() * w2.getZ());
		w3.setY(w1.getW() * w2.getX() - w1.getX() * w2.getW());
		w3.setZ(w1.getX() * w2.getY() - w1.getY() * w2.getX());
		w3.setW(w1.getY() * w2.getZ() - w1.getZ() * w2.getY());
	}
	return w3;
}






