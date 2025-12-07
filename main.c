#include <raylib.h>
#include <stdio.h>
#include <stdint.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

void initStuff();
void drawArray(int *arr, int size, uint8_t hightlight, Vector2 pointers);
void drawPointers(uint8_t i, uint8_t j);
void drawSwitchBridge(uint8_t i, uint8_t j);

// array component attributes
// 	element container
const int rectWidth = 80;
const int rectHeight = 60;
//	element value data
const int fontSize = 26;
//	position
int rectX = (int)(SCREEN_WIDTH * 1/6.) - 10;
int rectY = (int)(SCREEN_HEIGHT/2. - rectHeight/2.);

int main(void) {
	int arr[6] = {1, 2, 13, 5, 16, 10};
	// int arr[9] = {1, 20, 2, 5, 16, 8, 0, 1, 7};
	int arraySize = sizeof(arr)/sizeof(arr[0]);

	initStuff();

	int i = 0;
	int j = i + 1;
	int switched = 0;
    while (!WindowShouldClose()) {
		// check input
		Vector2 pointers = {i, j};
		if (IsKeyPressed(KEY_SPACE)) {
			j++;
			if (i == arraySize-2) {
				break; // breaks the whole loop
			}
			if (j == arraySize) {
				i++;
				j = i+1;
			}

			// change array
			if (arr[i] >= arr[j]) {
				arr[i] = arr[i] ^ arr[j];
				arr[j] = arr[i] ^ arr[j];
				arr[i] = arr[i] ^ arr[j];
				switched = 1;
			} else {
				switched = 0;
			}
		}

		BeginDrawing();
			ClearBackground(BLACK);
			drawArray(arr, arraySize, switched, pointers);
			drawPointers(i, j);
		EndDrawing();
    }

    CloseWindow();

    return 0;
}

void initStuff() {
	SetTargetFPS(60);
    InitWindow(800, 450, "vizzz");
}

void drawArray(int *arr, int size, uint8_t highlight, Vector2 pointers) {
	for (int i=0; i<size; i++) {
		int elementXMove = (rectWidth + 10) * i;
		int elementTextX = rectX + ((rectWidth - fontSize) / 2.) + 3;
		int elementTextY = rectY + ((rectHeight - fontSize) / 2.) + 3;
		char elementText[10];

		sprintf(elementText, "%d", arr[i]);

		DrawRectangle(rectX + elementXMove, rectY, rectWidth, rectHeight, BLUE);
		DrawText(elementText, elementTextX + elementXMove, elementTextY, fontSize, GREEN);
		if (highlight) {
			if (i == pointers.x || i == pointers.y) {
				DrawText(elementText, elementTextX + elementXMove, elementTextY, fontSize, RED);
			}
		}
	}
}

void drawPointers(uint8_t i, uint8_t j) {
	int elementIMove = (rectWidth + 10) * i;
	int elementJMove = (rectWidth + 10) * j;
	int elementIX = rectX + ((rectWidth - fontSize) / 2.) + 3;
	int elementJX = rectX + ((rectWidth - fontSize) / 2.) + 3;
	int elementY = rectY - rectHeight;
	char msgI[10];
	char msgJ[10];

	sprintf(msgI, "i=%d", i);
	sprintf(msgJ, "j=%d", j);

	DrawText(msgI, elementIX + elementIMove, elementY, fontSize, YELLOW);
	DrawText(msgJ, elementJX + elementJMove, elementY, fontSize, YELLOW);
}
