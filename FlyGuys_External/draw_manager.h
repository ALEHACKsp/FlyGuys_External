/* This file is part of FlyGuys_External by b3akers, licensed under the MIT license:
*
* MIT License
*
* Copyright (c) b3akers 2020
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/
#pragma once
#include <Windows.h>
#include "imgui/imgui.h"
#include "vector.h"

namespace draw_manager
{
	extern ImDrawList* _drawList;

	void begin_rendering();
	void end_rendering();

	void add_text_on_screen(vector const& point, DWORD color, int font_size, const char* format, ...);
	void add_rect_on_screen(const vector& a, const vector& b, DWORD col, float rounding = 0.0f, int rounding_corners_flags = ~0, float thickness = 1.0f );
	void add_filled_rect_on_screen(const vector& a, const vector& b, DWORD col, float rounding = 0.0f, int rounding_corners_flags = ~0);
	vector calc_text_size(int font_size, const char* format, ...);
};