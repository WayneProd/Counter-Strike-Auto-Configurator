// 13/08/2024 Koneko Prod.
// DESCRIPTION:
//
// Implementation of POSIX opendir for Visual C++.
// Derived from the MinGW C Library Extensions Source (released to the
//  public domain).
//
#pragma once

// * Includes
#include "Windows.h"
#include <fstream>
#include <string>
#include <sstream>
// * namespaces, classes and string
DEVMODE dm;

using namespace std;

string Video;
uint_fast16_t VClor;

HANDLE hConsole;

void setColor(uint8_t clr) {
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, clr);
}


class Display {
public:	
	// * Display info
	const uint_fast16_t DisplayHeight = GetSystemMetrics(SM_CYSCREEN);
	const uint_fast16_t DisplayWidth = GetSystemMetrics(SM_CXSCREEN);

	const void GetInfoDisplay() {
		dm.dmSize = sizeof(dm);
		EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm);

		HDC hdcScreen = GetDC(NULL);
		uint_fast16_t bpp = GetDeviceCaps(hdcScreen, BITSPIXEL) * GetDeviceCaps(hdcScreen, PLANES);
		ReleaseDC(NULL, hdcScreen);

		setColor(13);
		cout << "===============Display-Info===============\n\n";
		setColor(1);
		cout << "  Display Height: ";
		setColor(4);
		cout << DisplayHeight << endl;
		setColor(1);
		cout << "  Display Width: ";
		setColor(4);
		cout << DisplayWidth << endl << endl;;

		setColor(1);
		cout << "  Frequency: "; 
		setColor(4);
		cout << dm.dmDisplayFrequency << "hz" << endl;
		setColor(1);
		cout << "  DisplayBpp: ";
		setColor(4);
		cout << bpp << endl << endl;

		setColor(13);
		cout << "==========================================\n" << endl;
	}

	//Create a decimal number
	std::string decimalToHexadecimal(int decimal_num) {
		if (decimal_num == 0)
			return "0";

		std::stringstream ss;
		std::string hex_digits = "0123456789ABCDEF";

		while (decimal_num > 0) {
			int remainder = decimal_num % 16;
			ss << hex_digits[remainder];
			decimal_num /= 16;
		}

		std::string hex_num = ss.str();
		std::reverse(hex_num.begin(), hex_num.end()); // Реверсируем строку, чтобы получить правильный порядок символов

		return hex_num;
	}


	void CreateDisplaySettings() {

		cout << " Creating a display settings..." << endl;    

		HDC hdcScreen = GetDC(NULL);
		uint_fast16_t bpp = GetDeviceCaps(hdcScreen, BITSPIXEL) * GetDeviceCaps(hdcScreen, PLANES);
		ReleaseDC(NULL, hdcScreen);

		//Create a safe game settings!!!
		ofstream outf("DisplaySettings.REG");
		outf << "Windows Registry Editor Version 5.00\n\n";
		outf << "[HKEY_CURRENT_USER\\SOFTWARE\\Valve\\Half-Life\\Settings]\n";
		outf << char(34) << "EngineD3D"<< char(34) << "= dword:0" << endl;
		outf << char(34) << "DisplayBPP"<< char(34) << "= dword:" << decimalToHexadecimal(bpp) << endl;
		outf << char(34) << "DisplayHeight"<< char(34) << "= dword:" << decimalToHexadecimal(DisplayHeight) << endl;
		outf << char(34) << "DisplayWidth"<< char(34) << "= dword:" << decimalToHexadecimal(DisplayWidth) << endl;
		outf << char(34) << "addons_folder"<< char(34) << "= dword:0" << endl;
		outf << char(34) << "hdmodels"<< char(34) << "= dword:1" << endl;
		outf << char(34) << "ScreenBPP"<< char(34) << "= dword:" << decimalToHexadecimal(bpp) << endl;
		outf << char(34) << "ScreenHeight"<< char(34) << "= dword:258" << endl;
		outf << char(34) << "ScreenWidth"<< char(34) << "= dword:320" << endl;
		outf << char(34) << "ScreenWindowed"<< char(34) << "= dword:0" << endl;

		outf.close();
		cout << " Great!" << endl;

	}
};

