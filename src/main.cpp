#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <imgui.h>
#include <imgui_impl_allegro5.h>

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

  ImGui::StyleColorsDark();
  ImGui_ImplAllegro5_Init(display);

  bool running = true;
  while (running) {
    ALLEGRO_EVENT ev;
    while (al_get_next_event(event_queue, &ev)) {
      if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) running = false;
    }

    ImGui_ImplAllegro5_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Hello, world!");
    ImGui::Text("This is some useful text.");
    ImGui::End();

    ImGui::Render();
    al_clear_to_color(al_map_rgb(30, 30, 30));
    ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());
    al_flip_display();
  }

  ImGui_ImplAllegro5_Shutdown();
  ImGui::DestroyContext();
  al_destroy_display(display);
  al_destroy_event_queue(event_queue);

  return 0;
}