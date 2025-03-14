#include <SDL_ttf.h>

#include "simple_logger.h"

#include "gfc_list.h"
#include "gf2d_graphics.h"

#include "font.h"

typedef struct
{
    GFC_List *fonts;
}FontManager;


static FontManager font_manager = { 0 };


void font_close()
{
    TTF_Font* font;
    int i, c;
    c = gfc_list_get_count(font_manager.fonts);
    for (i = 0; i < c; i++)
    {
        font = gfc_list_get_nth(font_manager.fonts, i);
        if (!font) continue;
        TTF_CloseFont(font);
    }
    gfc_list_delete(font_manager.fonts);
    memset(&font_manager, 0, sizeof(FontManager));
    TTF_Quit();
}

void font_init()
{
    int i;
    TTF_Font* font;
    if (TTF_Init() != 0)
    {
        slog("failed to initialize TTF system");
        return;
    }
    font_manager.fonts = gfc_list_new();
    
    for (i = 0; i < FS_MAX; i++)
    {
        font = TTF_OpenFont("fonts/AGENCYR.TTF", 40 + (i * 4));
        if (!font)
        {
            slog("failed to open  the font ");
            continue;
        }
        gfc_list_append(font_manager.fonts, font);
    }
    atexit(font_close);
}

void font_draw_text(const char* text, FontStyles style, GFC_Color color, GFC_Vector2D position)
{
    TTF_Font* font;
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Color fg;
    SDL_Rect rect;
   

    

    font = gfc_list_get_nth(font_manager.fonts, style);
    if (!font)
    {
        slog("failed to render text '%s', missing font style %i", text, style);
        return;
    }
    fg = gfc_color_to_sdl(color);
    surface = TTF_RenderUTF8_Blended_Wrapped(font, text, fg, 0);
    if (!surface)
    {
        slog("the error");
        return;
    }
    surface = gf2d_graphics_screen_convert(&surface);
    if (!surface)
    {
        slog("the error");
        return;
    }
    texture = SDL_CreateTextureFromSurface(gf2d_graphics_get_renderer(), surface);
    if (!texture)
    {
        SDL_FreeSurface(surface);
        slog("this error");
        return;
    }
    rect.x = position.x;
    rect.y = position.y;
    rect.w = surface->w;
    rect.h = surface->h;
    SDL_RenderCopy(gf2d_graphics_get_renderer(),
        texture,
        NULL,
        &rect);
    SDL_FreeSurface(surface);


 
}