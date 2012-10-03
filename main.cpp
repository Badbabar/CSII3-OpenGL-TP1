#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "include/Ship.h"
#include "include/Car.h"
#include "include/Shoot.h"
#include "include/Map.h"
#include "include/Person.h"

// Taille de la fenêtre
#define LARGEUR 1024
#define HAUTEUR 780

#define FRAMES_PER_SECOND 50

#define MAX_PERSONS 15
#define PERSON_SPAWN_TIME 1000

#undef main

using namespace std;

int main(int argc, char *argv[])
{
    // Initialisation du générateur de nombres aléatoires
    srand ( time(NULL) );

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
    Car ship(LARGEUR / 2, HAUTEUR / 2);

    // Tirs
    vector<Shoot *> shoots;

    // Passants
    vector<Person *> persons;

    // Gestion des passants
    Uint32 next_person_time = 0 ; // variable enregistrant le moment du dernier tir
    Uint32 person_now; // heure actuelle

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

                            // Création du tir ici
                            shoots.push_back(ship.Fire());
                        }
                        break;

                    default:

                        break;
                }
                break;

            default:

                break;
        }

        // Images par seconde
        current_time = SDL_GetTicks();
        while (current_time - last_time < (1000/FRAMES_PER_SECOND)) {
            // On se met en pause le temps voulu
            SDL_Delay(1000/FRAMES_PER_SECOND - (current_time - last_time));
            current_time = SDL_GetTicks();
        }

        last_time = SDL_GetTicks();

        // Maj de la voiture
        ship.UpdatePositions(0, LARGEUR, 0, HAUTEUR);

        // Maj des tirs
        for (int i = 0; i < shoots.size(); i++)
        {
            if (shoots[i]->IsOut(0, LARGEUR, 0, HAUTEUR)) {
                delete shoots[i];
                shoots.erase(shoots.begin() + i);
                i--;
            } else {
                shoots[i]->UpdatePositions();
                shoots[i]->Draw();
            }
        }

        // Ajout de passants
        person_now = SDL_GetTicks();
        if ( next_person_time <= person_now ) {
            next_person_time = person_now + PERSON_SPAWN_TIME;

            // Création du passant ici
            persons.push_back(new Person(0, LARGEUR, 0, HAUTEUR));
        }

        // Maj des passants selon collision avec voiture ou balle
        for (int i = 0; i < persons.size(); i++)
        {
            persons[i]->UpdatePositions(0, LARGEUR, 0, HAUTEUR);

            if (persons[i]->IsAlive() && ship.Collision(persons[i]->GetX(), persons[i]->GetY()))
                persons[i]->SetAlive(false);

            if (persons[i]->IsAlive())
                for (int j = 0; j < shoots.size(); j++)
                    if (persons[i]->Collision(shoots[j]->GetX(), shoots[j]->GetY()))
                        persons[i]->SetAlive(false);
        }

        // On efface la fenêtre
        glClear(GL_COLOR_BUFFER_BIT);

        // Dessin de la map
        map.Draw(0, LARGEUR, 0, HAUTEUR);

        // Dessin des tirs
        for (int i = 0; i < shoots.size(); i++) {
            shoots[i]->Draw();
        }

        // Dessin des passants
        for (int i = 0; i < persons.size(); i++)
        {
            persons[i]->Draw();
        }

        // Dessin de la voiture
        ship.Draw();

        // Affichage (en double buffering)
        glFlush();
        SDL_GL_SwapBuffers();
    }

    // Fin du programme
    SDL_Quit();
    return 0;
}
