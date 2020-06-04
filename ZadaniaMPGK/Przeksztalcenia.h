#include "Macierz.h"

using namespace std;

template <int n>
class Przeksztalcenia
{

private:
	Macierz<n> macierz;
public:
	
	Przeksztalcenia();
	Macierz<n> getMacierz();

	Przeksztalcenia<n> skaluj(float x);
	Przeksztalcenia<3> skaluj(float x, float y);
	Przeksztalcenia<4> skaluj(float x, float y, float z);
	Przeksztalcenia<n> skaluj(float tab[n]);

	Przeksztalcenia<n> przesun(float x);
	Przeksztalcenia<3> przesun(float x, float y);
	Przeksztalcenia<4> przesun(float x, float y, float z);
	Przeksztalcenia<n> przesun(float tab[n]);

	Przeksztalcenia<3> obroc(float stopien);
	Przeksztalcenia<4> obrocX(float stopien);
	Przeksztalcenia<4> obrocY(float stopien);
	Przeksztalcenia<4> obrocZ(float stopien);
	//Przeksztalcenia<4> obroc(float, Wektor<3>);
};

template<int n>
Przeksztalcenia<n>::Przeksztalcenia()
{
	Macierz<n> macierz = Macierz<n>();
}

template<int n>
inline Macierz<n> Przeksztalcenia<n>::getMacierz()
{
	return this->macierz;
}

template<int n>
inline Przeksztalcenia<n> Przeksztalcenia<n>::skaluj(float x)
{
	Macierz<n> m = Macierz<n>();
	for (int i = 0; i < n - 1; i++)
		m.setElement(i, i, x);

	this->macierz *= m;
	return *this;
}

template<int n>
Przeksztalcenia<3> Przeksztalcenia<n>::skaluj(float x, float y)
{
	Macierz<3> m = Macierz<3>();
	m.setElement(0, 0, x);
	m.setElement(1, 1, y);

	this->macierz *= m;
	return *this;
}

 
template<int n>
Przeksztalcenia<4> Przeksztalcenia<n>::skaluj(float x, float y, float z)
{
	Macierz<4> m = Macierz<4>();
	m.setElement(0, 0, x);
	m.setElement(1, 1, y);
	m.setElement(2, 2, z);

	this->macierz *= m;
	return *this;
}


template<int n>
Przeksztalcenia<n> Przeksztalcenia<n>::skaluj(float tab[n])
{
	Macierz<n> m = Macierz<n>();
	for (int i = 0; i < n - 1; i++)
		m.setElement(i, i, tab[i]);

	this->macierz *= m;
	return *this;
}

template<int n>
Przeksztalcenia<n> Przeksztalcenia<n>::przesun(float x)
{
	Macierz<n> m = Macierz<n>();
	for (int i = 0; i < n - 1; i++)
		m.setElement(n - 1, i, x);

	this->macierz *= m;
	return *this;
}

template<int n>
Przeksztalcenia<3> Przeksztalcenia<n>::przesun(float x, float y)
{
	Macierz<3> m = Macierz<3>();
	m.setElement(2, 0, x);
	m.setElement(2, 1, y);

	this->macierz *= m;
	return *this;
}

template<int n>
Przeksztalcenia<4> Przeksztalcenia<n>::przesun(float x, float y, float z)
{
	Macierz<4> m = Macierz<4>();
	m.setElement(3, 0, x);
	m.setElement(3, 1, y);
	m.setElement(3, 2, z);

	this->macierz *= m;
	return *this;
}

template<int n>
Przeksztalcenia<n> Przeksztalcenia<n>::przesun(float tab[n])
{
	Macierz<n> m = Macierz<n>();
	for (int i = 0; i < n - 1; i++)
		m.setElement(n - 1, i, tab[i]);

	this->macierz *= m;
	return *this;
}

template<int n>
Przeksztalcenia<3> Przeksztalcenia<n>::obroc(float stopnie)
{
	float theta = naRadiany(stopnie);
	Macierz<3> m = Macierz<3>();

	m.setElement(0, 0, (round(cosf(theta))));
	m.setElement(0, 1, (round(sinf(theta))));
	m.setElement(1, 0, (round(-sinf(theta))));
	m.setElement(1, 1, (round(cosf(theta))));

	this->macierz *= m;
	return *this;
}

template<int n>
inline Przeksztalcenia<4> Przeksztalcenia<n>::obrocX(float stopien)
{
	Macierz<4> m = Macierz<4>();
	float theta = naRadiany(stopien);

	m.setElement(1, 1, cosf(theta));
	m.setElement(1, 2, -sinf(theta));
	m.setElement(2, 1, sinf(theta));
	m.setElement(2, 2, cosf(theta));

	this->macierz *= m;
	return *this;
}

template<int n>
inline Przeksztalcenia<4> Przeksztalcenia<n>::obrocY(float stopien)
{
	Macierz<4> m = Macierz<4>();
	float theta = naRadiany(stopien);

	m.setElement(0, 0, cosf(theta));
	m.setElement(0, 2, sinf(theta));
	m.setElement(2, 0, -sinf(theta));
	m.setElement(2, 2, cosf(theta));

	this->macierz *= m;
	return *this;
}

template<int n>
inline Przeksztalcenia<4> Przeksztalcenia<n>::obrocZ(float stopien)
{
	Macierz<4> m = Macierz<4>();
	float theta = naRadiany(stopien);

	m.setElement(0, 0, cosf(theta));
	m.setElement(0, 1, -sinf(theta));
	m.setElement(1, 0, sinf(theta));
	m.setElement(1, 1, cosf(theta));

	this->macierz *= m;
	return *this;
}






