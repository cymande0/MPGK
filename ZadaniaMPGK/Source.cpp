#include "Header.h"

GLuint ProgramMPGK::VAO;
GLuint ProgramMPGK::VBO;
GLuint ProgramMPGK::IBO;
GLuint ProgramMPGK::programZShaderami;
GLuint ProgramMPGK::vertexShaderId;
GLuint ProgramMPGK::fragmentShaderId;
GLint ProgramMPGK::zmiennaShader;

using namespace std;

const int iloscWie = 36;

ProgramMPGK::ProgramMPGK(void)
{
	wysokoscOkna = 768;
	szerokoscOkna = 1024;
	polozenieOknaX = 100;
	polozenieOknaY = 100;
}

ProgramMPGK::ProgramMPGK(int wysokoscOkna, int szerokoscOkna, int polozenieOknaX, int polozenieOknaY)
{
	this->wysokoscOkna = wysokoscOkna;
	this->szerokoscOkna = szerokoscOkna;
	this->polozenieOknaX = polozenieOknaX;
	this->polozenieOknaY = polozenieOknaY;
}

ProgramMPGK::~ProgramMPGK()
{

}

void ProgramMPGK::stworzenieOkna(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(szerokoscOkna, wysokoscOkna);
	glutInitWindowPosition(polozenieOknaX, polozenieOknaY);
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow("Konrad Pieta - MPGK");
}

void ProgramMPGK::inicjalizacjaGlew()
{
	glewExperimental = GL_TRUE;
	GLenum wynik = glewInit();
	if (wynik != GLEW_OK)
	{
		std::cerr << "Nie udalo sie zainicjalizowac GLEW. Blad: " << glewGetErrorString(wynik) << std::endl;
		//system("pause");
		exit(1);
	}
}

void  ProgramMPGK::wyswietl()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	static GLfloat zmiana = 0.0f;
	zmiana += 0.0005f;
	glUniform1f(zmiennaShader, abs(sinf(zmiana)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)(sizeof(GLfloat) * 4));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glutSwapBuffers();
}

void ProgramMPGK::usun()
{
	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);
	glDeleteProgram(programZShaderami);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
	glDeleteVertexArrays(1, &VAO);
}

void ProgramMPGK::stworzenieVAO()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
}

