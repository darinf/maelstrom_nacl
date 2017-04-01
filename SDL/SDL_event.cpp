#include "SDL_event.h"

#include <stdio.h>
#include <unistd.h>

//XXX #include <ppapi/c/ppb_input_event.h>
#include "myerror.h"
//XXX #include "ppb.h"
//XXX #include "pp_resource_queue.h"

#if 0
extern PPResourceQueue g_input_queue;

static int ToUnicode(uint32_t key_code, PP_Resource input_event) {
  // NOTE: We should really handle PP_INPUTEVENT_TYPE_CHAR instead,
  // but this hacky approach is good enough for a subset of ASCII.

  if (key_code >= SDLK_0 && key_code <= SDLK_9)
    return (int) key_code;

  if (key_code >= SDLK_a && key_code <= SDLK_z) {
    uint32_t modifiers = ppb.input_event->GetModifiers(input_event);
    if (modifiers & PP_INPUTEVENT_MODIFIER_SHIFTKEY)
      return (int) key_code;

    return (int) key_code + 32;
  }

  if (key_code == SDLK_BACKSPACE || key_code == SDLK_DELETE)
    return '\b';

  if (key_code == SDLK_RETURN)
    return '\r';

  return 0;
}

static bool TranslateEvent(PP_Resource input_event, SDL_Event* result) {
  bool translated = true;

  PP_InputEvent_Type input_event_type = ppb.input_event->GetType(input_event);

  switch (input_event_type) {
    case PP_INPUTEVENT_TYPE_MOUSEDOWN: {
      PP_Point position = ppb.mouse_input_event->GetPosition(input_event);
      //mesg("mousedown [x=%u, y=%u]", position.x, position.y);
      result->type = SDL_MOUSEBUTTONDOWN;
      result->button.button = 1;
      result->button.x = position.x;
      result->button.y = position.y;
      break;
    }
    case PP_INPUTEVENT_TYPE_KEYDOWN: {
      uint32_t key_code = ppb.keyboard_input_event->GetKeyCode(input_event);
      //mesg("keydown [key_code=%u]", key_code);
      result->type = SDL_KEYDOWN;
      result->key.state = SDL_PRESSED;
      result->key.keysym.sym = key_code;
      result->key.keysym.mod = 0;
      result->key.keysym.unicode = ToUnicode(key_code, input_event);
      break;
    }
    case PP_INPUTEVENT_TYPE_KEYUP: {
      uint32_t key_code = ppb.keyboard_input_event->GetKeyCode(input_event);
      //mesg("keyup [key_code=%u]", key_code);
      result->type = SDL_KEYUP;
      result->key.state = SDL_RELEASED;
      result->key.keysym.sym = key_code;
      result->key.keysym.mod = 0;
      result->key.keysym.unicode = ToUnicode(key_code, input_event);
      break;
    }
    default:
      //mesg("unknown input event");
      translated = false;
      break;
  }
  return translated;
}
#endif

int SDL_PollEvent(SDL_Event* event) { 
  error("Unimplemented: SDL_PollEvent\n");
#if 0
  for (;;) {
    PP_Resource input_resource = g_input_queue.GetOrFail();
    if (!input_resource)
      return 0;

    bool translated = TranslateEvent(input_resource, event);

    ppb.core->ReleaseResource(input_resource);

    if (translated)
      break;
  }
#endif
  return 0;
}

int SDL_WaitEvent(SDL_Event* event) {
  error("Unimplemented: SDL_WaitEvent\n");
#if 0
  for (;;) {
    PP_Resource input_resource = g_input_queue.Get();
    if (!input_resource)
      return 0;

    bool translated = TranslateEvent(input_resource, event);

    ppb.core->ReleaseResource(input_resource);

    if (translated)
      break;
  }
#endif
  return 0;
}

const char* SDL_GetKeyName(SDLKey key) {
  switch (key) {
    case SDLK_BACKSPACE:
      return "backspace";
    case SDLK_TAB:
      return "tab";
    case SDLK_RETURN:
      return "return";
    case SDLK_PAUSE:
      return "pause";
    case SDLK_ESCAPE:
      return "escape";
    case SDLK_SPACE:
      return "space";
    case SDLK_LEFT:
      return "left";
    case SDLK_UP:
      return "up";
    case SDLK_RIGHT:
      return "right";
    case SDLK_DELETE:
      return "delete";
    case SDLK_0:
      return "0";
    case SDLK_1:
      return "1";
    case SDLK_2:
      return "2";
    case SDLK_3:
      return "3";
    case SDLK_4:
      return "4";
    case SDLK_5:
      return "5";
    case SDLK_6:
      return "6";
    case SDLK_7:
      return "7";
    case SDLK_8:
      return "8";
    case SDLK_9:
      return "9";
    case SDLK_a:
      return "a";
    case SDLK_c:
      return "c";
    case SDLK_l:
      return "l";
    case SDLK_p:
      return "p";
    case SDLK_q:
      return "q";
    case SDLK_x:
      return "x";
    case SDLK_z:
      return "z";
    case SDLK_F1:
      return "F1";
    case SDLK_F3:
      return "F3";
  }
  return "###";
}

void SDL_EnableUNICODE(int) {}