class Config {
public:
	void bind(const string& button, const string& action) {
		// Открыть файл для записи (std::ofstream открывает файл для записи)
		std::ofstream outFile("userconfig.cfg", std::ios::app); // ios::app добавляет данные в конец файла

		// Записать содержимое в файл
		outFile << "bind" << " " << '"' << button << '"' << " " << '"' << action << '"' << std::endl;

		// Закрыть файл
		outFile.close();
	}


	void CheckVideo() {
		DISPLAY_DEVICE dd;
		dd.cb = sizeof(dd);
		DWORD deviceIndex = 0;

		cout << " Checking your GPU..." << endl;
		

		while (EnumDisplayDevices(NULL, deviceIndex, &dd, 0)) {
			// Проверяем, содержит ли имя устройства строку "AMD"
			if (std::wstring(dd.DeviceString).find(L"ATI") != std::wstring::npos) {
				VClor = 4;
				Video = "AMD";
			}
			else if (std::wstring(dd.DeviceString).find(L"AMD") != std::wstring::npos) {
				VClor = 4;
				Video = "AMD";
			}
			else if (std::wstring(dd.DeviceString).find(L"NVIDIA") != std::wstring::npos) {
				VClor = 2;
				Video = "NVIDIA";
			}
			else {
				VClor = 15;
				Video = "UNKNOWN VIDEO!!!";
			}

			deviceIndex++;
		}

		cout << " Your videocard: ";
		setColor(VClor);
		cout << Video << endl;
		setColor(13);
	}

	void CreateConfig() {

		dm.dmSize = sizeof(dm);
		EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm);

		ofstream outf("userconfig.cfg");

		outf << "// This file is overwritten whenever you change your user settings in the game." << endl;
		outf << "//	W             W     A		Y    y	N	N	EEEEE" << endl;
		outf << "//	 W     W     W     A A		 Y   y	NN	N	E" << endl;
		outf << "//	  W   W W   w	  A   A		  Yyy	N N	N	EEEEE" << endl;
		outf << "//     W W   W W	 AAAAAAA		Y	N  NN	E" << endl;
		outf << "// 		W     W		A		A	  yyY	N   N	EEEEE" << endl;
		outf << "// Add custom configurations to the file " << char(34) << "userconfig.cfg" << char(34) << "." << endl << endl;

		outf << "unbindall" << endl;
		outf.close();
		bind("TAB", "+showscores");
		bind("ENTER", "+attack");
		bind("ESCAPE", "cancelselect");
		bind("SPACE", "+jump");
		bind("'", "+moveup");
		bind("+", "sizeup");
		bind(",", "buyammo1");
		bind("/", "+movedown");
		bind("0", "slot10");
		bind("1", "slot1");
		bind("2", "slot2");
		bind("3", "slot3");
		bind("4", "slot4");
		bind("5", "slot5");
		bind("6", "slot6");
		bind("7", "slot7");
		bind("8", "slot8");
		bind("9", "slot9");
		bind(";", "+mlook");
		bind("=", "sizeup");
		bind("[", "invprev");
		bind("]", "invnext");
		bind("`", "toggleconsole");
		bind("a", "+moveleft");
		bind("b", "buy");
		bind("c", "radio3");
		bind("d", "+moveright");
		bind("e", "+use");
		bind("f", "impulse 100");
		bind("g", "drop");
		bind("h", "+commandmenu");
		bind("i", "showbriefing");
		bind("k", "+voicerecord");
		bind("m", "chooseteam");
		bind("n", "nightvision");
		bind("o", "buyequip");
		bind("q", "lastinv");
		bind("r", "+reload");
		bind("s", "+back");
		bind("t", "impulse 201");
		bind("u", "messagemode2");
		bind("w", "+forward");
		bind("x", "radio2");
		bind("y", "messagemode");
		bind("z", "radio1");
		bind("~", "toggleconsole");
		bind("UPARROW", "+forward");
		bind("DOWNARROW", "+back");
		bind("LEFTARROW", "+left");
		bind("RIGHTARROW", "+right");
		bind("ALT", "+strafe");
		bind("CTRL", "+duck");
		bind("SHIFT", "+speed");
		bind("F1", "autobuy");
		bind("F2", "rebuy");
		bind("F5", "snapshot");
		bind("F10", "quit promt");
		bind("INS", "+klook");
		bind("PGDN", "+lookdown");
		bind("PGUP", "+lookup");
		bind("END", "force_centerview");
		bind("MWHEELDOWN", "+jump");
		bind("MWHEELUP", "invprev");
		bind("MOUSE1", "+attack");
		bind("MOUSE2", "+attack2");
		bind("PAUSE", "pause");
		//////////////////////////////////////////////////

