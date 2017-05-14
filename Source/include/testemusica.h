//Using SDL, SDL_image, SDL_mixer, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>

//The music that will be played
Mix_Music *gMusic = NULL;

//The sound effects that will be used
Mix_Chunk *gScratch = NULL;
Mix_Chunk *gHigh = NULL;
Mix_Chunk *gMedium = NULL;
Mix_Chunk *gLow = NULL;

//Initialize SDL
if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
{
    printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
    success = false;
}
 //Initialize PNG loading
int imgFlags = IMG_INIT_PNG;
if( !( IMG_Init( imgFlags ) & imgFlags ) )
{
    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
    success = false;
}

 //Initialize SDL_mixer
if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
{
    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    success = false;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load prompt texture
    if( !gPromptTexture.loadFromFile( "21_sound_effects_and_music/prompt.png" ) )
    {
        printf( "Failed to load prompt texture!\n" );
        success = false;
    }

    //Load music
    gMusic = Mix_LoadMUS( "21_sound_effects_and_music/beat.wav" );
    if( gMusic == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    //Load sound effects
    gScratch = Mix_LoadWAV( "21_sound_effects_and_music/scratch.wav" );
    if( gScratch == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    gHigh = Mix_LoadWAV( "21_sound_effects_and_music/high.wav" );
    if( gHigh == NULL )
    {
        printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    gMedium = Mix_LoadWAV( "21_sound_effects_and_music/medium.wav" );
    if( gMedium == NULL )
    {
        printf( "Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    gLow = Mix_LoadWAV( "21_sound_effects_and_music/low.wav" );
    if( gLow == NULL )
    {
        printf( "Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    return success;
}

void close()
{
    //Free loaded images
    gPromptTexture.free();

    //Free the sound effects
    Mix_FreeChunk( gScratch );
    Mix_FreeChunk( gHigh );
    Mix_FreeChunk( gMedium );
    Mix_FreeChunk( gLow );
    gScratch = NULL;
    gHigh = NULL;
    gMedium = NULL;
    gLow = NULL;
    
    //Free the music
    Mix_FreeMusic( gMusic );
    gMusic = NULL;

    //Destroy window    
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}
//Handle key press
else if( e.type == SDL_KEYDOWN )
{
    switch( e.key.keysym.sym )
    {
        //Play high sound effect
        case SDLK_1:
        Mix_PlayChannel( -1, gHigh, 0 );
        break;
        
        //Play medium sound effect
        case SDLK_2:
        Mix_PlayChannel( -1, gMedium, 0 );
        break;
        
        //Play low sound effect
        case SDLK_3:
        Mix_PlayChannel( -1, gLow, 0 );
        break;
        
        //Play scratch sound effect
        case SDLK_4:
        Mix_PlayChannel( -1, gScratch, 0 );
        break;
                                    case SDLK_9:
        //If there is no music playing
        if( Mix_PlayingMusic() == 0 )
        {
            //Play the music
            Mix_PlayMusic( gMusic, -1 );
        }
        //If music is being played
        else
        {
            //If the music is paused
            if( Mix_PausedMusic() == 1 )
            {
                //Resume the music
                Mix_ResumeMusic();
            }
            //If the music is playing
            else
            {
                //Pause the music
                Mix_PauseMusic();
            }
        }
        break;
        
        case SDLK_0:
        //Stop the music
        Mix_HaltMusic();
        break;
    }
}
