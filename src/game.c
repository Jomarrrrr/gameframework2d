#include <SDL.h>
#include <SDL_main.h>
#include "simple_logger.h"

#include "gf2d_graphics.h"
#include "gf2d_sprite.h"

#include "gfc_input.h"
#include "gfc_string.h"
#include "gfc_audio.h"
#include <SDL_mixer.h>
#include <SDL_audio.h>
#include <SDL_image.h>


#include "font.h"
#include "camera.h"
#include "entity.h"
#include "player.h"
#include "world.h"  
#include "slime.h"
int main(int argc, char * argv[])
{
    /*variable declarations*/

    int done = 0;
    const Uint8 * keys;
    int loops = 5;
    World* world;
    World* world2;
    gfc_audio_init(32, 8, 1, 1, true, false);
	int toggle = 0;
    Mix_VolumeMusic(32);
    int mx,my;
    float mf = 0;
    Sprite *mouse;
    Sprite* light;
	Sprite* arrow;
    GFC_Color mouseGFC_Color = gfc_color8(0,0,0,255);
    Entity* player; 
    Entity* slime;

    /*program initializtion*/
    init_logger("gf2d.log",0);
    slog("---==== BEGIN ====---");
    gf2d_graphics_initialize(
        "gf2d",
        1200,
        720,
        1200,
        720,
        gfc_vector4d(0,0,0,255),
        0);
    gf2d_graphics_set_frame_delay(16);
    gf2d_sprite_init(1024);
    font_init();
    entity_system_initialize(1024); 
    SDL_Init(SDL_INIT_AUDIO);
    SDL_ShowCursor(SDL_DISABLE);
    gfc_input_init("./config/input.cfg");
    camera_set_size(gfc_vector2d(1200, 700));
    /*demo setup*/
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 8, 2048);
    Mix_VolumeMusic(32);

    Mix_Music* bgm = Mix_LoadMUS("audio/bgm.wav");
    Mix_PlayMusic(bgm, -1);

    light = gf2d_sprite_load_light(
        "images/light.png",
        54,
        54,
        1,
        0);
  
    mouse = gf2d_sprite_load_all("images/pointer.png",32,32,16,0);
	arrow = gf2d_sprite_load_all("images/arrow.png", 54, 54, 1, 0);
    player = player_new();
    slime = slime_new();
    
    world = world_load("config/test_world.map");
	world2 = world_load("config/world2.map");
    world_setup_camera(world);
 
    slog("press [escape] to quit");
   
    /*main game loop*/
    while(!done)
    {
        
        bgm = Mix_LoadMUS("audio/bgm.wav");
        Mix_LoadMUS("audio/bgm.wav");
        SDL_PumpEvents();   // update SDL's internal event structures
        gfc_input_update();
     

        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        /*update things here*/
        SDL_GetMouseState(&mx,&my);
        mf+=0.1;
        if (mf >= 16.0)mf = 0;
        
        entity_system_think();
        entity_system_update();


        gf2d_graphics_clear_screen();// clears drawing buffers
        // all drawing should happen betweem clear_screen and next_frame
            //backgrounds drawn first
        if (keys[SDL_SCANCODE_UP])
        {
            toggle = 1;
            world_free(world);
        }
		if (toggle == 0)
		{
			world_draw(world);
		}
		else
		{
			world_draw(world2);
		}
		//draw the player and slime
		entity_system_draw();
		
		entity_draw(slime);
        entity_draw(player);

		//draw the world 
        world_draw(world);
            

            entity_system_draw();
            GFC_Vector2D slimp;
            slimp = get_position(slime);
            GFC_Vector2D playerpos = get_position(player);
            int slimex = slimp.x;
			
            char message[256]; // Make sure the buffer is large enough to hold the message
			

            // Format the message to include the value of slimex
            sprintf(message, "Press ESC to quit\nain't that neato. slimex = %d", slimex);

            // Draw the formatted message
            font_draw_text(message, FS_small, GFC_COLOR_CYAN, gfc_vector2d(10, 10));

            //UI elements last
            gf2d_sprite_draw(
                arrow,
                gfc_vector2d(mx,my),
                NULL,
                NULL,
                NULL,
                NULL,
                &mouseGFC_Color,
                0);
            if (playerpos.x > 1000)
            {
            GFC_Color white = gfc_color8(255, 255, 255, 255);
            gf2d_sprite_draw(
                arrow,
                gfc_vector2d(playerpos.x - 200, playerpos.y),
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                0);
         
            
           }

            if (playerpos.x < 50)
            {
                GFC_Color white = gfc_color8(255, 255, 255, 255);
                gf2d_sprite_draw(
                    arrow,
                    gfc_vector2d(playerpos.x + 200, playerpos.y),
                    NULL,
                    NULL,
                    NULL,
                    NULL,
                    NULL,
                    0);


            }

                if (!arrow) {
                    slog("Arrow sprite failed to load!");
                }

        gf2d_graphics_next_frame();// render current draw frame and skip to the next frame

        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
        //slog("Rendering at %f FPS",gf2d_graphics_get_frames_per_second());
    }
    entity_free(player);
    entity_free(slime);
    world_free(world);
    world_free(world2);
    slog("---==== END ====---");
    return 0;
}
/*eol@eof*/
