#ifndef TEXTURAS_H
#define TEXTURAS_H
#include <SOIL/SOIL.h>
#include <GL/freeglut.h>
GLuint  text_sol = 0;
GLuint  text_mercurio = 0;
GLuint  text_venus = 0;
GLuint  text_terra = 0;
GLuint  text_marte = 0;
GLuint  text_netuno = 0;
GLuint  text_jupiter = 0;
GLuint  text_saturno = 0;
GLuint  text_urano = 0;
GLuint  text_fundo = 0; 
GLuint  text_lua = 0;

GLuint carregaTextura(const char* arquivo){
    GLuint id_textura = SOIL_load_OGL_texture(
                                arquivo,
                                SOIL_LOAD_AUTO,
                                SOIL_CREATE_NEW_ID,
                                SOIL_FLAG_INVERT_Y
                                );                                                                                        
    if(id_textura == 0){
        printf("Erro SOIL: %s", SOIL_last_result());
    }

    return id_textura;
}

void defineTexturas(){
	text_sol = carregaTextura("images/sol.png");
	text_venus = carregaTextura("images/venus.png");
	text_mercurio = carregaTextura("images/mercurio.png");
	text_urano = carregaTextura("images/urano.png");
	text_netuno = carregaTextura("images/netuno.png");
	text_saturno = carregaTextura("images/saturno.png");
	text_terra = carregaTextura("images/terra.png");
	text_jupiter = carregaTextura("images/jupiter.png");
	text_marte = carregaTextura("images/marte.png");
	text_lua = carregaTextura("images/lua.png");
	text_fundo = carregaTextura("images/estrelas_fundo.png");
}

#endif 
