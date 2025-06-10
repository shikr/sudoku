#include <imgui.h>
#include <cstdio>

#include "utils/sudoku.h"

void RenderTable(AppState state) {
  if (ImGui::BeginTable("Table", state.size, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
    for (int i = 0; i < state.size; i++) {
      ImGui::TableNextRow();
      for (int j = 0; j < state.size; j++) {
        ImGui::TableSetColumnIndex(j);
        ImGui::Text("Col %d", state.table[i][j]);
      }
    }

    ImGui::EndTable();
  }
}

void RenderInput(AppState &state) {
  if (!ImGui::BeginChild("Input Table", ImVec2(0, 0), true))
    return;
  ImGui::Text("Establece los valores iniciales de la tabla.");
  ImGui::SeparatorText("Sudoku");
  if (!ImGui::BeginTable("Input Table", state.size)) return;
  for (int i = 0; i < state.size; i++) {
    ImGui::TableNextRow();
    for (int j = 0; j < state.size; j++) {
      char label[32];
      ImGui::TableSetColumnIndex(j);
      snprintf(label, sizeof(label), "##cell_%d_%d", i, j);
      ImGui::SliderInt(label, &state.table[i][j], 0, state.size);
    }
  }
  ImGui::EndTable();
  if (ImGui::Button("Aceptar")) state.status = Resolving;
  ImGui::EndChild();
}

void RenderUi(AppState *state) {
  const ImGuiViewport *main_viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(
      ImVec2(main_viewport->WorkPos.x, main_viewport->WorkPos.y));
  ImGui::SetNextWindowSize(
      ImVec2(main_viewport->WorkSize.x, main_viewport->WorkSize.y));
  
  if(ImGui::Begin("Sudoku Solver", NULL, ImGuiWindowFlags_NoDecoration)) {
    switch (state->status) {
      case Resolving:
        RenderTable(*state);
        break;
      case Selecting:
        RenderInput(*state);
        break;
      case SizeSelecting:
        break;
      case Finished:
        break;
    }
    ImGui::End();
  }
}
