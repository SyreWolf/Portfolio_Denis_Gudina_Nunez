#include <GL/glut.h>
#include <Windows.h>
#include <MMSystem.h>
#include <iostream>
#include <fstream>
#include <string>
#include "vector3d.h"
#include "solido.h"
#include "cubo.h"
#include "esfera.h"
#include "cilindro.h"
#include "escena.h"
#include "camara.h"
#include "pared.h"
#include "Jugador.h"

//Variable registro del tipo de partida a guardar
int x;
int mx = -1;
int my = -1;
double t = 0;
double dt = 0.1;
//Variable para pausar el gameloop
bool paused = false;

CamaraFPS cam;
//Variables que se van a usar en la partida
Jugador *player;
Bala *bala;
Pelota *pelota;
Pared *pared;

Escena e;

//Getter y setter del registro declarado anteriormente
void setReg(int a) {
	x = a;
}

int getReg() {
	return x;
}

//Metodo que se encarga de leer el archivo de puntuaciones
void read() {
	string line;
	ifstream file("Puntuaciones.txt");
	cout << "\n\nEstas son las ultimas puntuaciones registradas\n" << endl;
	if (file.is_open())
	{
		while (getline(file, line))
		{
			cout << line << '\n';
		}
		file.close();

		cout << "\n\n";
	}
	else {
		cout << "No se puede abrir el archivo";
	}

}

/*El metodo sirve para interpretar el valor de x seleccionado
para así poder guardar el tipo de partida que era a la hora de 
escribir la puntuacion en el fichero*/
string decide(int x) {
	if (x == 1) {
		return "Modo tutorial";
	}
	else if (x == 2) {
		return "Modo facil";
	}
	else if (x == 3) {
		return "Modo medio";
	}
	else if (x == 4) {
		return "Modo dificil";
	}
	else if (x == 5) {
		return "Modo pesadilla";
	}
}

/*Metodo que se encarga de escribir en el fichero
a continuacion de la ultima linea escrita*/
void write(int puntuacion) {
	ofstream file("Puntuaciones.txt", ios::app);
	if (file.is_open())
	{
		file << decide(x) << "----" << puntuacion << endl;
		file.close();
	}
	else cout << "No se puede abrir el archivo";
}

