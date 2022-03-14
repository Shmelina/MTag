#include "Graphics.h"

Graphics::Graphics()
{
	factory = NULL;
	rendertarget = NULL;
	brush = NULL;
	text_factory = NULL;
	text_format = NULL;
	text_format_center = NULL;
	StrokeStyle = NULL;
	StrokeStyle2 = NULL;
	wrong_file = NULL;
	text_format_lyrics = NULL;
}

Graphics::~Graphics()
{
	if (factory) factory->Release();
	if (rendertarget) rendertarget->Release();
	if (brush) brush->Release();
	if (text_factory) text_factory->Release();
	if (text_format) text_format->Release();
	if (text_format_center) text_format_center->Release();
	if (text_format_lyrics) text_format_lyrics->Release();
	if (StrokeStyle) StrokeStyle->Release();
	if (StrokeStyle2) StrokeStyle2->Release();
	if (wrong_file) wrong_file->Release();
}

bool Graphics::Init(HWND windowhandle)
{
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE::D2D1_FACTORY_TYPE_MULTI_THREADED, &factory);
	if (res != S_OK)
		return false;

	RECT rect;
	GetClientRect(windowhandle, &rect);

	res = factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(windowhandle, D2D1::SizeU(rect.right, rect.bottom)),
		&rendertarget);

	if (res != S_OK)
		return false;

	res = rendertarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &brush);

	if (res != S_OK)
		return false;

	res = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(text_factory),
		reinterpret_cast<IUnknown**>(&text_factory)
	);

	res = text_factory->CreateTextFormat(
		L"Verdana",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		16,
		L"Cyrl", //locale
		&text_format
	);
	if (res != S_OK)
		return false;

	text_format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_JUSTIFIED);

	text_format->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

	res = text_factory->CreateTextFormat(
		L"Verdana",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		16,
		L"Cyrl", //locale
		&text_format_center
	);
	if (res != S_OK)
		return false;

	text_format_center->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

	text_format_center->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

	res = text_factory->CreateTextFormat(
		L"Verdana",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		16,
		L"Cyrl", //locale
		&text_format_lyrics
	);
	if (res != S_OK)
		return false;

	text_format_lyrics->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_JUSTIFIED);

	text_format_lyrics->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);

	float dashes[] = { 0.0f/*, 34.0f, 34.0f/*, 12.0f, 8.0f, 8.0f */ };

	res = factory->CreateStrokeStyle(
		D2D1::StrokeStyleProperties(
			D2D1_CAP_STYLE_FLAT,
			D2D1_CAP_STYLE_FLAT,
			D2D1_CAP_STYLE_ROUND,
			D2D1_LINE_JOIN_MITER,
			10.0f,
			D2D1_DASH_STYLE_CUSTOM,
			0.0f),
		dashes,
		ARRAYSIZE(dashes),
		&StrokeStyle
	);

	if (res != S_OK)
		return false;

	float dashes2[] = { 5.0f, 5.0f, 5.0f/*, 12.0f, 8.0f, 8.0f */ };

	res = factory->CreateStrokeStyle(
		D2D1::StrokeStyleProperties(
			D2D1_CAP_STYLE_FLAT,
			D2D1_CAP_STYLE_FLAT,
			D2D1_CAP_STYLE_ROUND,
			D2D1_LINE_JOIN_MITER,
			10.0f,
			D2D1_DASH_STYLE_CUSTOM,
			0.0f),
		dashes2,
		ARRAYSIZE(dashes),
		&StrokeStyle2
	);

	if (res != S_OK)
		return false;

	wrong_file = load_bitmap_from_file(L"data/wrong_image.jpg");

	return true;
}

void Graphics::ClrScr(float r, float g, float b)
{
	rendertarget->Clear(D2D1::ColorF(r, g, b));
}

void Graphics::ClrScr(Color4f color)
{
	rendertarget->Clear(color);
}


void Graphics::DrawCircle(float x, float y, FLOAT radius, float r, float g, float b, float a)
{
	brush->SetColor(D2D1::ColorF(r, g, b, a));
	rendertarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush, 3.0f);
	brush->SetColor(D2D1::ColorF(1, 1, 1, a));
	rendertarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush);
}

void Graphics::DrawCircle(Coordinate coord, FLOAT radius, Color4f color)
{
	D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2F(coord.X, coord.Y), radius, radius);
	brush->SetColor(color);
	rendertarget->DrawEllipse(ellipse, brush, 3.0f);
	brush->SetColor(D2D1::ColorF(1.0f, 1.0f, 1.0f, color.a));
	rendertarget->FillEllipse(ellipse, brush);
}

