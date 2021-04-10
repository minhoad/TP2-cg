#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "texturas.h"
#include<stdbool.h>

GLfloat angle, fAspect, rotX, rotY;
GLdouble obsX, obsY, obsZ;
GLint especMaterial;
GLuint planetas[15];
int movimento = 1;

double aceleracao = 0;
double aceleracao_lua = 0;
bool flag_camera = false;
bool verificaIluminacao = true;
bool desenharOrbitas = false;
bool flag_atualiza_posicao = true;


void DefineIluminacao (){
        GLfloat luzAmbiente[4]={0.4,0.4,0.4,1.0}; 
        GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};         
        GLfloat luzEspecular[4]={1.0, 1.0,1.0, 1.0};	
        GLfloat posicaoLuz[4]={2.67,2.67, 15.76, 1.0};
 
        GLfloat especularidade[4]={0.8,0.8,0.8,1.0}; 
        GLint especMaterial = 100 ;
 
        glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
    
        glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

        glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
        glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
        glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );   
}
void PosicionaObservador(){
	glMatrixMode(GL_MODELVIEW);// Especifica o sistema de coordenadas do modelo
	
	glLoadIdentity();
	
	glTranslatef(-obsX*0.5,-obsY*0.5,-obsZ*0.5);// Especifica a posicao 
	glRotatef(rotX,1,0,0);//do observador(camera)
	glRotatef(rotY,0,1,0);//e do alvo
}

void carregaPlanetas(){
	for(int i = 1; i <11; i++)planetas[i] = glGenLists(i);
	GLUquadric *qobj = gluNewQuadric();
	//Mercurio
	glNewList(planetas[1], GL_COMPILE);	
		gluQuadricTexture(qobj,GL_TRUE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,text_mercurio);
		gluSphere(qobj,1,50,50);
		glDisable(GL_TEXTURE_2D);
	glEndList();
	//Venus
	glNewList(planetas[2], GL_COMPILE);
		gluQuadricTexture(qobj,GL_TRUE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,text_venus);
		gluSphere(qobj,1.61,50,50);
		glDisable(GL_TEXTURE_2D);
	glEndList();
	//Lua
	glNewList(planetas[10], GL_COMPILE);
		gluQuadricTexture(qobj,GL_TRUE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,text_lua);
		gluSphere(qobj,0.4,50,50);
		glDisable(GL_TEXTURE_2D);
	glEndList();
	//Terra
	glNewList(planetas[3], GL_COMPILE);
		gluQuadricTexture(qobj,GL_TRUE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,text_terra);
		gluSphere(qobj,1.73,50,50);
		glDisable(GL_TEXTURE_2D);
	glEndList();
	//Marte
	glNewList(planetas[8], GL_COMPILE);
		gluQuadricTexture(qobj,GL_TRUE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,text_marte);
		gluSphere(qobj,0.9,50,50);
		glDisable(GL_TEXTURE_2D);
	glEndList();
	//Jupiter
	glNewList(planetas[4], GL_COMPILE);
		gluQuadricTexture(qobj,GL_TRUE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,text_jupiter);
		gluSphere(qobj,3.34,50,50);
		glDisable(GL_TEXTURE_2D);
	glEndList();
	//Saturno
	glNewList(planetas[5], GL_COMPILE);
		gluQuadricTexture(qobj,GL_TRUE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,text_saturno);
		gluSphere(qobj,2.95,50,50);
		glDisable(GL_TEXTURE_2D);
	glEndList();
	//Urano
	glNewList(planetas[6], GL_COMPILE);
		gluQuadricTexture(qobj,GL_TRUE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,text_urano);
		gluSphere(qobj,1.10,50,50);
		glDisable(GL_TEXTURE_2D);
	glEndList();
	//Netuno
	glNewList(planetas[7], GL_COMPILE);
		gluQuadricTexture(qobj,GL_TRUE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,text_netuno);
		gluSphere(qobj,1.06,50,50);
		glDisable(GL_TEXTURE_2D);
	glEndList();
	//Fundo é uma esfera para dar profundidade
	glNewList(planetas[9], GL_COMPILE);
		gluQuadricTexture(qobj,GL_TRUE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,text_fundo);
		gluSphere(qobj,500,50,50);
		glDisable(GL_TEXTURE_2D);
	glEndList();

}

