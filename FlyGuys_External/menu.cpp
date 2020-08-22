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
#include "menu.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "draw_manager.h"

#include <mutex>

namespace settings {
	namespace movement {
		bool fly_enabled = false;
		int fly_speed = 30;
		bool speed_enabled = false;
		int speed_boost = 15;

		bool disable_stun_collision = false;
		bool disable_object_collisions = false;
	};
	namespace cheat {
		bool hide_enabled_cheats = false;
		bool make_me_reach = false;
		bool player_esp_enabled = false;
		bool super_grab_enabled = false;
		float grabber_velocity = 1;
	};
};
namespace cheat_helper {
	bool disable_fly = false;
	bool disable_speed = false;
};

namespace menu {
	bool movement_tab_active = true;
	bool misc_tab_active = true;

	void push_color_for_button( bool active ) {
		if ( active ) {
			ImGui::PushStyleColor( ImGuiCol_Button, ImVec4 { 0.f, 92.f / 255.f, 196.f / 255.f, 1.f } );
			ImGui::PushStyleColor( ImGuiCol_ButtonHovered, ImVec4 { 0.f, 92.f / 255.f, 196.f / 255.f, 1.f } );
		} else {
			ImGui::PushStyleColor( ImGuiCol_Button, ImVec4 { 61.f / 255.f, 61.f / 255.f, 61.f / 255.f, 1.f } );
			ImGui::PushStyleColor( ImGuiCol_ButtonHovered, ImVec4 { 0.f, 128.f / 255.f, 199.f / 255.f, 1.f } );
		}
	}

	void draw_button( const char* name, bool& config_key, bool* change_opositive = nullptr ) {
		push_color_for_button( config_key );
		if ( ImGui::Button( name, { 125 + 50,20 } ) ) {
			config_key = !config_key;
			if ( change_opositive )
				*change_opositive = !config_key;
		}

		ImGui::PopStyleColor( 2 );
	}

	void draw_slider( const char* name, int* val, int min, int max ) {
		ImGui::PushStyleColor( ImGuiCol_Button, ImVec4 { 0.f, 92.f / 255.f, 196.f / 255.f, 1.f } );
		ImGui::PushStyleColor( ImGuiCol_ButtonHovered, ImVec4 { 0.f, 92.f / 255.f, 196.f / 255.f, 1.f } );

		ImGui::SliderInt( name, val, min, max );

		ImGui::PopStyleColor( 2 );
	}

	void draw_slider( const char* name, float* val, float min, float max ) {
		ImGui::PushStyleColor( ImGuiCol_Button, ImVec4 { 0.f, 92.f / 255.f, 196.f / 255.f, 1.f } );
		ImGui::PushStyleColor( ImGuiCol_ButtonHovered, ImVec4 { 0.f, 92.f / 255.f, 196.f / 255.f, 1.f } );

		ImGui::SliderFloat( name, val, min, max );

		ImGui::PopStyleColor( 2 );
	}

	void draw_tab( const char* name, bool& active ) {
		ImGui::Text( name );
		ImGui::SameLine( 118 + 50 );

		ImGui::PushStyleColor( ImGuiCol_Button, ImVec4 { 0.f, 92.f / 255.f, 196.f / 255.f, 1.f } );
		ImGui::PushStyleColor( ImGuiCol_ButtonHovered, ImVec4 { 0.f, 92.f / 255.f, 196.f / 255.f, 1.f } );
		if ( ImGui::Button( "", { 10,10 } ) )
			active = !active;
		ImGui::PopStyleColor( 2 );
	}

	bool collisions_tab_active = true;
	bool tetetete;