void Graphics::DrawTextM(string str, float x, float y, float w, float h, Color4f color)
{
	wstring wstr = wstring(str.begin(), str.end());
	CONST WCHAR* ch = wstr.c_str();
	brush->SetColor(color);
	rendertarget->DrawTextW(ch, (UINT32)wcslen(ch), text_format, D2D1::RectF(x - w, y - h, x + w, y + h), brush);
	//rendertarget->DrawRectangle(D2D1::Rect(x - w, y - h, x + w, y + h), brush, 1.0f, StrokeStyle);
}

void Graphics::DrawTextCenterM(string str, float x, float y, float w, float h, Color4f color)
{
	wstring wstr = wstring(str.begin(), str.end());
	CONST WCHAR* ch = wstr.c_str();
	brush->SetColor(color);
	rendertarget->DrawTextW(ch, (UINT32)wcslen(ch), text_format_center, D2D1::RectF(x - w, y - h, x + w, y + h), brush);
}

void Graphics::DrawTextM(wstring str, Coordinate position, Coordinate size, Color4f color)
{
	wstring tmp;
	if (str.size() > size.X / 10)
	{
		tmp = str.substr(0, (size_t)floor(size.X / 10 - 4));
		tmp += wstring(3, '.');
	}
	else
		tmp = str;
	CONST WCHAR* ch = tmp.c_str();
	brush->SetColor(color);
	rendertarget->DrawTextW(ch, (UINT32)wcslen(ch), text_format, D2D1::RectF(position.X - size.X / 2, position.Y - size.Y / 2, position.X + size.X / 2, position.Y + size.Y / 2), brush);
	//rendertarget->DrawRectangle(D2D1::RectF(position.X - size.X / 2, position.Y - size.Y / 2, position.X + size.X / 2, position.Y + size.Y / 2), brush, 1.0f, StrokeStyle);
}

void Graphics::DrawTextLyricsM(wstring str, Coordinate position, Coordinate size, Color4f color)
{
	CONST WCHAR* ch = str.c_str();
	brush->SetColor(color);
	rendertarget->DrawTextW(ch, (UINT32)wcslen(ch), text_format_lyrics, D2D1::RectF(position.X - size.X / 2, position.Y - size.Y / 2, position.X + size.X / 2, position.Y + size.Y / 2), brush);
}

void Graphics::DrawTextCenterM(wstring str, Coordinate position, Coordinate size, Color4f color)
{
	CONST WCHAR* ch = str.c_str();
	brush->SetColor(color);
	rendertarget->DrawTextW(ch, (UINT32)wcslen(ch), text_format_center, D2D1::RectF(position.X - size.X / 2, position.Y - size.Y / 2, position.X + size.X / 2, position.Y + size.Y / 2), brush);
}

void Graphics::DrawTextM(string str, Coordinate position, Coordinate size, Color4f color)
{
	wstring wstr = wstring(str.begin(), str.end());
	CONST WCHAR* ch = wstr.c_str();
	brush->SetColor(color);
	rendertarget->DrawTextW(ch, (UINT32)wcslen(ch), text_format, D2D1::RectF(position.X - size.X / 2, position.Y - size.Y / 2, position.X + size.X / 2, position.Y + size.Y / 2), brush);
}

void Graphics::DrawTextM(float i, float x, float y, float w, float h, Color4f color)
{
	string str = to_string(i);
	wstring wstr = wstring(str.begin(), str.end());
	CONST WCHAR* ch = wstr.c_str();
	brush->SetColor(D2D1::ColorF(color.r, color.g, color.b, color.a));
	rendertarget->DrawTextW(ch, (UINT32)wcslen(ch), text_format, D2D1::RectF(x - w, y - h, x + w, y + h), brush);
}

void Graphics::DrawTextM(int i, float x, float y, float w, float h, Color4f color)
{
	string str = to_string(i);
	wstring wstr = wstring(str.begin(), str.end());
	CONST WCHAR* ch = wstr.c_str();
	brush->SetColor(color);
	rendertarget->DrawTextW(ch, (UINT32)wcslen(ch), text_format, D2D1::RectF(x - w, y - h, x + w, y + h), brush);
}

void Graphics::DrawLine(Coordinate c1, Coordinate c2, Color4f color)
{
	brush->SetColor(color);
	rendertarget->DrawLine(D2D1::Point2F(c1.X, c1.Y), D2D1::Point2F(c2.X, c2.Y), brush, 2.0f, StrokeStyle);
}

