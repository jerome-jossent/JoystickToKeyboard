#define WINVER 0x0500
#include <windows.h>
#include "CXBOXController.h"
#include "ConsoleApplication1.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

CXBOXController* Player1;
INPUT ip;
int main()
{
	int id = -1;
	Player1 = new CXBOXController(id);
	while (!Player1->IsConnected())
	{
		id++;
		Player1 = new CXBOXController(id);
	}
	cout << "GamePad numero ";
	cout << id;
	cout << " sends Key :\n";

	SHORT seuil = 20000;

	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	HKL kbl = GetKeyboardLayout(0);
	unsigned char
		L_U, L_L, L_D, L_R, L_T,
		R_U, R_L, R_D, R_R, R_T,
		D_U, D_L, D_D, D_R,
		A, B, X, Y,
		Back, Start,
		L_S, R_S;
	string touches;

	int i = 0;
	cout << "\nSaisir dans l'ordre \n";
	cout << "Joystick gauche HAUT, BAS, GAUCHE, DROITE, CLIC,\n";
	cout << "Joystick droit  HAUT, BAS, GAUCHE, DROITE, CLIC,\n";
	cout << "Croix	     HAUT, BAS, GAUCHE, DROITE,\n";
	cout << "A, B, X, Y,\nBack, Start,\n";
	cout << "Back, Start,\n";
	cout << "Gauche, Droit\n";
	cout << "Terminer par entrer.\n";
	getline(cin, touches);
	if (touches == "")
		touches = "m:wx          *    p  ";

	//bind
	L_U = VkKeyScanEx(touches[i++], kbl);
	L_D = VkKeyScanEx(touches[i++], kbl);
	L_L = VkKeyScanEx(touches[i++], kbl);
	L_R = VkKeyScanEx(touches[i++], kbl);
	L_T = VkKeyScanEx(touches[i++], kbl);

	R_U = VkKeyScanEx(touches[i++], kbl);
	R_D = VkKeyScanEx(touches[i++], kbl);
	R_L = VkKeyScanEx(touches[i++], kbl);
	R_R = VkKeyScanEx(touches[i++], kbl);
	R_T = VkKeyScanEx(touches[i++], kbl);

	D_U = VkKeyScanEx(touches[i++], kbl);
	D_D = VkKeyScanEx(touches[i++], kbl);
	D_L = VkKeyScanEx(touches[i++], kbl);
	D_R = VkKeyScanEx(touches[i++], kbl);

	A = VkKeyScanEx(touches[i++], kbl);
	B = VkKeyScanEx(touches[i++], kbl);
	X = VkKeyScanEx(touches[i++], kbl);
	Y = VkKeyScanEx(touches[i++], kbl);
	Back = VkKeyScanEx(touches[i++], kbl);
	Start = VkKeyScanEx(touches[i++], kbl);
	L_S = VkKeyScanEx(touches[i++], kbl);
	R_S = VkKeyScanEx(touches[i++], kbl);

	//http://www.kbdedit.com/manual/low_level_vk_list.html
	while (true)
	{
		if (Player1->IsConnected())
		{
			BYTE XL = Player1->GetState().Gamepad.bLeftTrigger;

			SHORT XL = Player1->GetState().Gamepad.sThumbLX;
			SHORT YL = Player1->GetState().Gamepad.sThumbLY;
			if (XL < -seuil) sendKeyDown(L_L); else sendKeyUp(L_L);
			if (XL > seuil) sendKeyDown(L_R); else sendKeyUp(L_R);
			if (YL < -seuil) sendKeyDown(L_D); else sendKeyUp(L_D);
			if (YL > seuil)	sendKeyDown(L_U); else sendKeyUp(L_U);
			if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) sendKeyDown(L_T); else sendKeyUp(L_T);

			SHORT XR = Player1->GetState().Gamepad.sThumbRX;
			SHORT YR = Player1->GetState().Gamepad.sThumbRY;
			if (XR < -seuil) sendKeyDown(R_L); else sendKeyUp(R_L);
			if (XR > seuil) sendKeyDown(R_R); else sendKeyUp(R_R);
			if (YR < -seuil) sendKeyDown(R_D); else sendKeyUp(R_D);
			if (YR > seuil)	sendKeyDown(R_U); else sendKeyUp(R_U);
			if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) sendKeyDown(R_T); else sendKeyUp(R_T);

			if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) sendKeyDown(D_L); else sendKeyUp(D_L);
			if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) sendKeyDown(D_R); else sendKeyUp(D_R);
			if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) sendKeyDown(D_U); else sendKeyUp(D_U);
			if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) sendKeyDown(D_D); else sendKeyUp(D_D);

			if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A) sendKeyDown(A); else sendKeyUp(A);
			if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_B) sendKeyDown(B); else sendKeyUp(B);
			if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_X) sendKeyDown(X); else sendKeyUp(X);
			if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_Y) sendKeyDown(Y); else sendKeyUp(Y);

			if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) sendKeyDown(L_S); else sendKeyUp(L_S);
			if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) sendKeyDown(R_S); else sendKeyUp(R_S);

			if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_BACK) sendKeyDown(Back); else sendKeyUp(Back);
			if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_START) sendKeyDown(Start); else sendKeyUp(Start);

		}
		else
		{
			std::cout << "\n\tERROR! - Controller Not Found!\n";
			std::cout << "Press Any Key To Exit.";
			std::cin.get();
			break;
		}

		Sleep(10);
	}

#pragma region Touche => vibration
	std::cout << "Instructions:\n";
	std::cout << "[A] Vibrate Left Only\n";
	std::cout << "[B] Vibrate Right Only\n";
	std::cout << "[X] Vibrate Both\n";
	std::cout << "[Y] Vibrate Neither\n";
	std::cout << "[BACK] Exit\n";

	while (true)
	{
		if (Player1->IsConnected())
		{
			if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A)
			{
				Player1->Vibrate(65535, 0);
			}

			if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_B)
			{
				Player1->Vibrate(0, 65535);
			}

			if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_X)
			{
				Player1->Vibrate(65535, 65535);
			}

			if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_Y)
			{
				Player1->Vibrate();
			}

			if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
			{
				break;
			}
		}
		else
		{
			std::cout << "\n\tERROR! PLAYER 1 - XBOX 360 Controller Not Found!\n";
			std::cout << "Press Any Key To Exit.";
			std::cin.get();
			break;
		}
	}

	delete(Player1);

	return(0);
#pragma endregion
}

void sendKeyDown(unsigned char keyCode)
{
	ip.ki.wVk = keyCode;
	ip.ki.dwFlags = 0;
	SendInput(1, &ip, sizeof(INPUT));
	//INPUT input;
	//input.type = INPUT_KEYBOARD;

	//input.ki.wScan = 0; // hardware scan code for key
	//input.ki.wVk = keyCode;
	//input.ki.dwFlags = 0;
	//input.ki.time = 0;
	//input.ki.dwExtraInfo = 0;

	//SendInput(1, &input, sizeof(INPUT));
}

void sendKeyUp(unsigned char keyCode)
{
	ip.ki.wVk = keyCode;
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
	//INPUT input;
	//input.type = INPUT_KEYBOARD;

	//input.ki.wVk = keyCode;
	//input.ki.dwFlags = KEYEVENTF_KEYUP;
	//input.ki.time = 0;
	//input.ki.dwExtraInfo = 0;

	//SendInput(1, &input, sizeof(INPUT));
}