void ProgramMPGK::stworzenieVBO()
{
	//Przyklady
	Wektor<3> w1 = Wektor<3>();
	cout << "Wektor: " << w1 << endl;
	
	Wektor<3> w2 = Wektor<3>(3);
	cout << "Wektor z trojami " << w2 << endl;
	
	Wektor<3> w3 = Wektor<3>(1, 2, 3);
	cout << "Wektor 1: " << w3 << endl;

	cout << "Wektor 1 + Wektor 2: " << w1 + w2 << endl;
	cout << "Wektor 1 - Wektor 2: " << w1 - w2 << endl;
	cout << "Wektor 1 * liczba 3: " << w1 * 3 << endl;

	cout << "Dlugosc wektora 1: " << w1.liczDlugoscWektora() << endl;
	cout << "Iloczyn skalarny wektorow w1 i w2: " << w1.iloczynSkalarny(w1,w2) << endl;
	cout << "Iloczyn wektorowy wektorow w1 i w2: " << w1.iloczynWektorowy(w1,w2) << endl;

	Macierz<3> m1 = Macierz<3>();
	cout << "Macierz domyslna:\n" << m1 << endl;
	Macierz<3> m2 = Macierz<3>(2);
	cout << "Macierz2 (przekatna: 2):\n" << m2 << endl;

	cout << "Dodawanie macierzy 1 i 2:\n" << m1+m2 << endl; 
	cout << "Odejmowanie macierzy 1 i 2:\n" << m1-m2 << endl;
	cout << "Mnozenie Macierz 1 przez skalar:\n" << m1 * 3 << endl;
	cout << "Mnozenie macierzy przez wektor w1:\n" <<m1 * w1 << endl;

	float tablica1[4][4] = { {-0.2f, 0.4f, 0.1f, 1.0f}, {-1.0f, 0.0f, 0.0f, 1.0f}, {-0.4f, -0.4f, 0.4f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f} };
	Macierz<4> m3 = Macierz<4>(tablica1);

	float tablica2[4][4] = { {-0.4f, 0.4f, 0.0f, 2.0f}, {0.0f, 0.0f, 1.0f, 1.0f}, {0.4f, 0.4f, 0.0f, 1.0f}, {0.5f, 0.5f, 0.0f, 1.0f} };
	Macierz<4> m4 = Macierz<4>(tablica2);

	float kat = 30;
	m3 *= Przeksztalcenia<4>().obrocX(kat).getMacierz();
	m4 *= Przeksztalcenia<4>().obrocY(kat).getMacierz();

	GLfloat wierzcholki[] = {
		m1.getElement(0,0), m1.getElement(0,1) ,m1.getElement(0,2), m1.getElement(0,3),
		m1.getElement(1,0), m1.getElement(1,1), m1.getElement(1,2), m1.getElement(1,3),
		m1.getElement(2,0), m1.getElement(2,1), m1.getElement(2,2), m1.getElement(2,3),
		m1.getElement(3,0), m1.getElement(3,1), m1.getElement(3,2), m1.getElement(3,3),
		m2.getElement(0,0), m2.getElement(0,1), m2.getElement(0,2), m2.getElement(0,3),
		m2.getElement(1,0), m2.getElement(1,1), m2.getElement(1,2), m2.getElement(1,3),
		m2.getElement(2,0), m2.getElement(2,1), m2.getElement(2,2), m2.getElement(2,3),
		m2.getElement(3,0), m2.getElement(3,1), m2.getElement(3,2), m2.getElement(3,3),
		m3.getElement(0,0), m3.getElement(0,1) ,m3.getElement(0,2), m3.getElement(0,3),
		m3.getElement(1,0), m3.getElement(1,1), m3.getElement(1,2), m3.getElement(1,3),
		m3.getElement(2,0), m3.getElement(2,1), m3.getElement(2,2), m3.getElement(2,3),
		m3.getElement(3,0), m3.getElement(3,1), m3.getElement(3,2), m3.getElement(3,3),
		m4.getElement(0,0), m4.getElement(0,1), m4.getElement(0,2), m4.getElement(0,3),
		m4.getElement(1,0), m4.getElement(1,1), m4.getElement(1,2), m4.getElement(1,3),
		m4.getElement(2,0), m4.getElement(2,1), m4.getElement(2,2), m4.getElement(2,3),
		m4.getElement(3,0), m4.getElement(3,1), m4.getElement(3,2), m4.getElement(3,3)
	};

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(wierzcholki), wierzcholki, GL_STATIC_DRAW);
}

void ProgramMPGK::stworzenieIBO()
{
	GLuint indeksyTab[] = {
			0, 1, 2, 1, 2, 3,
	};

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeksyTab), indeksyTab, GL_STATIC_DRAW);
}

void ProgramMPGK::stworzenieProgramu()
{
	programZShaderami = glCreateProgram();

	if (programZShaderami == 0)
	{
		std::cerr << "Blad podczas tworzenia programu shaderow." << std::endl;
		//system("pause");
		exit(1);
	}

	const char* vertexShader =
		"	#version 330 core \n																	\
			layout(location=0) in vec4 polozenie; \n												\
			layout(location=1) in vec4 kolorVS; \n													\
			out vec4 kolorFS; \n																	\
			uniform float zmianaShader; \n															\
			void main()			 \n																	\
			{		 \n																				\
				gl_Position = vec4(zmianaShader * polozenie.x, zmianaShader * polozenie.y, zmianaShader * polozenie.z, polozenie.w); \n		\
				kolorFS = kolorVS; \n																\
			}";

	const char* fragmentShader =
		"	#version 330 core \n						\
			out vec4 kolor;	\n							\
			in vec4 kolorFS; \n							\
			void main()	\n								\
			{			\n								\
				kolor = kolorFS;	\n					\
			}";

	vertexShaderId = dodanieDoProgramu(programZShaderami, vertexShader, GL_VERTEX_SHADER);
	fragmentShaderId = dodanieDoProgramu(programZShaderami, fragmentShader, GL_FRAGMENT_SHADER);

	GLint linkowanieOK = 0;
	glLinkProgram(programZShaderami);
	glGetProgramiv(programZShaderami, GL_LINK_STATUS, &linkowanieOK);
	if (linkowanieOK == GL_FALSE) {
		GLint dlugoscLoga = 0;
		glGetProgramiv(programZShaderami, GL_INFO_LOG_LENGTH, &dlugoscLoga);
		std::vector<GLchar> log(dlugoscLoga);
		glGetProgramInfoLog(programZShaderami, dlugoscLoga, NULL, &log[0]);
		std::cerr << "Blad podczas linkowania programu shaderow." << std::endl;
		for (std::vector<GLchar>::const_iterator i = log.begin(); i != log.end(); ++i)
			std::cerr << *i;
		std::cerr << std::endl;
		glDeleteProgram(programZShaderami);
		//system("pause");
		exit(1);
	}

	GLint walidacjaOK = 0;
	glValidateProgram(programZShaderami);
	glGetProgramiv(programZShaderami, GL_VALIDATE_STATUS, &walidacjaOK);
	if (walidacjaOK == GL_FALSE) {
		GLint dlugoscLoga = 0;
		glGetProgramiv(programZShaderami, GL_INFO_LOG_LENGTH, &dlugoscLoga);
		std::vector<GLchar> log(dlugoscLoga);
		glGetProgramInfoLog(programZShaderami, dlugoscLoga, NULL, &log[0]);
		std::cerr << "Blad podczas walidacji programu shaderow." << std::endl;
		for (std::vector<GLchar>::const_iterator i = log.begin(); i != log.end(); ++i)
			std::cerr << *i;
		std::cerr << std::endl;
		glDeleteProgram(programZShaderami);
		//system("pause");
		exit(1);
	}

	glUseProgram(programZShaderami);

	zmiennaShader = glGetUniformLocation(programZShaderami, "zmianaShader");
	if (zmiennaShader == -1)
	{
		std::cerr << "Nie znalezion zmiennej uniform." << std::endl;
		//system("pause");
		exit(1);
	}
}