	std::once_flag init_style;
	void draw( ) {

		std::call_once( init_style, [ & ] ( ) {
			auto& style = ImGui::GetStyle( );
			style.WindowRounding = 0.f;
			style.FrameRounding = 0.f;
			style.ItemSpacing = ImVec2( 8, 2 );
			style.WindowPadding = ImVec2( 3.f, 3.f );
			style.Colors[ ImGuiCol_FrameBg ] = ImVec4 { 56.f / 255.f, 59.f / 255.f, 58.f / 255.f, 1.f };
			style.Colors[ ImGuiCol_FrameBgActive ] = ImVec4 { 56.f / 255.f, 59.f / 255.f, 58.f / 255.f, 1.f };
			style.Colors[ ImGuiCol_FrameBgHovered ] = ImVec4 { 56.f / 255.f, 59.f / 255.f, 58.f / 255.f, 1.f };
			style.Colors[ ImGuiCol_SliderGrabActive ] = ImVec4 { 0.f, 92.f / 255.f, 196.f / 255.f, 1.f };
			style.Colors[ ImGuiCol_SliderGrab ] = ImVec4 { 0.f, 128.f / 255.f, 199.f / 255.f, 1.f };
			} );

		ImGui::Begin( "tab_movement", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar );
		ImGui::SetWindowSize( { 131 + 50,0 }, ImGuiCond_Always );
		draw_tab( "Movement", movement_tab_active );
		if ( movement_tab_active ) {
			draw_button( "Fly", settings::movement::fly_enabled, &cheat_helper::disable_fly );
			draw_slider( "Fly speed", &settings::movement::fly_speed, 1, 100 );
			draw_button( "Speed", settings::movement::speed_enabled, &cheat_helper::disable_speed );
			draw_slider( "Speed boost", &settings::movement::speed_boost, 1, 100 );
		}
		ImGui::End( );

		ImGui::Begin( "tab_collisions", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar );
		ImGui::SetWindowSize( { 131 + 50,0 }, ImGuiCond_Always );
		draw_tab( "Collisions", collisions_tab_active );
		if ( collisions_tab_active ) {
			draw_button( "Disable stun", settings::movement::disable_stun_collision );
			draw_button( "Disable collisions", settings::movement::disable_object_collisions );
		}
		ImGui::End( );

		ImGui::Begin( "tab_misc", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar );
		ImGui::SetWindowSize( { 131 + 50,0 }, ImGuiCond_Always );
		draw_tab( "Misc", misc_tab_active );
		if ( misc_tab_active ) {
			draw_button( "Hide enable cheats", settings::cheat::hide_enabled_cheats );
			draw_button( "Player ESP", settings::cheat::player_esp_enabled );
			draw_button( "Super grab", settings::cheat::super_grab_enabled );
			draw_slider( "Grab vlocity", &settings::cheat::grabber_velocity, 0, 1 );
		}
		ImGui::End( );
	}
	char old_keys[ 256 ] = { 0 };
	void update_keys( ) {
		char new_keys[ 256 ];
		for ( auto i = 0; i < 256; i++ )
			new_keys[ i ] = GetAsyncKeyState( i );

		if ( ( new_keys[ 0x52 ] && !old_keys[ 0x52 ] )) {
			settings::movement::fly_enabled = !settings::movement::fly_enabled;
			cheat_helper::disable_fly = !settings::movement::fly_enabled;
		}

		if ( new_keys[ 0x43 ] && !old_keys[ 0x43 ] ) {
			settings::movement::speed_enabled = !settings::movement::speed_enabled;
			cheat_helper::disable_speed = !settings::movement::speed_enabled;
		}

		if ( new_keys[ 0x58 ] && !old_keys[ 0x58 ] ) {
			settings::cheat::player_esp_enabled = !settings::cheat::player_esp_enabled;
		}

		if ( new_keys[ 0x47 ] && !old_keys[ 0x47 ] ) {
			settings::cheat::super_grab_enabled = !settings::cheat::super_grab_enabled;
		}

		memcpy( old_keys, new_keys, 256 );
	}

	void update_indicators( ) {
		if ( settings::cheat::hide_enabled_cheats ) return;

		auto text_size = draw_manager::calc_text_size( 18, "TEST" );
		auto y = float( 10 );

		draw_manager::add_text_on_screen( { 10,y }, 0xFFFFFFFF, 18, "Press [Insert] to open menu, or Press [F7] to quit" );
		y += text_size.y + 4.f;
		y += text_size.y + 4.f;

		draw_manager::add_text_on_screen( { 10,y }, 0xFFFFFFFF, 18, "Enable cheats:" );
		y += text_size.y + 4.f;

		if ( settings::movement::fly_enabled ) {
			draw_manager::add_text_on_screen( { 10,y }, 0xFFFFFFFF, 18, "Fly [R]" );
			y += text_size.y + 4.f;
		}
		if ( settings::movement::speed_enabled ) {
			draw_manager::add_text_on_screen( { 10,y }, 0xFFFFFFFF, 18, "Speed [C]" );
			y += text_size.y + 4.f;
		}

		if ( settings::cheat::player_esp_enabled ) {
			draw_manager::add_text_on_screen( { 10,y }, 0xFFFFFFFF, 18, "Player ESP [X]" );
			y += text_size.y + 4.f;
		}

		if ( settings::cheat::super_grab_enabled ) {
			draw_manager::add_text_on_screen( { 10,y }, 0xFFFFFFFF, 18, "Super Grab [G]" );
			y += text_size.y + 4.f;
		}

		if ( settings::movement::disable_stun_collision ) {
			draw_manager::add_text_on_screen( { 10,y }, 0xFFFFFFFF, 18, "No Stun" );
			y += text_size.y + 4.f;
		}
		if ( settings::movement::disable_object_collisions ) {
			draw_manager::add_text_on_screen( { 10,y }, 0xFFFFFFFF, 18, "No Collisions" );
			y += text_size.y + 4.f;
		}
	}
};
