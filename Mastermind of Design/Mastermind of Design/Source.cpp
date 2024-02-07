// اللهم صلِ وسلم وبارك علي سيدنا محمد صلي الله عليه وسلم // 
#define _CRT_SECURE_NO_WARNINGS
#include "Manufacturing management.h"
#include<iostream>
#include <stdlib.h>
#include<conio.h>
#include<windows.h>
#include<stdio.h>
#include<process.h>
#include<vector>
#include<thread>
#include<chrono>
#include <random>
#include <ctime>
#include<queue>


using namespace std;
#define fast ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);cin.exceptions(ios::badbit | ios::failbit);
#define endl "\n";
void color(int cnt) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cnt);
}
void menu(int pos) {
	int mx_size = 5;
	vector<string> v = { "Add product .", "Delete product .", "Search product .","Production all products .", "Exit ." };

	cout << "Menu of industrial" << endl;
	cout << "******************" << endl;
	for (auto i = 0; i < mx_size; ++i) {
		if (pos == i) {
			cout << "\033[48;5;166m";
			cout << v[i] << endl;
			cout << "\033[0m";
		}
		else {
			cout << v[i] << endl;
		}
	}
}
Manufacturing_management MM;
int Menu() {
	system("cls");
	int i = 0;
	char ch;
	menu(0);

	while (true) {
		
		ch = _getch();

		switch (ch) {
		case 27:
			exit(0);
			break;
		case 72: // UP
			system("cls");
			i = (i - 1 + 5) % 5;
			menu(i);
			break;
		case 80: // DOWN
			system("cls");
			i = (i + 1) % 5;
			menu(i);
			break;
		case '\r': // Enter
			return i;
		default:
			break;
		}
	}
}
void Handle_Menu() {

	while (true) {
		system("cls");

		int i = Menu();

		switch (i) {
		case 0:
			MM.add_product();
			break;
		case 1:
			MM.delete_product();
			system("pause");
			break;
		case 2:
			MM.search_product();
			system("pause");
			break;
		case 3:
			MM.production_all_product();
			system("pause");
			break;
		default:
			system("cls");
			cout << "THANK YOU" << endl;
			return;
		}
	}
}


void hideCursor() { cout << "\033[?25l"; }
void showCursor() { cout << "\033[?25h"; }
void Bold_and_underline_txt() { cout << "\033[1;4m"; }
void reset_setting_default() { cout << "\033[0m"; }
void move_cursor_row_colmn() { cout << "\033[10;20H"; /* Move the cursor 10 row && 20 colmn*/}
void display_loading_animation() {
	cout << "Loading: ";
	for (int i = 0; i < 30; ++i) {
		cout << "\033[44m "; // Blue background
		cout << "\033[0m";   // Reset attributes
		cout << "\033[46m "; // Cyan background
		this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	cout << '\n' << endl;
}
void display_rotation_line_animation() {
	for (int i = 0; i < 10; ++i) {
		cout << "-";
		this_thread::sleep_for(std::chrono::milliseconds(200));
		cout << "\b";
		cout << "\\";
		this_thread::sleep_for(std::chrono::milliseconds(200));
		cout << "\b";
		cout << "|";
		this_thread::sleep_for(std::chrono::milliseconds(200));
		cout << "\b";
		cout << "/";
		this_thread::sleep_for(std::chrono::milliseconds(200));
		cout << "\b";
	}
	cout << '\n' << endl;
}
void Another_display_rotation_line_animation_loading() {
	const int numFrames = 4; // Number of animation frames
	const char frames[numFrames] = { '|', '/', '-', '\\' }; // Characters for each frame

	int frameIndex = 0; // Current frame index

	int cnt = 0;
	while (cnt++ <= 20) {
		// Clear the screen
		std::cout << "\033[2J";

		// Move cursor to the center of the screen
		std::cout << "\033[" << 12 << ";" << 35 << "H";

		// Display the rotating frame
		std::cout << frames[frameIndex] << " Loading...";

		// Update frame index
		frameIndex = (frameIndex + 1) % numFrames;

		// Wait for a short duration
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
}
void Loading2() {
	const int width = 40; // Width of the progress bar

	for (int progress = 0; progress <= width; ++progress) {
		// Clear the screen
		std::cout << "\033[2J";

		// Move cursor to the center of the screen
		std::cout << "\033[" << 1 << ";" << 2 << "H";

		// Display the progress bar
		std::cout << "[";

		for (int i = 0; i < width; ++i) {
			if (i < progress) {
				std::cout << "=";
			}
			else if (i == progress) {
				std::cout << ">";
			}
			else {
				std::cout << " ";
			}
		}

		std::cout << "] " << (progress * 100 / width) << "%";

		// Wait for a short duration
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	// Move to a new line after completion
	std::cout << '\n' << "Loading complete!" << endl;
}
void Clock_time() {
	while (true) {
		// Get the current time
		time_t now = time(0);
		tm* ltm = localtime(&now);

		// Clear the screen
		cout << "\033[2J";

		// Move cursor to the center of the screen
		cout << "\033[" << 1 << ";" << 90 << "H";

		// Display the digital clock
		cout << "Current Time: ";
		cout << (ltm->tm_hour < 10 ? "0" : "") << ltm->tm_hour << ":";
		cout << (ltm->tm_min < 10 ? "0" : "") << ltm->tm_min << ":";
		cout << (ltm->tm_sec < 10 ? "0" : "") << ltm->tm_sec;

		// Wait for a second
		this_thread::sleep_for(std::chrono::seconds(1));
	}
}
void Nested_loading() {
	const int barWidth = 40;

	while (true) {
		for (int i = 0; i <= barWidth; ++i) {
			float progress = static_cast<float>(i) / barWidth * 100;

			std::cout << "\r[";
			for (int j = 0; j < barWidth; ++j) {
				if (j < i) std::cout << "=";
				else std::cout << " ";
			}
			std::cout << "] " << static_cast<int>(progress) << "%";
			std::cout.flush();

			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
		std::cout << endl;
	}
}
void LOADING() {
	const int width = 50;

	while (true) {
		for (int i = 0; i <= width; ++i) {
			std::cout << "[" << std::string(i, '=') << std::string(width - i, ' ') << "]" << i * 2 << "%" << "\r";
			std::cout.flush();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}
}

int main()
{
	Handle_Menu();
	return 0;
}