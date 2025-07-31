#ifndef MENU_HPP
#define MENU_HPP

#include <stdlib.h>
#include <stdio.h>

#define BUTTON_COUNT 4
#define CHARACTER_COUNT 6
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720


int currentScreen = -1;


// Main menu variables
int mainMenuScreen = -1;
int buttonImages[BUTTON_COUNT];
const char* buttonNames[BUTTON_COUNT] = { "Play", "Settings", "About", "Exit" };
int hoveredButtonIndex = -1;

//  Variables for the two options after clicking "Play"

int optionButtonImages[2];
int hoveredOptionButtonIndex = -1;
int subMenuBackground;

// Variables for character selection
int characterImages[CHARACTER_COUNT];
int selectedCharacterP1 = -1;
int selectedCharacterP2 = -1;

// Back button variables
int backButtonImage;
bool backButtonHover = false;


struct Button {
	int x;
	int y;
	int width;
	int height;
};

Button buttons[BUTTON_COUNT];
Button backButton;
Button optionButtons[2];
Button characterButtonsP1[CHARACTER_COUNT];
Button characterButtonsP2[CHARACTER_COUNT];


// menu 
void showMenu() {
	if (currentScreen == -1) { // On the Main Menu
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, mainMenuScreen);

		// main menu buttons 
		for (int i = 0; i < BUTTON_COUNT; i++) {
			iShowImage(buttons[i].x, buttons[i].y, buttons[i].width, buttons[i].height, buttonImages[i]);
		}
		if (hoveredButtonIndex != -1) {
			int i = hoveredButtonIndex;
			double zoomFactor = 1.1;
			int newWidth = buttons[i].width * zoomFactor;
			int newHeight = buttons[i].height * zoomFactor;
			int newX = buttons[i].x - (newWidth - buttons[i].width) / 2;
			int newY = buttons[i].y - (newHeight - buttons[i].height) / 2;
			iShowImage(newX, newY, newWidth, newHeight, buttonImages[i]);
		}
	}
	else if (currentScreen == 0) { // Play Sub-Menu
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, subMenuBackground);

		//two option buttons
		for (int i = 0; i < 2; i++) {
			iShowImage(optionButtons[i].x, optionButtons[i].y, optionButtons[i].width, optionButtons[i].height, optionButtonImages[i]);
		}

		//  hover effect for option buttons
		if (hoveredOptionButtonIndex != -1) {
			int i = hoveredOptionButtonIndex;
			double zoomFactor = 1.06;
			int newWidth = optionButtons[i].width * zoomFactor;
			int newHeight = optionButtons[i].height * zoomFactor;
			int newX = optionButtons[i].x - (newWidth - optionButtons[i].width) / 2;
			int newY = optionButtons[i].y - (newHeight - optionButtons[i].height) / 2;
			iShowImage(newX, newY, newWidth, newHeight, optionButtonImages[i]);
		}

		//  Back Button on this screen
		if (backButtonHover) {
			double zoomFactor = 1.1;
			int newWidth = backButton.width * zoomFactor;
			int newHeight = backButton.height * zoomFactor;
			int newX = backButton.x - (newWidth - backButton.width) / 2;
			int newY = backButton.y - (newHeight - backButton.height) / 2;
			iShowImage(newX, newY, newWidth, newHeight, backButtonImage);
		}
		else {
			iShowImage(backButton.x, backButton.y, backButton.width, backButton.height, backButtonImage);
		}
	}
	else if (currentScreen == 1 || currentScreen == 2) {
		iSetColor(255, 255, 255);
		iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		iSetColor(0, 0, 0);
		//iText(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2, buttonNames[currentScreen], GLUT_BITMAP_TIMES_ROMAN_24);

		// Back Button
		if (backButtonHover) {
			double zoomFactor = 1.1;
			int newWidth = backButton.width * zoomFactor;
			int newHeight = backButton.height * zoomFactor;
			int newX = backButton.x - (newWidth - backButton.width) / 2;
			int newY = backButton.y - (newHeight - backButton.height) / 2;
			iShowImage(newX, newY, newWidth, newHeight, backButtonImage);
		}
		else {
			iShowImage(backButton.x, backButton.y, backButton.width, backButton.height, backButtonImage);
		}
	}
	else if (currentScreen == 10 || currentScreen == 11) { // play options selection
		iSetColor(255, 255, 255);
		iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

		// Display which option was chosen
		if (currentScreen == 10) {
			iSetColor(255, 255, 255);
			iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

			// Titles
			iSetColor(0, 0, 0);
			iText(100, SCREEN_HEIGHT - 40, "Player 1: Choose Your Character", GLUT_BITMAP_HELVETICA_18);
			iText(SCREEN_WIDTH - 450, SCREEN_HEIGHT - 40, "Player 2: Choose Your Character", GLUT_BITMAP_HELVETICA_18);

			// Player 1 Side (Left)
			for (int i = 0; i < CHARACTER_COUNT; i++) {
				Button b = characterButtonsP1[i];
				iShowImage(b.x, b.y, b.width, b.height, characterImages[i]);

				
			}

			// Player 2 Side (Right)
			for (int i = 0; i < CHARACTER_COUNT; i++) {
				Button b = characterButtonsP2[i];
				iShowImage(b.x, b.y, b.width, b.height, characterImages[i]);

				
			}

		}
		else iText(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2, "Option 2 Screen", GLUT_BITMAP_TIMES_ROMAN_24);

		// Back Button
		if (backButtonHover) {
			double zoomFactor = 1.1;
			int newWidth = backButton.width * zoomFactor;
			int newHeight = backButton.height * zoomFactor;
			int newX = backButton.x - (newWidth - backButton.width) / 2;
			int newY = backButton.y - (newHeight - backButton.height) / 2;
			iShowImage(newX, newY, newWidth, newHeight, backButtonImage);
		}
		else {
			iShowImage(backButton.x, backButton.y, backButton.width, backButton.height, backButtonImage);
		}
	}
	
}


