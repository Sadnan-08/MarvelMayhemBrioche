#include "iGraphics.h"
#include "menu.hpp"

int loadingScreen;

// Loading screen variables
int loadingBarWidth = 0;
bool loadingDone = false;
bool goToMainMenu = false;
bool blinkTextWhite = true;

void iDraw()
{
	iClear();

	if (!goToMainMenu)
	{
		// Show loading screen
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, loadingScreen);

		// Loading bar frame and fill
		iSetColor(255, 255, 255);
		iRectangle(390, 100, 500, 30);
		iFilledRectangle(390, 100, loadingBarWidth, 30);

		// If loading done, show text prompt
		if (loadingDone){
			if (blinkTextWhite) {
				iSetColor(255, 255, 255); // white
			}
			else {
				iSetColor(0, 0, 0); // black
			}
			iText(530, 150, "Press SPACE to continue", GLUT_BITMAP_HELVETICA_18);
		}
		else{
			iSetColor(255, 255, 255);
			iText(390, 140, "Loading...", GLUT_BITMAP_HELVETICA_18);
		}
	}
	else
	{
		// Show the actual menu screen after loading
		showMenu();
	}

}


void iMouseMove(int mx, int my)
{

}


void iPassiveMouseMove(int mx, int my)
{

	if (goToMainMenu) {
		// By default, assume nothing is hovered
		hoveredButtonIndex = -1;
		hoveredOptionButtonIndex = -1;
		backButtonHover = false;

		if (currentScreen == -1) { // On the main menu
			for (int i = 0; i < BUTTON_COUNT; i++) {
				if (mx >= buttons[i].x && mx <= buttons[i].x + buttons[i].width &&
					my >= buttons[i].y && my <= buttons[i].y + buttons[i].height) {
					hoveredButtonIndex = i;
					break;
				}
			}
		}
		else if (currentScreen == 0) { // On the Play Sub-Menu
			// hover for the two option buttons
			for (int i = 0; i < 2; i++) {
				if (mx >= optionButtons[i].x && mx <= optionButtons[i].x + optionButtons[i].width &&
					my >= optionButtons[i].y && my <= optionButtons[i].y + optionButtons[i].height) {
					hoveredOptionButtonIndex = i;
					return; // Exit after finding a hover
				}
			}
			//hover for the back button
			if (mx >= backButton.x && mx <= backButton.x + backButton.width &&
				my >= backButton.y && my <= backButton.y + backButton.height) {
				backButtonHover = true;
			}
		}
		else { // On any other sub-screen (Settings, About, Option 1, Option 2)
			// back button hover
			if (mx >= backButton.x && mx <= backButton.x + backButton.width &&
				my >= backButton.y && my <= backButton.y + backButton.height) {
				backButtonHover = true;
			}
		}
	}
}


void iMouse(int button, int state, int mx, int my)
{
	if (goToMainMenu)
	{
		// Handle menu clicks only after the loading screen
		handleMenuClick(button, state, mx, my);
	}

}

// This function runs at a fixed interval
// Special Keys:
// GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6, GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12, 
// GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP, GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT

void fixedUpdate()
{
	// Game logic can go here for player movement etc.
	if (isKeyPressed('w') || isSpecialKeyPressed(GLUT_KEY_UP)) {}
	if (isKeyPressed('a') || isSpecialKeyPressed(GLUT_KEY_LEFT)) {}
	if (isKeyPressed('s') || isSpecialKeyPressed(GLUT_KEY_DOWN)) {}
	if (isKeyPressed('d') || isSpecialKeyPressed(GLUT_KEY_RIGHT)) {}



}

// Handles the loading bar animation
void loadingBar(){
	if (!loadingDone){

		loadingBarWidth += 5;
		if (loadingBarWidth >= 500){
			loadingBarWidth = 500;
			loadingDone = true;
		}
	}

	else{
		if (isKeyPressed(' ')){
			goToMainMenu = true;
			// Load menu 
			if (mainMenuScreen == -1)
			{
				loadMenuAssets();
				loadCharacterSelectionAssets();
			}
		}
	}
}

void toggleBlinkColor() {
	blinkTextWhite = !blinkTextWhite;
}

int main()
{
	// Initialize graphics window
	iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Marvel Mayhem");

	//loading screen background image
	loadingScreen = iLoadImage("BG/loading.png");

	iSetTimer(350, toggleBlinkColor); // 350 ms = 0.35 sec toggle

	iSetTimer(10, loadingBar);

	iStart(); // Start the graphics engine

	return 0;
}
