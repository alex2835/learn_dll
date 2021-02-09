#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define DYNALO_EXPORT_SYMBOLS
#include <dynalo/symbol_helper.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <cstdint>


DYNALO_EXPORT void DYNALO_CALL Draw(ImGuiContext*);