void Graphics::DrawLine(float x1, float y1, float x2, float y2, Color4f color)
{
	DrawLine(Coordinate(x1, y1), Coordinate(x2, y2), color);
}

void Graphics::DrawHalfDuplex(float x1, float y1, float x2, float y2, Color4f color)
{
	brush->SetColor(color);
	rendertarget->DrawLine(D2D1::Point2F(x1, y1), D2D1::Point2F(x2, y2), brush, 2.0f, StrokeStyle2);
}

void Graphics::DrawRect(float x1, float y1, float x2, float y2, float r, float g, float b, float a)
{
	brush->SetColor(D2D1::ColorF(r, g, b, a));
	rendertarget->DrawRectangle(D2D1::Rect(x1, y1, x2, y2), brush, 1.0f, StrokeStyle);
	brush->SetColor(D2D1::ColorF(1, 1, 1, a));
	rendertarget->FillRectangle(D2D1::Rect(x1, y1, x2, y2), brush);
}

void Graphics::DrawFilledRect(float x1, float y1, float x2, float y2, Color4f color)
{
	brush->SetColor(D2D1::ColorF(0.0f, 0.0f, 0.0f, 1.0f));
	rendertarget->DrawRectangle(D2D1::Rect(x1, y1, x2, y2), brush, 1.0f, StrokeStyle);
	brush->SetColor(color);
	rendertarget->FillRectangle(D2D1::Rect(x1, y1, x2, y2), brush);
}

ID2D1Bitmap* Graphics::load_bitmap_from_file(wstring name)
{
	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pSource = NULL;
	IWICStream* pStream = NULL;
	IWICFormatConverter* pConverter = NULL;
	IWICBitmapScaler* pScaler = NULL;

	IWICImagingFactory* pIWICFactory = nullptr;

	HRESULT cr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory, (LPVOID*)&pIWICFactory);

	if (!SUCCEEDED(hr))
	{
		return nullptr;
	}

	ID2D1Bitmap* Bitmap = nullptr;

	PCWSTR pname = name.c_str();

	hr = pIWICFactory->CreateDecoderFromFilename(
		pname,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);

	if (SUCCEEDED(hr))
	{
		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
	}

	if (SUCCEEDED(hr))
	{

		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = pIWICFactory->CreateFormatConverter(&pConverter);

	}


	if (SUCCEEDED(hr))
	{
		hr = pConverter->Initialize(
			pSource,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			0.f,
			WICBitmapPaletteTypeMedianCut
		);
	}

	if (SUCCEEDED(hr))
	{

		// Create a Direct2D bitmap from the WIC bitmap.
		hr = rendertarget->CreateBitmapFromWicBitmap(
			pConverter,
			&Bitmap
		);
	}

	if (pIWICFactory) pIWICFactory->Release();
	if (pDecoder) pDecoder->Release();
	if (pSource) pSource->Release();
	if (pStream) pStream->Release();
	if (pConverter) pConverter->Release();
	if (pScaler) pScaler->Release();
	if (Bitmap != nullptr)
		return Bitmap;
	return nullptr;
}

void Graphics::DrawBitmap(float x, float y, float w, float h, ID2D1Bitmap* image)
{
	ID2D1Bitmap* tmp = nullptr;
	if (image != nullptr)
	{
		tmp = image;
	}
	else
	{
		tmp = wrong_file;
	}
	float cl = tmp->GetSize().width / 2;
	float ch = tmp->GetSize().height / 2;
	rendertarget->DrawRectangle(D2D1::RectF(x - w / 2, y - h / 2, x + w / 2, y + h / 2), brush, 1.0f, StrokeStyle);
	if (cl > ch)
		rendertarget->DrawBitmap(tmp, D2D1::RectF(x - w / 2, y - h / 2, x + w / 2, y + h / 2), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(cl - ch, ch - ch, cl + ch, ch + ch));
	else
		rendertarget->DrawBitmap(tmp, D2D1::RectF(x - w / 2, y - h / 2, x + w / 2, y + h / 2), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(cl - cl, ch - cl, cl + cl, ch + cl));
}

bool operator==(const Color4f& CL, const Color4f& CR)
{
	if (CL.r == CR.r && CL.g == CR.g && CL.b == CR.b && CL.a == CR.a)
		return true;
	return false;
}

bool operator==(const Coordinate& CL, const Coordinate& CR)
{
	if (CL.X == CR.X && CL.Y == CR.Y)
		return true;
	return false;
}