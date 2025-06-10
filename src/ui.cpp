#include <imgui.h>

#include "utils/table.h"
#include "utils/sudoku.h"

void RenderTable(Table table) {
  if (ImGui::BeginTable("Table", TABLE_SIZE, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
    for (int i = 0; i < TABLE_SIZE; i++) {
      ImGui::TableNextRow();
      for (int j = 0; j < TABLE_SIZE; j++) {
        ImGui::TableSetColumnIndex(j);
        ImGui::Text("Col %d", table[i][j]);
      }
    }

    ImGui::EndTable();
  }
}

void RenderUi(AppState *state) {
  const ImGuiViewport *main_viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(
      ImVec2(main_viewport->WorkPos.x, main_viewport->WorkPos.y));
  ImGui::SetNextWindowSize(
      ImVec2(main_viewport->WorkSize.x, main_viewport->WorkSize.y));
  
  if(ImGui::Begin("Sudoku Solver", NULL, ImGuiWindowFlags_NoDecoration)) {
    RenderTable(state->table);
    ImGui::End();
  }
}
