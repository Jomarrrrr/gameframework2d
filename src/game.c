#include <SDL.h>
#include "simple_logger.h"

#include "gf2d_graphics.h"
#include "gf2d_sprite.h"

#include "gfc_input.h"
#include "gfc_string.h"
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
    
    World* world;

    int mx,my;
    float mf = 0;
    Sprite *mouse;
    GFC_Color mouseGFC_Color = gfc_color8(2,2,255,100);
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
    entity_system_initialize(1024); 
    SDL_ShowCursor(SDL_DISABLE);
    gfc_input_init("./config/input.cfg");
    camera_set_size(gfc_vector2d(1200, 700));
    /*demo setup*/
  
    mouse = gf2d_sprite_load_all("images/pointer.png",32,32,16,0);
    player = player_new();
    slime = slime_new();
    world = world_load("config/test_world.map");
    world_setup_camera(world);
 
    slog("press [escape] to quit");
    /*main game loop*/
    while(!done)
    {
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
         world_draw(world);
            

            entity_system_draw();




            //UI elements last
            gf2d_sprite_draw(
                mouse,
                gfc_vector2d(mx,my),
                NULL,
                NULL,
                NULL,
                NULL,
                &mouseGFC_Color,
                (int)mf);

        gf2d_graphics_next_frame();// render current draw frame and skip to the next frame
        
        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
        //slog("Rendering at %f FPS",gf2d_graphics_get_frames_per_second());
    }
    entity_free(player);
    entity_free(slime);
    world_free(world);
    slog("---==== END ====---");
    return 0;
}
/*eol@eof*/
