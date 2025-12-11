#include <raylib.h>

void selection() {
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
}