GLuint ProgramMPGK::dodanieDoProgramu(GLuint programZShaderami, const GLchar* tekstShadera, GLenum typShadera)
{
	GLuint shader = glCreateShader(typShadera);

	// 35633 -> vertex shader, 35632 -> fragment shader
	const GLchar* typShaderaTekst = typShadera == 35633 ? "vertex" : "fragment";

	if (shader == 0) {
		std::cerr << "Blad podczas tworzenia " << typShaderaTekst << " shadera." << std::endl;
		//system("pause");
		exit(0);
	}

	const GLchar* tekstShaderaTab[1];
	tekstShaderaTab[0] = tekstShadera;
	GLint dlugoscShadera[1];
	dlugoscShadera[0] = strlen(tekstShadera);
	glShaderSource(shader, 1, tekstShaderaTab, dlugoscShadera);

	glCompileShader(shader);
	GLint kompilacjaOK = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &kompilacjaOK);
	if (kompilacjaOK == GL_FALSE)
	{
		GLint dlugoscLoga = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &dlugoscLoga);
		std::vector<GLchar> log(dlugoscLoga);
		glGetShaderInfoLog(shader, dlugoscLoga, NULL, &log[0]);
		std::cerr << std::endl;
		std::cerr << "Blad podczas kompilacji " << typShaderaTekst << " shadera." << std::endl;
		std::cerr << std::endl;
		std::cerr << "log: ";
		for (std::vector<GLchar>::const_iterator i = log.begin(); i != log.end(); ++i)
			std::cerr << *i;
		std::cerr << std::endl;
		glDeleteShader(shader);
		//system("pause");
		exit(1);
	}

	glAttachShader(programZShaderami, shader);
	return shader;
}
void ProgramMPGK::sprawdzenieWersji()
{
	std::cout << "Wersja GLEW: " << glewGetString(GLEW_VERSION) << std::endl;
	std::cout << "Wersja VENDOR: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Wersja REDERER: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Wersja GL: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "Wersja GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

int main(int argc, char** argv)
{
	ProgramMPGK obiektMPGK(786, 786, 100, 100);

	obiektMPGK.stworzenieOkna(argc, argv);
	obiektMPGK.inicjalizacjaGlew();
	obiektMPGK.sprawdzenieWersji();
	obiektMPGK.stworzenieVAO();
	obiektMPGK.stworzenieVBO();
	obiektMPGK.stworzenieIBO();
	obiektMPGK.stworzenieProgramu();
	glutDisplayFunc(obiektMPGK.wyswietl);
	glutIdleFunc(obiektMPGK.wyswietl);
	glutCloseFunc(obiektMPGK.usun);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glutMainLoop();

	//system("pause");
	return 0;
}