/*Implementacion de un menu sencillo por texto
para elegir el nivel de dificultad, que viene dado
por el nivel de la pelota inicial, dependiendo de una entrada
numerica elegimos el modo indicado generando una pelota con 
un nivel diferente en cada caso*/
void menu(int x) {
	cout << "Selecciona una opcion:\n" << endl;
	cout << "1. Modo tutorial - Pelota de nivel 1" << endl;
	cout << "2. Modo facil - Pelota de nivel 2" << endl;
	cout << "3. Modo medio - Pelota de nivel 4" << endl;
	cout << "4. Modo dificil - Pelota de nivel 7" << endl;
	cout << "5. Modo pesadilla - Pelota de nivel 10" << endl;
	cout << "6. Registro de puntuaciones de partidas anteriores" << endl;
	cout << "\n\nControles:\n\nMovimiento - A,D\nDisparar - Barra Espaciadora\nSalir - ESC\nPausa - P" << endl;
	cout << "Movimiento de camara - T,G\nGirar camara - Movimiento de raton manteniendo pulsado click izquierdo\n\n" << endl;

	cout << "Has elegido la opcion: " << endl;
	cin >> x;

	while (x != 1 && x != 2 && x != 3 && x != 4 && x != 5 && x != 6) {
		cout << "Entrada incorrecta, vuelve a intentarlo" << endl;
		cin >> x;
	}

	if (x == 1) {
		//Se inicializa la pelota y se añade a la escena
		pelota = new Pelota();
		pelota->setPos(Vector3D(0, 12, 0));
		pelota->setVel(Vector3D(1, 0, 0));
		pelota->setCol(Vector3D(0, 1, 0));
		pelota->setF(Vector3D(0, -0.98, 0));
		pelota->setLevel(1);
		pelota->setM(1);
		pelota->setR(1);
		pelota->setType("pelota");
		//e.addSolidos(pelota);
		e.add(pelota);
		setReg(x);
	}
	else if (x == 2) {
		//Se inicializa la pelota y se añade a la escena
		pelota = new Pelota();
		pelota->setPos(Vector3D(0, 12, 0));
		pelota->setVel(Vector3D(1, 0, 0));
		pelota->setCol(Vector3D(0, 1, 0));
		pelota->setF(Vector3D(0, -0.98, 0));
		pelota->setLevel(2);
		pelota->setM(1);
		pelota->setR(1);
		pelota->setType("pelota");
		//e.addSolidos(pelota);
		e.add(pelota);
		setReg(x);
	}
	else if (x == 3) {
		//Se inicializa la pelota y se añade a la escena
		pelota = new Pelota();
		pelota->setPos(Vector3D(0, 12, 0));
		pelota->setVel(Vector3D(1, 0, 0));
		pelota->setCol(Vector3D(0, 1, 0));
		pelota->setF(Vector3D(0, -0.98, 0));
		pelota->setLevel(4);
		pelota->setM(1);
		pelota->setR(1);
		pelota->setType("pelota");
		//e.addSolidos(pelota);
		e.add(pelota);
		setReg(x);
	}
	else if (x == 4) {
		//Se inicializa la pelota y se añade a la escena
		pelota = new Pelota();
		pelota->setPos(Vector3D(0, 12, 0));
		pelota->setVel(Vector3D(1, 0, 0));
		pelota->setCol(Vector3D(0, 1, 0));
		pelota->setF(Vector3D(0, -0.98, 0));
		pelota->setLevel(7);
		pelota->setM(1);
		pelota->setR(2.5);
		pelota->setType("pelota");
		//e.addSolidos(pelota);
		e.add(pelota);
		setReg(x);
	}
	else if (x == 5) {
		//Se inicializa la pelota y se añade a la escena
		pelota = new Pelota();
		pelota->setPos(Vector3D(0, 12, 0));
		pelota->setVel(Vector3D(1, 0, 0));
		pelota->setCol(Vector3D(0, 1, 0));
		pelota->setF(Vector3D(0, -0.98, 0));
		pelota->setLevel(10);
		pelota->setM(1);
		pelota->setR(3);
		pelota->setType("pelota");
		//e.addSolidos(pelota);
		e.add(pelota);
		setReg(x);
	}
	else if (x == 6) {
		//Llamada al metodo de lectura y de nuevo al menu
		read();
		menu(x);
	}
}

