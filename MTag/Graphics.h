#pragma once

#include <Windows.h>
#include <d2d1.h>
#include <dwrite.h>
#include <iostream>
#include <string>
#include <wincodec.h>
#include <wincodecsdk.h>
#include <Objbase.h>

#pragma comment(lib, "windowscodecs.lib")

using namespace std;

class Color4f : public D2D1_COLOR_F
{
public:
	Color4f()
	{
		r = 0.0f;
		g = 0.0f;
		b = 0.0f;
		a = 0.0f;
	};
	Color4f(float R, float G, float B, float A)
	{
		r = R;
		b = B;
		g = G;
		a = A;
	};
	friend bool operator== (const Color4f& CL, const Color4f& CR);
};

class Coordinate
{
public:
	float X;
	float Y;
	Coordinate(float x, float y) : X(x), Y(y) {}
	Coordinate() : X(0.0f), Y(0.0f) {}
	void Set_Coordinate(float x, float y)
	{
		X = x;
		Y = y;
	}
	friend bool operator== (const Coordinate& CL, const Coordinate& CR);
};

class Graphics
{
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* rendertarget;
	ID2D1SolidColorBrush* brush;
	IDWriteFactory* text_factory;
	IDWriteTextFormat* text_format;
	IDWriteTextFormat* text_format_center;
	IDWriteTextFormat* text_format_lyrics;
	ID2D1StrokeStyle* StrokeStyle;
	ID2D1StrokeStyle* StrokeStyle2;
	ID2D1Bitmap* wrong_file;
public:
	Graphics();
	~Graphics();

	bool Init(HWND windowHandle);
	void BeginDraw()
	{
		rendertarget->BeginDraw();
	}
	void EndDraw()
	{
		rendertarget->EndDraw();
	}

	void ClrScr(float r, float g, float b);
	void ClrScr(Color4f color);
	void DrawCircle(float x, float y, FLOAT radius, float r, float g, float b, float a);
	void DrawCircle(Coordinate coord, FLOAT radius, Color4f color);
	void DrawTextM(string str, float x, float y, float w, float h, Color4f color);
	void DrawTextCenterM(string str, float x, float y, float w, float h, Color4f color);
	void DrawTextM(wstring str, Coordinate position, Coordinate size, Color4f color);
	void DrawTextCenterM(wstring str, Coordinate position, Coordinate size, Color4f color);
	void DrawTextLyricsM(wstring str, Coordinate position, Coordinate size, Color4f color);
	void DrawTextM(string str, Coordinate position, Coordinate size, Color4f color);
	void DrawTextM(float i, float x, float y, float w, float h, Color4f color);
	void DrawTextM(int i, float x, float y, float w, float h, Color4f color);
	void DrawLine(Coordinate c1, Coordinate c2, Color4f color);
	void DrawLine(float x1, float y1, float x2, float y2, Color4f color);
	void DrawHalfDuplex(float x1, float y1, float x2, float y2, Color4f color);
	void DrawRect(float x1, float y1, float x2, float y2, float r, float g, float b, float a);
	//void DrawRect(Coordinate c1, Coordinate c2, Color4f color);
	void DrawFilledRect(float x1, float y1, float x2, float y2, Color4f color);
	ID2D1Bitmap* load_bitmap_from_file(wstring name);
	void DrawBitmap(float x, float y, float w, float h, ID2D1Bitmap* image);
};