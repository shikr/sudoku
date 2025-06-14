#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/fshook.h>
#include <imgui.h>
#include <imgui_impl_allegro5.h>

#include <cstdlib>
#include <ctime>

#include "ui.h"
#include "utils/sudoku.h"
#include "utils/table.h"

const char *FONT = "C:\\Windows\\Fonts\\segoeui.ttf";

int main() {
  al_init();
  al_install_keyboard();
  al_install_mouse();
  al_init_primitives_addon();
  al_set_new_display_flags(ALLEGRO_RESIZABLE);
  ALLEGRO_DISPLAY *display = al_create_display(800, 600);
  al_set_window_title(display, "ImGui + Allegro5");
  ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
  al_register_event_source(event_queue, al_get_display_event_source(display));
  al_register_event_source(event_queue, al_get_keyboard_event_source());
  al_register_event_source(event_queue, al_get_mouse_event_source());

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
  if (al_filename_exists(FONT)) {
    io.Fonts->AddFontFromFileTTF(FONT, 22);
  }

  ImGui::StyleColorsDark();
  ImGui_ImplAllegro5_Init(display);
  srand(time(NULL));

  bool running = true;
  AppState state;
  state.status = SizeSelecting;
  state.size = 9;
  state.subSize = 3;
  state.speed = 1;
  while (running) {
    ALLEGRO_EVENT ev;
    while (al_get_next_event(event_queue, &ev)) {
      ImGui_ImplAllegro5_ProcessEvent(&ev);
      if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) running = false;
      if (ev.type == ALLEGRO_EVENT_DISPLAY_RESIZE) {
        al_acknowledge_resize(display);
        ImGui_ImplAllegro5_InvalidateDeviceObjects();
        ImGui_ImplAllegro5_CreateDeviceObjects();
      }
    }

    ImGui_ImplAllegro5_NewFrame();
    ImGui::NewFrame();

    RenderUi(&state);

    ImGui::Render();
    al_clear_to_color(al_map_rgb(30, 30, 30));
    ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());
    al_flip_display();
  }
  freeTable(state.table, state.size);

  ImGui_ImplAllegro5_Shutdown();
  ImGui::DestroyContext();
  al_destroy_display(display);
  al_destroy_event_queue(event_queue);

  return 0;
}