void handleMenuClick(int button, int state, int mx, int my) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (currentScreen == -1) { // On the main menu
			for (int i = 0; i < BUTTON_COUNT; i++) {
				if (mx >= buttons[i].x && mx <= buttons[i].x + buttons[i].width &&
					my >= buttons[i].y && my <= buttons[i].y + buttons[i].height) {
					if (i == 3) { exit(0); } // Exit button
					currentScreen = i; // Sets screen to 0 (Play), 1 (Settings), or 2 (About)
					break;
				}
			}
		}
		else if (currentScreen == 0) { // On the Play Sub-Menu
			// Check for clicks on the two option buttons
			for (int i = 0; i < 2; i++) {
				if (mx >= optionButtons[i].x && mx <= optionButtons[i].x + optionButtons[i].width &&
					my >= optionButtons[i].y && my <= optionButtons[i].y + optionButtons[i].height) {
					currentScreen = 10 + i; // Set screen to 10 or 11
					return; // Exit function after handling click
				}
			}
			// Check for click on the back button
			if (mx >= backButton.x && mx <= backButton.x + backButton.width &&
				my >= backButton.y && my <= backButton.y + backButton.height) {
				currentScreen = -1; // Go back to the main menu
			}
		}
		else if (currentScreen == 1 || currentScreen == 2) { // On Settings or About

			// Check for back button click
			if (mx >= backButton.x && mx <= backButton.x + backButton.width &&
				my >= backButton.y && my <= backButton.y + backButton.height) {
				currentScreen = -1; // Go back to the main menu
			}
		}
		else if (currentScreen == 10 || currentScreen == 11) { // On final placeholder screens
			// Check for back button click
			if (mx >= backButton.x && mx <= backButton.x + backButton.width &&
				my >= backButton.y && my <= backButton.y + backButton.height) {
				currentScreen = 0; // Go back to the Play Sub-Menu
			}
		}
		else if (currentScreen == 10) {
			// Player 1 selection
			for (int i = 0; i < CHARACTER_COUNT; i++) {
				if (mx >= characterButtonsP1[i].x && mx <= characterButtonsP1[i].x + characterButtonsP1[i].width &&
					my >= characterButtonsP1[i].y && my <= characterButtonsP1[i].y + characterButtonsP1[i].height) {
					selectedCharacterP1 = i;
					if (selectedCharacterP1 == i) {
						iSetColor(0, 255, 0); // green border
						iRectangle(characterButtonsP1[i].x - 2, characterButtonsP1[i].y - 2, characterButtonsP1[i].width + 4, characterButtonsP1[i].height + 4);
					}
					printf("Player 1 selected character %d\n", i);
					return;
				}
			}

			// Player 2 selection
			for (int i = 0; i < CHARACTER_COUNT; i++) {
					if (mx >= characterButtonsP2[i].x && mx <= characterButtonsP2[i].x + characterButtonsP2[i].width && 
						my >= characterButtonsP2[i].y && my <= characterButtonsP2[i].y + characterButtonsP2[i].height) {
					selectedCharacterP2 = i;
					if (selectedCharacterP2 == i) {
						iSetColor(255, 0, 0); // red border
						iRectangle(characterButtonsP2[i].x - 2, characterButtonsP2[i].y - 2, characterButtonsP2[i].width + 4, characterButtonsP2[i].height + 4);
					}
					printf("Player 2 selected character %d\n", i);
					return;
				}
			}

			// Back
			if (mx >= backButton.x && mx <= backButton.x + backButton.width &&
				my >= backButton.y && my <= backButton.y + backButton.height) {
				currentScreen = 0;
				selectedCharacterP1 = -1;
				selectedCharacterP2 = -1;
			}
		}
	}
}