void desenhaOrbitas(){
	glColor3f(1,1,1);
	glBegin(GL_LINE_LOOP);
		for(int i=0;i<1000+1;i++)glVertex3f(13.75*-cos(0.1*3.14*i/10), 0, 13.75*sin(0.1*3.14*i/10));
	glEnd();
	glBegin(GL_LINE_LOOP);
		for(int i=0;i<1000+1;i++)glVertex3f(17.36*-cos(0.1*3.14*i/10), 0, 17.36*sin(0.1*3.14*i/10));
	glEnd();
	glBegin(GL_LINE_LOOP);
		for(int i=0;i<1000+1;i++)glVertex3f(23.68*-cos(0.1*3.14*i/10), 0, 23.68*sin(0.1*3.14*i/10));
	glEnd();
	glBegin(GL_LINE_LOOP);
		for(int i=0;i<1000+1;i++)glVertex3f(30.85*-cos(0.1*3.14*i/10), 0, 30.85*sin(0.1*3.14*i/10));
	glEnd();
	glBegin(GL_LINE_LOOP);
		for(int i=0;i<1000+1;i++)glVertex3f(58.29*-cos(0.1*3.14*i/10), 0, 58.29*sin(0.1*3.14*i/10));
	glEnd();
	glBegin(GL_LINE_LOOP);
		for(int i=0;i<1000+1;i++)glVertex3f(102.9*-cos(0.1*3.14*i/10), 0, 102.9*sin(0.1*3.14*i/10));
	glEnd();
	glBegin(GL_LINE_LOOP);
		for(int i=0;i<1000+1;i++)glVertex3f(195.05*-cos(0.1*3.14*i/10), 0, 195.05*sin(0.1*3.14*i/10));
	glEnd();
	glBegin(GL_LINE_LOOP);
		for(int i=0;i<1000+1;i++)glVertex3f(358.01*-cos(0.1*3.14*i/10), 0, 358.01*sin(0.1*3.14*i/10));
	glEnd();
	glFlush();

}

void desenhaMinhaCena(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glColor3f(1, 1, 1);

	//Desenha Fundo
	glPushMatrix();
		glRasterPos2f(0,-2.8);
		glBindTexture(GL_TEXTURE_2D,text_fundo);
		glTranslated(0,0,0);
		glCallList(planetas[9]);
	glPopMatrix();

	//Sol
	GLUquadric *qobj = gluNewQuadric();
	gluQuadricTexture(qobj,GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,text_sol);
	glPushMatrix();
	glTranslated(0,0,0);
	glRotated(-2.5*aceleracao, 0, 1, 0);
	glRotatef(90, -1, 0, 0);
		gluSphere(qobj,6.95,100,100);
		if(verificaIluminacao){
	
			DefineIluminacao();
			glEnable(GL_LIGHT0);
		}else{
			glDisable(GL_LIGHT0);
		}	
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	DefineIluminacao();
	//Mercurio
	glPushMatrix();
		glRasterPos2f(0,-2.8);
		glBindTexture(GL_TEXTURE_2D,text_mercurio);
		glTranslated(13.75*-cos(aceleracao*0.3),0, 13.75*-sin(aceleracao*0.3));
		glRotated(-20*aceleracao, 0, 1, 0);
		glRotatef(90, -1, 0, 0);
		glCallList(planetas[1]);
	glPopMatrix();

	//Venus
	glPushMatrix();
		
		glRasterPos2f(0,-2.8);
		glBindTexture(GL_TEXTURE_2D,text_venus);
		glTranslated(17.36*-cos(aceleracao*0.1),0, 17.36*-sin(aceleracao*0.1));
		glRotated(-20*aceleracao, 0, 1, 0);
		glRotatef(90, -1, 0, 0);
		glCallList(planetas[2]);
	glPopMatrix();
 
	//Terra
	glPushMatrix();
		glRasterPos2f(0,-2.8);
		glBindTexture(GL_TEXTURE_2D,text_terra);
		glTranslated(23.68*-cos(aceleracao*0.088),0, 23.68*-sin(aceleracao*0.088));
		glRotated(-20*aceleracao, 0, 1, 0);
        	glRotatef(90, -1, 0, 0);
		glCallList(planetas[3]);
		// Lua
		glPushMatrix();
				glRasterPos2f(0,-2.8);
				glBindTexture(GL_TEXTURE_2D, text_lua);
				glTranslated(2*-cos(aceleracao_lua*0.088),0, 2*-sin(aceleracao_lua*0.088));
				glRotated(-20*aceleracao, 0, 1, 0);
				glRotatef(90, -1, 0, 0);
				glCallList(planetas[10]);
		glPopMatrix();
	glPopMatrix();
	//Marte
	glPushMatrix();
		glRasterPos2f(0,-2.8);
		glBindTexture(GL_TEXTURE_2D,text_marte);
		glTranslated(30.85*-cos(aceleracao*0.040),0, 30.85*-sin(aceleracao*0.040));
		glRotated(-20*aceleracao, 0, 1, 0);
		glRotatef(90, -1, 0, 0);
		glCallList(planetas[8]);
	glPopMatrix();
	//Jupiter
	glPushMatrix();
		glRasterPos2f(0,-2.8);
		glBindTexture(GL_TEXTURE_2D,text_jupiter);
		glTranslated(58.29*-cos(aceleracao*0.035),0, 58.29*-sin(aceleracao*0.035));
		glRotated(-20*aceleracao, 0, 1, 0);
		glRotatef(90, -1, 0, 0);
		glCallList(planetas[4]);
	glPopMatrix();
	//Saturno
	glPushMatrix();
		glRasterPos2f(0,-2.8);
		glBindTexture(GL_TEXTURE_2D,text_saturno);
		glTranslated(102.9*-cos(aceleracao*0.027),0,102.9*-sin(aceleracao*0.027));
		glRotated(-20*aceleracao, 0, 1, 0);
		glRotatef(90, -1, 0, 0);
		glCallList(planetas[5]);
	glPopMatrix();
	//Urano
	glPushMatrix();
		glRasterPos2f(0,-2.8);
		glBindTexture(GL_TEXTURE_2D,text_urano);
		glTranslated(195.05*-cos(aceleracao*0.02),0, 195.05*-sin(aceleracao*0.02));
		glRotated(-20*aceleracao, 0, 1, 0);
		glRotatef(90, -1, 0, 0);
		glCallList(planetas[6]);
	glPopMatrix();
	//Netuno
	glPushMatrix();
		glRasterPos2f(0,-2.8);
		glBindTexture(GL_TEXTURE_2D,text_netuno);
		glTranslated(358.01*-cos(aceleracao*0.01),0, 358.01*-sin(aceleracao*0.01));
		glRotated(-20*aceleracao, 0, 1, 0);
		glRotatef(90, -1, 0, 0);
		glCallList(planetas[7]);
	glPopMatrix();
	if(desenharOrbitas)desenhaOrbitas();
	glutSwapBuffers();
}

