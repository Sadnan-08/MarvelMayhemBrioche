#ifndef SELECTIONMENU_HPP
#define SELECTIONMENU_HPP

#include "menu.hpp"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

// Render Option 1 or Option 2 selection screen
void showSelectionMenu() {
	iSetColor(255, 255, 255);
	iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	iSetColor(0, 0, 0);

	// Display selected option text
	if (currentScreen == 10) {
		iText(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2, "Option 1 Screen", GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else if (currentScreen == 11) {
		iText(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2, "Option 2 Screen", GLUT_BITMAP_TIMES_ROMAN_24);
	}

	// Back button rendering with hover effect
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

// Handle mouse click on Option 1 / Option 2 screens
void handleSelectionMenuClick(int mx, int my) {
	if (mx >= backButton.x && mx <= backButton.x + backButton.width &&
		my >= backButton.y && my <= backButton.y + backButton.height) {
		currentScreen = 0; // Go back to the Play Sub-Menu
	}
}


#endif