// Load all images and set button positions
void loadMenuAssets() {
	mainMenuScreen = iLoadImage("BG/main.png");
	subMenuBackground = iLoadImage("BG/main.png");

	// Load Back button image and define its properties
	backButtonImage = iLoadImage("UiElements/backButton.png");
	backButton.x = 30;
	backButton.y = 30;
	backButton.width = 195;
	backButton.height = 75;

	optionButtonImages[0] = iLoadImage("BG/modeSelection1.png");
	optionButtonImages[1] = iLoadImage("BG/modeSelection2.jpg");

	// two option buttons
	int optWidth = 600;
	int optHeight = 400;
	int spacing = 20;
	int totalWidth = (optWidth * 2) + spacing;
	int startX = (SCREEN_WIDTH - totalWidth) / 2;

	optionButtons[0].x = startX;
	optionButtons[0].y = (SCREEN_HEIGHT - optHeight) / 2;
	optionButtons[0].width = optWidth;
	optionButtons[0].height = optHeight;

	optionButtons[1].x = startX + optWidth + spacing;
	optionButtons[1].y = (SCREEN_HEIGHT - optHeight) / 2;
	optionButtons[1].width = optWidth;
	optionButtons[1].height = optHeight;


	// main menu buttons
	char imagePath[100];
	int startY = 525;
	for (int i = 0; i < BUTTON_COUNT; i++) {
		sprintf_s(imagePath, sizeof(imagePath), "UiElements/button%d.png", i + 1);
		buttonImages[i] = iLoadImage(imagePath);

		buttons[i].x = 100;
		buttons[i].y = startY - i * 140;
		buttons[i].width = 300;
		buttons[i].height = 117;
	}

	
}

void loadCharacterSelectionAssets() {
	// Load character images
	for (int i = 0; i < CHARACTER_COUNT; i++) {
		char imagePath[100];
		sprintf_s(imagePath, sizeof(imagePath), "Characters/char%d.jpg", i + 1);
		characterImages[i] = iLoadImage(imagePath);
	}

	// Position settings
	int charWidth = 100, charHeight = 100;
	int spacingX = 80, spacingY = 50;
	int cols = 2, rows = 3;

	// total width and height of the grid
	int totalWidth = 250;
	int totalHeight = 400;

	// Starting positions to center the grid vertically
	int startY = (SCREEN_HEIGHT - totalHeight) / 2;
	int startX_P1 = 150; // Player 1's grid starts 150px from the left
	int startX_P2 = SCREEN_WIDTH - 150 - totalWidth; // Player 2's grid starts 150px from right

	for (int i = 0; i < CHARACTER_COUNT; i++) {
		int row = i / cols;
		int col = i % cols;

		// Player 1 (Left Side)
		characterButtonsP1[i].x = startX_P1 + col * (charWidth + spacingX);
		characterButtonsP1[i].y = startY + (rows - 1 - row) * (charHeight + spacingY);
		characterButtonsP1[i].width = charWidth;
		characterButtonsP1[i].height = charHeight;

		// Player 2 (Right Side)
		characterButtonsP2[i].x = startX_P2 + col * (charWidth + spacingX);
		characterButtonsP2[i].y = characterButtonsP1[i].y; // Align with P1
		characterButtonsP2[i].width = charWidth;
		characterButtonsP2[i].height = charHeight;
	}
}

#endif 