void displayMe(void) {
	/* Borrar pantalla*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/* Inicializar transformaciones*/
	glLoadIdentity();

	/* Camara */
	cam.render();

	/* Luces */
	GLfloat lightpos[] = { 5.0,15.0,5.0,0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

	/* Visualiza escena */
	e.render();

	/* Mostrar Buffer*/
	glutSwapBuffers();
}
void mouseMoved(int x, int y)
{
	if (!paused) {
		if (mx >= 0 && my >= 0) {
			//pitch += y - my;
			//yaw += x - mx;
			Vector3D r;
			r = cam.getRot() + Vector3D(y - my, x - mx, 0);
			cam.setRot(r);
		}
		mx = x;
		my = y;
		glutPostRedisplay();
	}
}
void mousePress(int button, int state, int x, int y)
{
	if (!paused) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			mx = x;
			my = y;
		}
		if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
			mx = -1;
			my = -1;
		}
	}
}
void keyPressed(unsigned char key, int px, int py) {
	Vector3D vp;
	double x;
	switch (key) {
	case 't':
	case 'T':
		if (!paused){
			cam.update(dt * 2);
		}
		
		break;
	case 'g':
	case 'G':
		if (!paused) {
			cam.update(-dt * 2);
		}
		break;
		/*Caso para mover a la izquierda, hace un update después
		para evitar el lag del programa, dado que mientras se mueve el resto
		no actualiza*/
	case 'a':
	case 'A':
		if (!paused) {
			if (player->getPos().getX() >= -14) {
				player->setPos(player->getPos() - Vector3D(3, 0, 0) * dt * 2);

				e.update(dt);
			}
			else {
				e.update(dt);
			}
		}
		break;
		/*Caso para mover a la derecha, hace un update después
		para evitar el lag del programa, dado que mientras se mueve el resto
		no actualiza*/
	case 'd':
	case 'D':
		if (!paused) {
			if (player->getPos().getX() <= 14) {
				player->setPos(player->getPos() - Vector3D(-3, 0, 0) * dt * 2);

				e.update(dt);
			}
			else {
				e.update(dt);
			}
		}
		break;
		//Comando para mostrar por consola la puntuacion actual
	case 'e':
	case 'E':
		cout << player->getScore() << " puntos" << endl;
		break;
		//Comando para la pausa, pone a true un bool
	case 'p':
	case 'P':
		cout << "Pulse P para continuar" << endl;
		paused = !paused;
		break;
		/*Caso para el disparo, pone en movimiento la bala,
		añade un sonido asincrono y lanza la bala*/
	case 32:
		if (!paused) {
			if (bala->isMoving() == false) {
				PlaySound(TEXT("Disparo.wav"), NULL, SND_ASYNC);
				bala->setMoving(true);
				bala->setCol(Vector3D(1, 0, 1));
				bala->setPos(player->getPos() + Vector3D(0, 1, 0));
				bala->setVel(Vector3D(0, 7, 0));
				cout << "Bala disparada" << endl;
			}
			e.update(dt);
		}
		break;
		//Caso para salir, con escape se puede detener la ejecucion
	case 27:
		exit(0);
		break;
	}
	glutPostRedisplay(); //request display() call ASAP
}
void init(void) {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	cam.setPos(Vector3D(0, 5, 20));

	//Se inicializa el jugador y se añade a la escena
	player = new Jugador();
	player->setPos(Vector3D(0, 1, 0));
	player->setVel(Vector3D(0, 0, 0));
	player->setCol(Vector3D(1, 0, 0));
	player->setS(1.0f);
	player->setScore(0);
	player->setHit(false);
	player->setMuerto(false);
	player->setType("jugador");
	//e.addSolidos(player);
	e.setJugador(player);

	//Se inicializa la bala y se añade a la escena
	bala = new Bala();
	bala->setPos(Vector3D(0, -20, 0));
	bala->setVel(Vector3D(0, 0, 0));
	bala->setCol(Vector3D(0, 0, 0));
	bala->setR(0.35);
	bala->setM(1);
	bala->setF(1);
	bala->setHit(false);
	bala->setType("bala");
	//e.addSolidos(bala);
	e.setBala(bala);

	//Se inicializan las paredes y se añaden a la escena
	pared = new Pared(1, 18, 1);
	pared->setPos(Vector3D(-16, 0, 0));
	pared->setVertical(true);
	pared->setType("izquierda");
	//e.addSolidos(pared);
	e.add(pared);
	pared = new Pared(1, 18, 1);
	pared->setPos(Vector3D(16, 0, 0));
	pared->setVertical(true);
	pared->setType("derecha");
	//e.addSolidos(pared);
	e.add(pared);
	pared = new Pared(33, 1, 1);
	pared->setPos(Vector3D(0, -1, 0));
	//e.addSolidos(pared);
	e.add(pared);
	pared = new Pared(33, 1, 1);
	pared->setPos(Vector3D(0, 18, 0));
	//e.addSolidos(pared);
	e.add(pared);
}

void reshape(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, (GLfloat)width / (GLfloat)height, 1.0f, 200.0f);
	glMatrixMode(GL_MODELVIEW);
}

void idle(void) {
	/*En caso de que no este pausado el juego
	y que el jugador no este muerto se realiza
	el idle sin problemas. Si el jugador muere se
	cierra el programa, si el programa se pausa
	la ejecucion del programa no actualiza el juego*/
	if (!paused) {
		if (player->isMuerto() != true) {
			t += dt;
			e.update(dt);
			displayMe();
			if (e.getPelotas().size() == 0) {
				cout << "¡Has Ganado!" << endl;
				//Se guarda en fichero la puntuacion y el modo de juego
				write(player->getScore());
				exit(0);
				delete &e;
			}
		}
		else {
			cout << "¡Has Perdido!" << endl;
			//Se guarda en fichero la puntuacion y el modo de juego
			write(player->getScore());
			exit(0);
			delete &e;
		}
	}
	
	//glutPostRedisplay() ;
}

int main(int argc, char** argv) {
	/*Se inicia primero el menu, que
	nos obliga a seleccionar un modo de dificultad*/
	menu(x);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(600, 600);                    // window size
	glutInitWindowPosition(500, 200);                // distance from the top-left screen
	glutCreateWindow("Bubble Trouble");    // message displayed on top bar window
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(displayMe);
	glutKeyboardFunc(keyPressed);
	glutMotionFunc(mouseMoved);
	glutMouseFunc(mousePress);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}
