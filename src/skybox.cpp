#include "../include/skybox.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"
#include <stdio.h>

GLuint genSkybox(){
    char* extensions = (char*) glGetString(GL_EXTENSIONS); 
    if(strstr(extensions, "GL_ARB_texture_cube_map") != NULL){
        // Liste des faces successives pour la création des textures de CubeMap
        GLenum cube_map_target[6] = {           
            GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB, //Left
            GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB, //Right
            GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB, //Bottom
            GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB, //Top
            GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB, //Front
            GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB  //Back
        };
        
        // Chargement des six textures
        IMG* texture_image[6];
        const char* image_paths[6] = {
            "./maps/sky/lf.png",
            "./maps/sky/rt.png",
            "./maps/sky/dn.png",
            "./maps/sky/up.png",
            "./maps/sky/ft.png",
            "./maps/sky/bk.png",
        };

        for (int i = 0; i < 6; i++){
            texture_image[i] = new IMG();
            texture_image[i]->data = stbi_load(image_paths[i], &texture_image[i]->width, &texture_image[i]->height, nullptr, 0);
        }
        
        // Génération d'une texture CubeMap
        GLuint cube_map_texture_ID;
        glGenTextures(1, &cube_map_texture_ID);
        
        // Configuration de la texture
        glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, cube_map_texture_ID);
        
        for (int i = 0; i < 6; i++)
        {
            glTexImage2D(cube_map_target[i], 0, 3, texture_image[i]->height, texture_image[i]->width, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_image[i]->data);
        
            if (texture_image[i])                
            {
                if (texture_image[i]->data)    
                {
                    free(texture_image[i]->data);    
                }
                free(texture_image[i]);    
            }
        }
        
        glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP);

        return cube_map_texture_ID;

    } 
    else{
        printf("Erreur d'affichage");
    }
}

void drawSkyBox(GLuint textId){
    // Taille du cube
    float t = 1000.0f;
    glColor3f(1.,1.,1.);
    glEnable(GL_TEXTURE_CUBE_MAP_ARB); 
    
    // Utilisation de la texture CubeMap
    glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, textId);
    
    // Rendu de la géométrie
    glBegin(GL_TRIANGLE_STRIP);            // X Négatif        
        glTexCoord3f(-t,-t,-t); glVertex3f(-t,-t,-t);     
        glTexCoord3f(-t,t,-t); glVertex3f(-t,t,-t);
        glTexCoord3f(-t,-t,t); glVertex3f(-t,-t,t);
        glTexCoord3f(-t,t,t); glVertex3f(-t,t,t);
    glEnd();
    
    glBegin(GL_TRIANGLE_STRIP);            // X Positif
        glTexCoord3f(t, -t,-t); glVertex3f(t,-t,-t);
        glTexCoord3f(t,-t,t); glVertex3f(t,-t,t);
        glTexCoord3f(t,t,-t); glVertex3f(t,t,-t); 
        glTexCoord3f(t,t,t); glVertex3f(t,t,t);     
    glEnd();
    
    glBegin(GL_TRIANGLE_STRIP);            // Y Négatif    
        glTexCoord3f(-t,-t,-t); glVertex3f(t,-t,t);
        glTexCoord3f(-t,-t,t); glVertex3f(-t,-t,t);
        glTexCoord3f(t, -t,-t); glVertex3f(t,-t,-t);
        glTexCoord3f(t,-t,t); glVertex3f(-t,-t,-t);
    glEnd();
    
    glBegin(GL_TRIANGLE_STRIP);            // Y Positif        
        glTexCoord3f(-t,t,-t); glVertex3f(t,t,t);
        glTexCoord3f(t,t,-t); glVertex3f(t,t,-t); 
        glTexCoord3f(-t,t,t); glVertex3f(-t,t,t);
        glTexCoord3f(t,t,t); glVertex3f(-t,t,-t);     
    glEnd();
    
    glBegin(GL_TRIANGLE_STRIP);            // Z Négatif        
        glTexCoord3f(-t,-t,-t); glVertex3f(-t,-t,-t);
        glTexCoord3f(t, -t,-t); glVertex3f(t,-t,-t);
        glTexCoord3f(-t,t,-t); glVertex3f(-t,t,-t);
        glTexCoord3f(t,t,-t); glVertex3f(t,t,-t); 
    glEnd();
    
    glBegin(GL_TRIANGLE_STRIP);            // Z Positif    
        glTexCoord3f(-t,-t,t); glVertex3f(-t,-t,t);
        glTexCoord3f(-t,t,t); glVertex3f(-t,t,t);
        glTexCoord3f(t,-t,t); glVertex3f(t,-t,t);
        glTexCoord3f(t,t,t); glVertex3f(t,t,t);     
    glEnd();
    
    glDisable(GL_TEXTURE_CUBE_MAP_ARB); 
    // Réinitialisation de la matrice ModelView
}
