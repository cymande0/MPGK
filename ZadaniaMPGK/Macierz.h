#include <iostream>
#include <sstream>
#include <math.h>
#include "Wektor.h"

using namespace std;

template<int n>
class Macierz
{

public:

	float macierz[n][n];

	Macierz();
	Macierz(float a);
	Macierz(float**);
	Macierz(float(*)[n]);

//	Macierz(float macierz[n][n]);
	//Macierz(const Macierz& macierz);

	/*W przypadku, gdy wystepuje & przed 'operator', to nie jest zwracana nowa zmieanna tylko
	modyfikowany jest pierwszy argument, a zwracany jest wskaźnik na niego. */
	//2.1
	Macierz<n>& operator =(const Macierz<n>& m);
	//2.2
	Macierz<n> operator +(const Macierz<n>& m);
	//2.3
	Macierz<n>& operator +=(const Macierz<n>& m);
	//2.4
	Macierz<n> operator -(const Macierz<n>& m);
	//2.5
	Macierz<n>& operator -=(const Macierz<n>& m);
	//2.6
	Macierz<n> operator *(const int& skalar);
	//2.7
	Macierz<n>& operator *=(const int& skalar);
	//2.8
	Macierz<n> operator *(const Macierz<n>& m);
	//2.9
	Macierz<n>& operator *=(const Macierz<n>& m);
	//2.10
	template<int k>
	friend Wektor<k> operator *(Macierz<k>& m, Wektor<k>& w);
	//2.11
	template<int k>
	friend ostream& operator<<(ostream& out, const Macierz<k>& m);

	float getElement(int wiersz, int kolumna);
	void setElement(int wiersz, int kolumna, float wartosc);
	float* getTablicaMacierzy();
	Macierz<n> stworzMacierzJednostkowa();

	//tylko 3x3 i 4x4
	bool walidujeWielkoscMacierzy();
	int obliczWyznacznik(float **macierz, int rozmiar);
	float **transponujMacierz(float** macierz, int rozmiar);
	float **obliczMacierzOdwrocona(float **macierz, int rozmiar);
	float **odwrocMacierz(float **macierz, int rozmiar, int wyznacznik);
	float **liczDopelnienie(float **macierz, int rozmiar);

};

template<int n>
bool Macierz<n>::walidujeWielkoscMacierzy()
{
	if (n != 3 && n != 4)
	{
		cout << "Macierz moze byc tylko 3x3 lub 4x4";
		return false;
	}
	return true;
}

//1.1
template<int n>
inline Macierz<n>::Macierz()
{
	//Macierz jednostkowa
	if (walidujeWielkoscMacierzy()) {
		for (int i = 0; i < n; i++){
			for (int j = 0;  j < n; j++) {
				if (i == j) {
					macierz[i][j] = 1;
				}
				else {
					macierz[i][j] = 0;
				}
			}
		}
	}
}

//1.2
template<int n>
Macierz<n>::Macierz(float a)
{
	if (walidujeWielkoscMacierzy()){
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				macierz[i][j] = a;
			}
		}
	}
}

//1.3
template<int n>
Macierz<n>::Macierz(float** tablica)
{
	if (walidujeWielkoscMacierzy()){
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				macierz[i][j] = tablica[i][j];
			}
		}
	}
}

template<int n>
inline Macierz<n>::Macierz(float(* tablica)[n])
{
	if (walidujeWielkoscMacierzy()){
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				macierz[i][j] = tablica[i][j];
			}
		}
	}
}



//2.1 Przypisywania =
template<int n>
Macierz<n>& Macierz<n>::operator=(const Macierz<n>& m)
{
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			this->macierz[i][j] = m.macierz[i][j];
		}
	}
	return *this;
}

//2.2 Dodawania +
template<int n>
Macierz<n> Macierz<n>::operator+(const Macierz<n>& m1)
{
	Macierz<n> m2 = Macierz<n>();

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			m2.macierz[i][j] = this->macierz[i][j] + m1.macierz[i][j];
		}
	}
	return m2;
}

