#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>

#include "include/Ship.h"
#include "include/Shoot.h"
#include "include/Map.h"

// Taille de la fenêtre
#define LARGEUR 1024
#define HAUTEUR 780

#define FRAMES_PER_SECOND 50

#undef main

using namespace std;

int main(int argc, char *argv[])
{
    // Initialisation de SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Création de la surface d'affichage qui est en OpenGL
    // (changez le titre si besoin)
    SDL_WM_SetCaption("Spaceship",NULL);
    SDL_Surface* ecran = SDL_SetVideoMode(LARGEUR, HAUTEUR, 32, SDL_OPENGL);

    // Initialisation de l'affichage OpenGL
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    gluOrtho2D(0,LARGEUR,0,HAUTEUR); // Taille de l'écran
    SDL_Flip(ecran);

    // Boucle d'évènements
    bool continuer = true;

    SDL_Event event;
    SDL_EnableKeyRepeat(10,10); // Activation de la répétition de touches

    // Gestion des images par seconde
    Uint32 last_time = SDL_GetTicks(); // heure actuelle, derniere mise à jour
    Uint32 current_time;

    // Gestion des tirs par seconde
    Uint32 next_shoot_time = 0 ; // variable enregistrant le moment du dernier tir
    Uint32 shoot_now; // heure actuelle

    // Vaisseau
    Ship ship(300, 200);

    // Tirs
    vector<Shoot> shoots;

    // Carte
    Map map;

    while (continuer)
    {
        SDL_PollEvent(&event);
        // Selon le type d'evt, on choisi quoi faire
        switch(event.type)
        {
            case SDL_QUIT: // fin
                continuer = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_RIGHT:
                        ship.DecrementAngle();
                        break;
                    case SDLK_LEFT:
                        ship.IncrementAngle();
                        break;
                    case SDLK_UP:
                        ship.IncrementSpeed();
                        break;
                    case SDLK_DOWN:
                        ship.DecrementSpeed();
                        break;
                    case SDLK_SPACE:
                        // Si on a 100ms depuis le dernier tir
                        shoot_now = SDL_GetTicks();
                        if ( next_shoot_time <= shoot_now ) {
                            next_shoot_time = shoot_now + 100;
                            // création du tir ici
                            Shoot shoot(ship.GetX(), ship.GetY(), ship.GetAngle());
                            shoots.push_back(shoot);
                        }
                        break;
                }
                break;
        }

        current_time = SDL_GetTicks();
        while (current_time - last_time < (1000/FRAMES_PER_SECOND)) {
            // On se met en pause le temps voulu
            SDL_Delay(1000/FRAMES_PER_SECOND - (current_time - last_time));
            current_time = SDL_GetTicks();
        }

        last_time = SDL_GetTicks();

        // On efface la fenêtre
        glClear(GL_COLOR_BUFFER_BIT);

        map.Draw(0, LARGEUR, 0, HAUTEUR);

        ship.UpdatePositions(0, LARGEUR, 0, HAUTEUR);
        ship.Draw();

        for (int i = 0; i < shoots.size(); i++)
        {
            if (shoots[i].IsOut(0, LARGEUR, 0, HAUTEUR)) {
                //delete &shoots[i];
                shoots.erase(shoots.begin() + i);
                i--;
            } else {
                shoots[i].UpdatePositions();
                shoots[i].Draw();
            }
        }

        // Affichage (en double buffering)
        glFlush();
        SDL_GL_SwapBuffers();
    }

    // Fin du programme
    SDL_Quit();
    return 0;
}
