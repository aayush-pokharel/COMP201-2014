#include "view.h"

using namespace std;

// Initialize SDL
View::View(string title, int width, int height) {
    fail = false;
    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0) {
        fail = true;
        return;
    }
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fail = true;
        return;
    }
    // Get the screen
    screen = SDL_GetWindowSurface(window);
    //Initialize JPEG and PNG loading
    if( !( IMG_Init( IMG_INIT_JPG|IMG_INIT_PNG ) & (IMG_INIT_JPG|IMG_INIT_PNG) ) ) {
        fail = true;
        return;
    }
    //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
        fail = true;
        return;
    }

    // Initialize True type fonts
    if( TTF_Init() == -1 ) {
        return;
    }

    // Load assets
    snake = load("assets/snake.png");
    music = Mix_LoadMUS("assets/2Inventions_-_Johaness_Gilther_-_Don_t_leave_me.mp3");
    if (music != NULL) {
        Mix_PlayMusic( music, -1 );
    }
    food = Mix_LoadWAV("assets/yummy.wav");
    dead = Mix_LoadWAV("assets/nooo.wav");
    font = TTF_OpenFont( "assets/LiberationSans-Regular.ttf", 28 );
}

View::~View() {
    TTF_CloseFont( font );
    TTF_Quit();
    Mix_FreeMusic(music);
    Mix_FreeChunk(food);
    Mix_FreeChunk(dead);
    SDL_FreeSurface(snake);
    SDL_FreeSurface(text);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

/**
 *  Load an image from a file to a SDL_Surface
 */
SDL_Surface* View::load(char * path) {
    // Load image
    SDL_Surface* optimizedSurface = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path );
    if( loadedSurface == NULL ) {
        return NULL;
    }
    // Convert surface to screen format
    optimizedSurface = SDL_ConvertSurface( loadedSurface, screen->format, 0 );

    // Get rid of old loaded surface
    SDL_FreeSurface( loadedSurface );

    return optimizedSurface;
}

void View::show(Model * model) {

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,
        0x03, 0x3A, 0x01));

    SDL_Rect dest;
    char letter;
    for (int i = 0; i < model->getHeight(); i++) {
        for (int j = 0; j < model->getWidth(); j++) {
    if (model->eating()) {
        Mix_PlayChannel( -1, food, 0 );
    }
    if (model->gameOver()) {
        Mix_PlayChannel( -1, dead, 0 );
    }
    

            SDL_BlitSurface( letters[letter], NULL, screen, &dest );
        }
    }

    
    SDL_Color textColor = { 255, 255, 255 };
    text = TTF_RenderText_Solid( font, "Playing: Johaness Gilther - Don't leave me", textColor );
    dest.x = 10;
    dest.y = 730;
    SDL_BlitSurface( text, NULL, screen, &dest );
    SDL_UpdateWindowSurface(window);
}

/*
// Show the model, one cell at a time
void View::show(Model * model) {
    for (int j = 0; j < model->getWidth(); j++) {
        cout << "\t" << j;
    }
    cout << endl;
    for (int i = 0; i < model->getHeight(); i++) {
        cout << i;
        for (int j = 0; j < model->getWidth(); j++) {
            cout << "\t" << model->get(i, j);
        }
        cout << endl;
    }
}
*/