//2.3 Dodawania z przypisaniem +=
template<int n>
Macierz<n>& Macierz<n>::operator+=(const Macierz<n>& m)
{
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			this->macierz[i][j] += m.macierz[i][j];
		}
	}
	return *this;
}

//2.4) Odejmowania -
template<int n>
Macierz<n> Macierz<n>::operator-(const Macierz<n>& m1)
{
	Macierz<n> m2 = Macierz<n>();

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			m2.macierz[i][j] = this->macierz[i][j] - m1.macierz[i][j];
		}
	}
	return m2;
}

//2.5) Odejmowania z przypisaniem -=
template<int n>
Macierz<n>& Macierz<n>::operator-=(const Macierz<n>& m)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++){
			this->macierz[i][j] -= m.macierz[i][j];
		}
	}
	return *this;
}

//2.6) Mnożenia * (przez liczbę całkowitą)
template<int n>
Macierz<n> Macierz<n>::operator*(const int& skalar)
{
	Macierz<n> m = Macierz<n>();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++){
			m.macierz[i][j] = this->macierz[i][j] * skalar;
		}
	}
	return m;
}

//2.7) Mnożenia z przypisaniem *= (przez liczbę całkowitą)
template<int n>
Macierz<n>& Macierz<n>::operator*=(const int& skalar)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++){
			this->macierz[i][j] *= skalar;
		}
	}
	return *this;
}

//2.8) Mnożenia * (macierzy)
template<int n>
Macierz<n> Macierz<n>::operator*(const Macierz<n>& m1)
{
	Macierz<n> m2 = Macierz<n>();
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			for (int k = 0; k < n; k++){
				m2.macierz[i][j] += this->macierz[i][k] * m1.macierz[k][j];
			}
		}
	}
	return m2;
}

//2.9) Mnożenia z przypisaniem *= (macierzy)
template<int n>
Macierz<n>& Macierz<n>::operator*=(const Macierz<n>& m1)
{
	Macierz<n> m2 = *this;
	for (int i = 0; i < n; i++){
		for (int k = 0; k < n; k++){
			float temp = 0.0f;
			for (int j = 0; j < n; j++){
				temp += (m2.macierz[i][j] * m1.macierz[j][k]);
			}
			macierz[i][k] = temp;
		}
	}
	return *this;
}

//2.10) Mnożenia * (wektora przez macierz)
template<int k>
inline Wektor<k> operator*(Macierz<k>& m, Wektor<k>& w)
{
	float suma;
	float wektor[k];
	for (int i = 0; i < k; i++){
		suma = 0;
		suma += m.macierz[i][0] * w.getX();
		suma += m.macierz[i][1] * w.getY();
		suma += m.macierz[i][2] * w.getZ();
		if (k == 4) {
			suma += m.macierz[i][3] * w.getW();
		}
	}
	return Wektor<k>(wektor);
}

//2.11) Wysyłania do strumienia <<
template<int n>
ostream& operator<<(ostream& output, Macierz<n> const& m)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			output << m.macierz[i][j];
			if (j != n - 1) {
				output << ", ";
			}
		}
		if (i != n - 1) {
			output << ";\n ";
		}
	}
	return output;
}


//3.1) Ustawianie i zwracanie konkretnych elementów macierzy.
template<int n>
inline float Macierz<n>::getElement(int wiersz, int kolumna)
{
	return this->macierz[wiersz][kolumna];
}

template<int n>
inline void Macierz<n>::setElement(int wiersz, int kolumna, float wartosc)
{
	this->macierz[wiersz][kolumna] = wartosc;
}

//3.2) Dostęp do tablicy danej macierzy.
template<int n>
inline float* Macierz<n>::getTablicaMacierzy()
{
	return this->macierz;
}

//3.3) Stworzenie macierzy jednostkowej.
template<int n>
inline Macierz<n> Macierz<n>::stworzMacierzJednostkowa()
{
	Macierz<n> m = Macierz<n>();
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++) {
			if (i == j){
				macierz[i][j] = 1;
			}
			else{
				macierz[i][j] = 0;
			}
		}
	}
	return m;
}