		ofstream outFi("userconfig.cfg", std::ios::app);
		outFi << "_cl_autowepswitch " << char(34) << "0" << char(34) << endl;
		outFi << "_snd_mixahead " << char(34) << "0.1" << char(34) << endl;
		if (Video == "AMD") {
			outFi << "ati_npatch " << char(34) << "1.0" << char(34) << endl;
			outFi << "ati_subdiv " << char(34) << "2.0" << char(34) << endl;
		}
		else if (Video == "NVIDIA") {
			outFi << "ati_npatch " << char(34) << "0" << char(34) << endl;
			outFi << "ati_subdiv " << char(34) << "0" << char(34) << endl;
		}
		else {
			outFi << "ati_npatch " << char(34) << "0" << char(34) << endl;
			outFi << "ati_subdiv " << char(34) << "0" << char(34) << endl;
		}
		outFi << "bgmvolume " << char(34) << "1.000000" << char(34) << endl;
		outFi << "sv_cheats " << char(34) << "1" << char(34) << endl;
		outFi << "sv_maxupdaterate " << char(34) << "103" << char(34) << endl;
		outFi << "sv_lan_rate " << char(34) << "20000" << char(34) << endl;
		outFi << "sv_unlag " << char(34) << "1" << char(34) << endl;
		outFi << "bottomcolor " << char(34) << "6" << char(34) << endl;
		outFi << "brightness " << char(34) << "3" << char(34) << endl;
		outFi << "cl_allowdownload " << char(34) << "1" << char(34) << endl;
		outFi << "cl_allowupload " << char(34) << "1" << char(34) << endl;
		outFi << "cl_backspeed " << char(34) << "400" << char(34) << endl;
		outFi << "cl_bob " << char(34) << "0.01" << char(34) << endl;
		outFi << "cl_cmdbackup " << char(34) << "2" << char(34) << endl;
		outFi << "cl_cmdrate " << char(34) << dm.dmDisplayFrequency + 5 << char(34) << endl;
		outFi << "cl_corpsestay " << char(34) << "120.000000" << char(34) << endl;
		outFi << "cl_crosshair_color " << char(34) << "50 250 50" << char(34) << endl;
		outFi << "cl_crosshair_size " << char(34) << "small" << char(34) << endl;
		outFi << "cl_crosshair_translucent " << char(34) << "0" << char(34) << endl;
		outFi << "cl_dlmax " << char(34) << "512" << char(34) << endl;
		outFi << "cl_download_ingame " << char(34) << "1" << char(34) << endl;
		outFi << "cl_dynamiccrosshair " << char(34) << "0" << char(34) << endl;
		outFi << "cl_filterstuffcmd " << char(34) << "0" << char(34) << endl;
		outFi << "cl_forwardspeed " << char(34) << "400" << char(34) << endl;
		outFi << "cl_himodels " << char(34) << "0" << char(34) << endl;
		outFi << "cl_idealpitchscale " << char(34) << "0.8" << char(34) << endl;
		outFi << "cl_lc " << char(34) << "1" << char(34) << endl;
		outFi << "cl_logocolor " << char(34) << "#Valve_Blue" << char(34) << endl;
		outFi << "cl_logofile " << char(34) << "skull" << char(34) << endl;
		outFi << "cl_lw " << char(34) << "1" << char(34) << endl;
		outFi << "cl_min_ct " << char(34) << "2" << char(34) << endl;
		outFi << "cl_min_t " << char(34) << "1" << char(34) << endl;
		outFi << "cl_minmodels " << char(34) << "1" << char(34) << endl;
		outFi << "cl_mousegrab " << char(34) << "0" << char(34) << endl;
		outFi << "cl_radartype " << char(34) << "0" << char(34) << endl;
		outFi << "cl_righthand " << char(34) << "1" << char(34) << endl;
		outFi << "cl_shadow " << char(34) << "1" << char(34) << endl;
		outFi << "cl_showfps " << char(34) << "0" << char(34) << endl;
		outFi << "cl_sidespeed " << char(34) << "400" << char(34) << endl;
		outFi << "cl_smoothtime " << char(34) << "0.1" << char(34) << endl;
		outFi << "cl_timeout " << char(34) << "60" << char(34) << endl;
		outFi << "cl_updaterate " << char(34) << 102 << char(34) << endl;
		outFi << "cl_vsmoothing " << char(34) << "0.05" << char(34) << endl;
		outFi << "cl_weather " << char(34) << "1" << char(34) << endl;
		outFi << "cl_interp " << char(34) << "0" << char(34) << endl;
		outFi << "con_color " << char(34) << "255 180 30" << char(34) << endl;
		outFi << "con_mono " << char(34) << "0" << char(34) << endl;
		outFi << "crosshair " << char(34) << "1.000000" << char(34) << endl;
		outFi << "default_fov " << char(34) << "160" << char(34) << endl;
		outFi << "ex_interp " << char(34) << "0" << char(34) << endl;
		outFi << "fastsprites " << char(34) << "2" << char(34) << endl;
		outFi << "fps_max " << char(34) << dm.dmDisplayFrequency + 1 << char(34) << endl;
		outFi << "fps_override " << char(34) << "1" << char(34) << endl;
		outFi << "gamma " << char(34) << "3" << char(34) << endl;
		outFi << "gl_ansio " << char(34) << "16" << char(34) << endl;
		outFi << "gl_dither " << char(34) << "1" << char(34) << endl;
		outFi << "gl_flipmatrix " << char(34) << "0" << char(34) << endl;
		outFi << "gl_fog " << char(34) << "1" << char(34) << endl;
		outFi << "gl_keeptjunctions " << char(34) << "1" << char(34) << endl;
		outFi << "gl_lightholes " << char(34) << "1" << char(34) << endl;
		outFi << "gl_max_size " << char(34) << "1024" << char(34) << endl;
		outFi << "gl_monolights " << char(34) << "0" << char(34) << endl;
		outFi << "gl_overbright " << char(34) << "0" << char(34) << endl;
		outFi << "gl_picmip " << char(34) << "0" << char(34) << endl;
		if (Video == "AMD") {
			outFi << "gl_polyoffset " << char(34) << "4" << char(34) << endl;
		}
		else if (Video == "NVIDIA") {
			outFi << "gl_polyoffset " << char(34) << "0.1" << char(34) << endl;
		}
		else {
			outFi << "gl_polyoffset " << char(34) << "1" << char(34) << endl;
		}
		outFi << "gl_round_down " << char(34) << "3" << char(34) << endl;
		outFi << "gl_spriteblend " << char(34) << "1" << char(34) << endl;
		outFi << "gl_texturemode " << char(34) << "GL_LINEAR_MIPMAP_LINEAR" << char(34) << endl;
		outFi << "gl_vsync " << char(34) << "1" << char(34) << endl;
		outFi << "gl_wateramp " << char(34) << "0" << char(34) << endl;
		outFi << "graphheight " << char(34) << "64.0" << char(34) << endl;
		outFi << "hisound " << char(34) << "1" << char(34) << endl;
		outFi << "hpk_maxsize " << char(34) << "0.001" << char(34) << endl;
		outFi << "hud_capturemouse " << char(34) << "1" << char(34) << endl;
		outFi << "hud_centerid " << char(34) << "0" << char(34) << endl;
		outFi << "hud_deathnotice_time " << char(34) << "6" << char(34) << endl;
		outFi << "hud_draw " << char(34) << "1" << char(34) << endl;
		outFi << "hud_fastswitch " << char(34) << "0" << char(34) << endl;
		outFi << "hud_saytext_internal " << char(34) << "1" << char(34) << endl;
		outFi << "hud_takesshots " << char(34) << "0" << char(34) << endl;
		outFi << "joystick " << char(34) << "0" << char(34) << endl;
		outFi << "lookspring " << char(34) << "0.000000" << char(34) << endl;
		outFi << "lookstrafe " << char(34) << "0.000000" << char(34) << endl;
		outFi << "lookstrafe " << char(34) << "0.000000" << char(34) << endl;
		outFi << "m_customaccel " << char(34) << "0" << char(34) << endl;
		outFi << "m_customaccel_exponent " << char(34) << "1" << char(34) << endl;
		outFi << "m_customaccel_max " << char(34) << "0" << char(34) << endl;
		outFi << "m_customaccel_scale " << char(34) << "0.04" << char(34) << endl;
		outFi << "m_filter " << char(34) << "0" << char(34) << endl;
		outFi << "m_forward " << char(34) << "1" << char(34) << endl;
		outFi << "m_mousethread_sleep " << char(34) << "1" << char(34) << endl;
		outFi << "m_pitch " << char(34) << "0.022" << char(34) << endl;
		outFi << "m_rawinput " << char(34) << "1" << char(34) << endl;
		outFi << "m_side " << char(34) << "0.8" << char(34) << endl;
		outFi << "m_yaw " << char(34) << "0.022" << char(34) << endl;
		outFi << "max_shells " << char(34) << "64.000000" << char(34) << endl;
		outFi << "max_smokepuffs " << char(34) << "64.000000" << char(34) << endl;
		outFi << "model " << char(34) << "gordon" << char(34) << endl;
		outFi << "MP3FadeTime " << char(34) << "2.0" << char(34) << endl;
		outFi << "MP3Volume " << char(34) << "0" << char(34) << endl;
		outFi << "mp_decals " << char(34) << "120.000000" << char(34) << endl;
		outFi << "name " << char(34) << "Friendly" << char(34) << endl;
		outFi << "net_graph " << char(34) << "1" << char(34) << endl;
		outFi << "net_graphpos " << char(34) << "1" << char(34) << endl;
		outFi << "net_scale " << char(34) << "5" << char(34) << endl;
		outFi << "r_detailtextures " << char(34) << "0" << char(34) << endl;
		outFi << "rate " << char(34) << "100000" << char(34) << endl;
		outFi << "room_off " << char(34) << "0" << char(34) << endl;
		outFi << "scoreboard_shortheaders " << char(34) << "0" << char(34) << endl;
		outFi << "scoreboard_showavatars " << char(34) << "1" << char(34) << endl;
		outFi << "scoreboard_showhealth " << char(34) << "1" << char(34) << endl;
		outFi << "scoreboard_showmoney " << char(34) << "1" << char(34) << endl;
		outFi << "sensitivity " << char(34) << "3.000000" << char(34) << endl;
		outFi << "skin " << char(34) << char(34) << endl;
		outFi << "sp_decals " << char(34) << "4096" << char(34) << endl;
		outFi << "spec_autodirector_internal " << char(34) << "1" << char(34) << endl;
		outFi << "spec_drawcone_internal " << char(34) << "1" << char(34) << endl;
		outFi << "spec_drawnames_internal " << char(34) << "1" << char(34) << endl;
		outFi << "spec_drawstatus_internal " << char(34) << "1" << char(34) << endl;
		outFi << "spec_mode_internal " << char(34) << "3" << char(34) << endl;
		outFi << "spec_pip " << char(34) << "0" << char(34) << endl;
		outFi << "suitvolume " << char(34) << "0.250000" << char(34) << endl;
		outFi << "sv_aim " << char(34) << "0" << char(34) << endl;
		outFi << "sv_voiceenable " << char(34) << "1" << char(34) << endl;
		outFi << "team " << char(34) << char(34) << endl;
		outFi << "topcolor " << char(34) << "30" << char(34) << endl;
		outFi << "viewsize " << char(34) << "120" << char(34) << endl;
		outFi << "violence_ablood " << char(34) << "1" << char(34) << endl;
		outFi << "violence_agibs " << char(34) << "1" << char(34) << endl;
		outFi << "violence_hblood " << char(34) << "1" << char(34) << endl;
		outFi << "violence_hgibs " << char(34) << "1" << char(34) << endl;
		outFi << "voice_enable " << char(34) << "1" << char(34) << endl;
		outFi << "voice_forcemicrecord " << char(34) << "1" << char(34) << endl;
		outFi << "voice_modenable " << char(34) << "1" << char(34) << endl;
		outFi << "voice_scale " << char(34) << "0.750000" << char(34) << endl;
		outFi << "volume " << char(34) << "0.220000" << char(34) << endl;
		outFi << "zoom_sensitivity_ratio " << char(34) << "1.2" << char(34) << endl;
		outFi << "setinfo " << char(34) << "_vgui_menus" << char(34) << " " << char(34) << "1" << char(34) << endl;
		outFi << "setinfo " << char(34) << "_ah" << char(34) << " " << char(34) << "1" << char(34) << endl;
		outFi << "setinfo " << char(34) << "_demorecorder" << char(34) << " " << char(34) << "2" << char(34) << endl;
		outFi << "+mlook" << endl;
		outFi.close();
	}
};
