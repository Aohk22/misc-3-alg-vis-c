#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	Rectangle rect;
	int data;
	int fontSize;
} ElementFrame;

typedef struct {
	Rectangle rect;
	ElementFrame *efs;
	int size;
} ArrayFrame;

ArrayFrame *NewArrayFrame(int *arr, int arrLen, int x, int y, int elementHeight, int elementWidth, int margin, int padding, int fontSize) {
	ArrayFrame *pAF = malloc(sizeof(ArrayFrame));
	pAF->efs = malloc(sizeof(ElementFrame)*arrLen);

	pAF->size = arrLen;
	pAF->rect = (Rectangle) { .x = x, .y = y, .width = elementWidth*arrLen+2*margin+padding*(arrLen), .height = elementHeight+2*margin };
	for (int i = 0; i < arrLen; i++) {
		pAF->efs[i] = (ElementFrame) {
			.rect = {
				.x = x+margin+((elementWidth+padding)*i),
				.y = y+margin,
				.width = elementWidth,
				.height = elementHeight,
			},
			.data = *(arr+i),
			.fontSize = fontSize,
		};
	}

	return pAF;
}

void DestroyElementFrame(ElementFrame *ef) {
	free(ef);
}

void DestroyArrayFrame(ArrayFrame *af) {
	free(af->efs);
	free(af);
}

void DrawElementFrame(ElementFrame *ef) {
	char text[10];
	sprintf(text, "%d", ef->data);

	DrawRectangleRec(ef->rect, BLUE);
	DrawText(
			text,
			(int)ef->rect.x + (ef->rect.width-ef->fontSize)/2.,
			(int)ef->rect.y + (ef->rect.height-ef->fontSize)/2.,
			ef->fontSize, ORANGE);
}

void DrawArrayFrame(ArrayFrame *af) {
	DrawRectangleRec(af->rect, GREEN);
	for (int i = 0; i < af->size; i++) {
		DrawElementFrame(&af->efs[i]);
	}
}

int main(void) {
	int array[7] = {1, 2, 43, 4, 5, 6, 7};
	int len = sizeof(array)/sizeof(int);
	ArrayFrame *pAF = NewArrayFrame(
			array, len, 
			150, 300, // x, y
			40, 50, // height, width
			4, 4, 20 // margin, padding, font size
	);

	SetTargetFPS(60);
	InitWindow(700, 600, "a;dlfkj");

	while (!WindowShouldClose()) {
		BeginDrawing();
			DrawArrayFrame(pAF);
		EndDrawing();
	}

	DestroyArrayFrame(pAF);

	return 0;
}