//3.4) Transponowanie macierzy.
template<int n>
float** Macierz<n>::transponujMacierz(float** macierz, int rozmiar)
{
	float** macierzTransponowana;
	macierzTransponowana = new float* [rozmiar];
	for (int i = 0; i < rozmiar; i++)
		macierzTransponowana[i] = new float[rozmiar];

	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < rozmiar; j++) {
			macierzTransponowana[j][i] = macierz[i][j];
		}
	}
	return macierzTransponowana;
}

//3.5) Macierz odwrocona
template<int n>
float** Macierz<n>::obliczMacierzOdwrocona(float** macierz, int rozmiar)
{
	int wyznacznik = obliczWyznacznik(macierz, rozmiar);
	if (wyznacznik == 0) {
		cout << ("Wyznacznik rowny zero. Macierz odwrotna nie istnieje.");
		exit(0);
	}

	float** macierzDopelnien = liczDopelnienie(macierz, rozmiar);
	float** macierzTrans = transponujMacierz(macierzDopelnien, rozmiar);
	float** odwroconaMacierz = odwrocMacierz(macierzTrans, rozmiar, wyznacznik);

	return odwroconaMacierz;
}

//Metody pomocniczne

template<int n>
inline int Macierz<n>::obliczWyznacznik(float** m, int rozmiar)
{
	int wyznacznik = 0;
	float submatrix[rozmiar][rozmiar];

	if (rozmiar == 2){
		return ((m[0][0] * m[1][1]) - (m[1][0] * m[0][1]));
	}
	else {
		for (int x = 0; x < rozmiar; x++) {
			int subi = 0;
			for (int i = 1; i < rozmiar; i++){
				int subj = 0;
				for (int j = 0; j < rozmiar; j++){
					if (j == x)
						continue;
					submatrix[subi][subj] = m[i][j];
					subj++;
				}
				subi++;
			}
			wyznacznik = wyznacznik + (pow(-1, x) * m[0][x] * obliczWyznacznik(submatrix, rozmiar - 1));
		}
	}
	return wyznacznik;
}

template<int n>
inline float** Macierz<n>::liczDopelnienie(float** macierz, int rozmiar)
{
	float** macierzDopelnien;
	macierzDopelnien = new float* [rozmiar];
	for (int i = 0; i < rozmiar; i++)
		macierzDopelnien[i] = new float[rozmiar];

	if (rozmiar == 1){
		macierzDopelnien[0][0] = 1;
		return macierzDopelnien;
	}
	for (int i = 0; i < rozmiar; i++){
		for (int j = 0; j < rozmiar; j++){
			float** nowaMacierz;
			int nowyRozmiar = rozmiar - 1;
			nowaMacierz = new float* [nowyRozmiar];
			for (int o = 0; o < nowyRozmiar; o++){
				nowaMacierz[o] = new float[nowyRozmiar];
			}
			int m = 0, c = 0;
			for (int k = 0; k < rozmiar; k++){
				int c = 0;
				if (k == j) continue;
				for (int l = 0; l < rozmiar; l++){
					if (l == i) continue;
					nowaMacierz[m][c] = macierz[k][l];
					c++;
				}
				m++;
			}
			macierzDopelnien[j][i] = pow(-1, j + i) * obliczWyznacznik(nowaMacierz, nowyRozmiar);
		}
	}
	return macierzDopelnien;
}

template<int n>
float ** Macierz<n>::odwrocMacierz(float** macierz, int rozmiar, int wyznacznik)
{
		float** macierzOdwrotna;
		macierzOdwrotna = new float* [rozmiar];
		for (int i = 0; i < rozmiar; i++){
			macierzOdwrotna[i] = new float[rozmiar];
		}
		for (int i = 0; i < rozmiar; i++){
			for (int j = 0; j < rozmiar; j++){
				if (macierz[i][j] == 0) macierzOdwrotna[i][j] = 0;
				else macierzOdwrotna[i][j] = round((float)macierz[i][j] / wyznacznik * 100) / 100;
			}
		}
		return macierzOdwrotna;
}



