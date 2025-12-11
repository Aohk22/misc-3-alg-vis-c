#include <raylib.h>
#include <stdio.h>
#include <stdint.h>
#include "elements.c"

#define SCREEN_WIDTH 850
#define SCREEN_HEIGHT 470
#define FONT_SIZE 26


void drawArray(ArrayElm *arrElm, uint8_t highlight, Vector2 pointers, int padding);
void drawPointers(ArrayElm *arrElm, uint8_t i, uint8_t j, int padding);

void initStuff() {
	SetTargetFPS(60);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "vizzz");
}

int main(void) {
	int arr[6] = {1, 2, 13, 5, 16, 10};
	const int arraySize = sizeof(arr)/sizeof(arr[0]);
	const int screenMiddleX = SCREEN_WIDTH*1/2.;
	const int screenMiddleY = SCREEN_HEIGHT*1/2.;
	const int boxWidth = 50;
	const int boxHeight = 50;
	ArrayElm *arrElm = newArrayElement(
			arr, arraySize,
			(Vector2){boxWidth, boxHeight}, 
			(Vector2){screenMiddleX - (boxWidth/2.) * arraySize, screenMiddleY},
			FONT_SIZE
	);

	initStuff();

	int i = 0;
	int j = i + 1;
	int switched = 0;
	char *algName = "Selection sort.";
	const Vector2 algNamePosition = {
		.x = (SCREEN_WIDTH/2.)-(6*FONT_SIZE), // 6-7 is about half the text len
		.y = SCREEN_HEIGHT*1/6.
	};
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

		// draw stuff
		BeginDrawing();
			ClearBackground(BLACK);
			DrawText(algName, algNamePosition.x, algNamePosition.y, FONT_SIZE, WHITE);
			drawArray(arrElm, switched, pointers, 5);
			drawPointers(arrElm, i, j, 5);
		EndDrawing();
    }

    CloseWindow();

    return 0;
}

void drawPointers(ArrayElm *arrElm, uint8_t i, uint8_t j, int padding) {
	char msgI[10];
	char msgJ[10];

	sprintf(msgI, "i=%d", i);
	sprintf(msgJ, "j=%d", j);

	int posY = arrElm->base.y - arrElm->rectSize.y;
	int baseX = arrElm->base.x + ((arrElm->rectSize.x - 1*arrElm->textSize) / 2.);
	int iPosX = (arrElm->rectSize.x + padding) * i + baseX;
	int jPosX = (arrElm->rectSize.x + padding) * j + baseX;

	DrawText(msgI, iPosX, posY, FONT_SIZE, YELLOW);
	DrawText(msgJ, jPosX, posY, FONT_SIZE, YELLOW);
}
