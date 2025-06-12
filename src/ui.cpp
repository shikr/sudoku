#include <imgui.h>

#include <cstdio>

#include "utils/fs.h"
#include "utils/sudoku.h"
#include "utils/table.h"

void RenderTable(AppState state) {
  if (ImGui::BeginTable("Table", state.size,
                        ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
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

void RenderFinish(AppState state) {
  if (!ImGui::BeginChild("Finish Table")) return;
  int row, col;
  if (findEmpty(state, row, col))
    ImGui::Text("No se ha podido completar el sudoku...");
  else
    ImGui::Text("Terminado.");
  ImGui::SeparatorText("Sudoku");
  RenderTable(state);
  ImGui::EndChild();
}

void RenderInput(AppState &state) {
  if (!ImGui::BeginChild("Input Table", ImVec2(0, 0), true)) return;
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
  if (ImGui::Button("Aleatorio")) fillRandom(state);
  ImGui::SameLine();
  if (ImGui::Button("Aceptar")) {
    state.key = tableToKey(state);
    // TODO: use in a new thread
    solve(state);
    state.step = 0;
    state.lastStepTime = ImGui::GetTime();
    state.table = getStep(state);
    state.step++;
    state.status = Resolving;
  }
  ImGui::EndChild();
}

void RenderSize(AppState &state) {
  if (!ImGui::BeginChild("Input Size", ImVec2(0, 0), true)) return;
  ImGui::Text("Establece las dimensiones de la tabla.");
  ImGui::RadioButton("9x9", &state.size, 9);
  ImGui::RadioButton("4x4", &state.size, 4);
  if (state.size == 9)
    state.subSize = 3;
  else
    state.subSize = 2;
  if (ImGui::Button("Aceptar")) {
    fillTable(state.table, state.size);
    state.status = Selecting;
  }
  ImGui::EndChild();
}

void RenderUi(AppState *state) {
  const ImGuiViewport *main_viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x, main_viewport->WorkPos.y));
  ImGui::SetNextWindowSize(ImVec2(main_viewport->WorkSize.x, main_viewport->WorkSize.y));

  if (ImGui::Begin("Sudoku Solver", NULL, ImGuiWindowFlags_NoDecoration)) {
    switch (state->status) {
      case Resolving:
        if (ImGui::GetTime() - state->lastStepTime > DELAY) {
          state->lastStepTime = ImGui::GetTime();
          state->table = getStep(*state);
          state->step++;
          if (state->step >= getStepsSize(state->key)) state->status = Finished;
        }
        RenderTable(*state);
        break;
      case Selecting:
        RenderInput(*state);
        break;
      case SizeSelecting:
        RenderSize(*state);
        break;
      case Finished:
        RenderFinish(*state);
        break;
    }
    ImGui::End();
  }
}