void rotaciona(){
	if(flag_atualiza_posicao){
		aceleracao += .05f;
		aceleracao_lua += .5f;
	}
	glutPostRedisplay();
}

void TeclaPressionada(unsigned char key, int x, int y){
	switch(key){
	    	case 27:	// ESC
	    		exit(0);
	    		break;

	    	case 'p':	
		case 'P':
	    		flag_atualiza_posicao = !flag_atualiza_posicao;
		    	break;
		case 'c':
		case 'C':
			if(!flag_camera){	
				rotX = 100;
				rotY = 15;
				obsZ = 400;
				flag_camera = !flag_camera;
				
			}else{
				rotX = rotY = 0;
				obsX = obsY = 0;
				obsZ = 400; 	
				flag_camera = !flag_camera;
				
			}
        		break;	
		case 'l':
		case 'L':
			verificaIluminacao = !verificaIluminacao;
			break;
		case 'o': 
		case 'O':
			desenharOrbitas = !desenharOrbitas;
			break;
			
	}
	PosicionaObservador();
	
	glutPostRedisplay();
}

void GerenciaMouse(int button, int state, int x, int y){
	switch(button){
		case GLUT_LEFT_BUTTON:// dando zoom
			if(state == GLUT_DOWN){
				if(angle >= 10)angle -= 5;
			}
			break;
		case GLUT_RIGHT_BUTTON:// tirando o zoom
			if(state == GLUT_DOWN){
				if(angle <= 160)angle += 5;
			}
			break;
	}
	
	glMatrixMode(GL_PROJECTION);// Especifica o sistema de coordenadas de projecao
	
	glLoadIdentity();
	
	gluPerspective(angle,fAspect,0.5,800);//projecao perspectiva(angulo,aspecto,zMin,zMax)

	PosicionaObservador();
	
	glutPostRedisplay();
}

void TeclaIPressionada(int tecla, int x, int y){
	switch(tecla){
		case GLUT_KEY_LEFT:	
			rotY -= 2;
			break;
		case GLUT_KEY_RIGHT:
			rotY += 2;	
			break;
		case GLUT_KEY_UP:	rotX++;
							break;
		case GLUT_KEY_DOWN:	rotX--;
							break;
		case GLUT_KEY_F1:	obsZ++;
							break;
		case GLUT_KEY_F2:	obsZ--;
							break;					
	}
	PosicionaObservador();
	 
	glutPostRedisplay();
}

void reshape(GLsizei w, GLsizei h){
	if ( h == 0 ) h = 1;// Para previnir uma divisao por zero

	glViewport(0, 0, w, h);

	fAspect = (GLfloat)w/(GLfloat)h;

	// Especifica o sistema de coordenadas de projecao
	glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity();

	// projeção perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(angle,fAspect,0.5,800);

	PosicionaObservador();
}


void setup(){
	especMaterial = 150;
	glEnable (GL_TEXTURE_2D);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);       
        glEnable(GL_COLOR_MATERIAL);      
        glEnable(GL_LIGHTING);  
        glEnable(GL_LIGHT0);
        glEnable(GL_DEPTH_TEST);
      	glShadeModel(GL_FLAT);
	angle = 100;
    	defineTexturas();
    	carregaPlanetas();
        rotX = 0;
        rotY = 0;
        obsX=obsY=0;
        obsZ = 400;
}
int main(int argc, char** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
    	glutInitWindowPosition(5,5);
	glutInitWindowSize(1280,800);
	glutCreateWindow("Sistema Solar");
	glutDisplayFunc(desenhaMinhaCena);
	glutSpecialFunc(TeclaIPressionada);
	glutKeyboardFunc(TeclaPressionada);
    	glutReshapeFunc(reshape);
	glutMouseFunc(GerenciaMouse);
	glutIdleFunc(rotaciona);
	setup();
	glutMainLoop();
	return 0;
}
