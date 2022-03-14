#pragma once
#include "framework.h"
#include "Graphics.h"

using namespace std;

class Menue
{
public:

	wstring text;

	Coordinate left_top_corner;

	float Heigth;
	float Length;

	bool isopen;
	bool hovered;

	map<int, wstring> menue;
	bool popup;
	bool active;
	Menue(wstring menu_title, Coordinate position, float h, float l, bool p)
	{
		text = menu_title;
		left_top_corner = position;
		Heigth = h;
		Length = l;
		isopen = false;
		popup = p;
		hovered = false;
		active = true;
	}
	Menue(wstring menu_title, float left_top_x, float left_top_y, float h, float l)
	{
		text = menu_title;
		left_top_corner.Set_Coordinate(left_top_x, left_top_y);
		Heigth = h;
		Length = l;
		popup = false;
		isopen = false;
		hovered = false;
		active = true;
	}
	void add_entry(wstring text, int Case)
	{
		menue[Case] = text;
	}
	void render(Graphics* G)
	{
		if (active)
		{
			G->DrawRect(left_top_corner.X, left_top_corner.Y, left_top_corner.X + Length, left_top_corner.Y + Heigth, 0, 0, 0, 1);
			G->DrawTextCenterM(text, Coordinate(left_top_corner.X + Length / 2, left_top_corner.Y + Heigth / 2), Coordinate(Length, Heigth), Color4f(0, 0, 0, 1));
			int in = 1;
			if (isopen)
			{
				if (popup)
				{
					for (auto i : menue)
					{
						G->DrawRect(left_top_corner.X, left_top_corner.Y + in * Heigth, left_top_corner.X + Length, left_top_corner.Y + (in + 1) * Heigth, 0, 0, 0, 1);
						G->DrawTextCenterM(i.second, Coordinate(left_top_corner.X + Length / 2, left_top_corner.Y + in * Heigth + Heigth / 2), Coordinate(Length, Heigth), Color4f(0, 0, 0, 1));;
						in++;
					}
				}
				else
				{
					for (auto i : menue)
					{
						G->DrawRect(left_top_corner.X, left_top_corner.Y - (in - 1) * Heigth, left_top_corner.X + Length, left_top_corner.Y - in * Heigth, 0, 0, 0, 1);
						G->DrawTextCenterM(i.second, Coordinate(left_top_corner.X + Length / 2, left_top_corner.Y - in * Heigth + Heigth / 2), Coordinate(Length, Heigth), Color4f(0, 0, 0, 1));
						in++;
					}
				}
			}
		}
		else
		{
			G->DrawRect(left_top_corner.X, left_top_corner.Y, left_top_corner.X + Length, left_top_corner.Y + Heigth, 0.5, 0.5, 0.5, 1);
			G->DrawTextCenterM(text, Coordinate(left_top_corner.X + Length / 2, left_top_corner.Y + Heigth / 2), Coordinate(Length, Heigth), Color4f(0.5, 0.5, 0.5, 1));
		}
	}
	int select(float x, float y)
	{
		int in = 1;
		if (isopen && !hovered)
		{
			if (popup)
			{
				for (auto& i : menue)
				{
					if (area(x, y, left_top_corner.X, left_top_corner.Y + in * Heigth, left_top_corner.X + Length, left_top_corner.Y + (in + 1) * Heigth))
					{
						isopen = false;
						set_name(i.second);
						return i.first;
					}
					in++;
				}
			}
			else
			{
				for (auto& i : menue)
				{
					if (area(x, y, left_top_corner.X, left_top_corner.Y - in * Heigth, left_top_corner.X + Length, left_top_corner.Y))
					{
						isopen = false;
						set_name(i.second);
						return i.first;
					}
					in++;
				}
			}
		}
		return -1;
	}
	void set_name(wstring str)
	{
		text = str;
	}
	void set_name(int str)
	{
		text = to_wstring(str);
	}

	void open(float x, float y)
	{
		if (!hovered && area(x, y, left_top_corner.X, left_top_corner.Y, left_top_corner.X + Length, left_top_corner.Y + Heigth))
			isopen = !isopen;
	}

	bool area(float x, float y, float x1, float y1, float x2, float y2)
	{
		if (x1 < x && x < x2)
			if (y2 > y && y > y1)
				return true;
		return false;
	}
};

class Check_box
{
public:
	Coordinate left_top_corner;
	float Heigth;
	float Length;
	bool active;
	float x1, x2, x3, y1, y2, y3;

	Check_box(Coordinate position, float h, float l)
	{
		left_top_corner = position;
		Heigth = h;
		Length = l;
		active = false;
		x1 = left_top_corner.X + Length / 2;
		y1 = left_top_corner.Y + Heigth - 2;
		x2 = left_top_corner.X + 2;
		y2 = left_top_corner.Y + 2;
		x3 = left_top_corner.X + Length - 2;
		y3 = left_top_corner.Y + 2;
	}

	void render(Graphics* G)
	{
		G->DrawRect(left_top_corner.X, left_top_corner.Y, left_top_corner.X + Length, left_top_corner.Y + Heigth, 0, 0, 0, 1);
		if (active)
		{
			G->DrawLine(x1, y1, x2, y2, Color4f(0, 0, 0, 1));
			G->DrawLine(x1, y1, x3, y3, Color4f(0, 0, 0, 1));
		}
	}

	void check(float x, float y)
	{
		if (area(x, y, left_top_corner.X, left_top_corner.Y, left_top_corner.X + Length, left_top_corner.Y + Heigth))
			active = !active;
	}

	bool area(float x, float y, float x1, float y1, float x2, float y2)
	{
		if (x1 < x && x < x2)
			if (y2 > y && y > y1)
				return true;
		return false;
	}
};

class Button
{
public:
	bool condition;
	Coordinate left_top_corner;
	Coordinate move_dist;
	float Heigth;
	float Length;
	float x1, x2, x3, y1, y2, y3;
	wstring text1, text2, text;
	bool active;
	bool hovered;

	Button(Coordinate position, wstring name1, wstring name2, float h, float l)
	{
		condition = false;
		text = name1;
		text1 = name1;
		text2 = name2;
		left_top_corner = position;
		Heigth = h;
		Length = l;
		active = false;
		hovered = false;
		x1 = left_top_corner.X + Length;
		y1 = left_top_corner.Y + Heigth;
		x2 = left_top_corner.X + 2;
		y2 = left_top_corner.Y + 2;
		x3 = left_top_corner.X + Length - 2;
		y3 = left_top_corner.Y + 2;
		move_dist = Coordinate(0, 0);
	}

	void render(Graphics* G)
	{
		if (active && !hovered)
		{
			G->DrawRect(left_top_corner.X + move_dist.X, left_top_corner.Y + move_dist.Y, left_top_corner.X + Length + move_dist.X, left_top_corner.Y + Heigth + move_dist.Y, 0, 0, 0, 1);
			G->DrawTextCenterM(text, Coordinate(left_top_corner.X + Length / 2 + move_dist.X, left_top_corner.Y + Heigth / 2 + move_dist.Y), Coordinate(Length, Heigth), Color4f(0, 0, 0, 1));
		}
		else
		{
			G->DrawRect(left_top_corner.X + move_dist.X, left_top_corner.Y + move_dist.Y, left_top_corner.X + Length + move_dist.X, left_top_corner.Y + Heigth + move_dist.Y, 0.5, 0.5, 0.5, 1);
			G->DrawTextCenterM(text, Coordinate(left_top_corner.X + Length / 2 + move_dist.X, left_top_corner.Y + Heigth / 2 + move_dist.Y), Coordinate(Length, Heigth), Color4f(0.5, 0.5, 0.5, 1));
		}
	}

	bool check(float x, float y)
	{
		if (active && !hovered && area(x, y, left_top_corner.X + move_dist.X, left_top_corner.Y + move_dist.Y, left_top_corner.X + Length + move_dist.X, left_top_corner.Y + Heigth + move_dist.Y))
		{
			if (condition)
				text = text1;
			else
				text = text2;
			condition = !condition;
			return true;
		}
		return false;
	}

	void move(float x, float y)
	{
		move_dist.X = x;
		move_dist.Y = y;
	}

	void set_condition(bool cond)
	{
		if (cond)
			text = text1;
		else
			text = text2;
		condition = cond;
	}

	bool area(float x, float y, float x1, float y1, float x2, float y2)
	{
		if (x1 < x && x < x2)
			if (y2 > y && y > y1)
				return true;
		return false;
	}
};

class Button_Area
{
public:
	bool condition;
	Coordinate left_top_corner;
	Coordinate move_dist;
	float Heigth;
	float Length;
	float x1, x2, x3, y1, y2, y3;
	bool active;

	Button_Area(Coordinate position, float h, float l)
	{
		condition = false;
		left_top_corner = position;
		Heigth = h;
		Length = l;
		active = true;
		x1 = left_top_corner.X + Length;
		y1 = left_top_corner.Y + Heigth;
		x2 = left_top_corner.X + 2;
		y2 = left_top_corner.Y + 2;
		x3 = left_top_corner.X + Length - 2;
		y3 = left_top_corner.Y + 2;
		move_dist = Coordinate(0, 0);
	}

	void render(Graphics* G)
	{
		if (condition)
		{
			G->DrawRect(left_top_corner.X + move_dist.X, left_top_corner.Y + move_dist.Y, left_top_corner.X + Length + move_dist.X, left_top_corner.Y + Heigth + move_dist.Y, 0, 0, 0, 1);
			G->DrawFilledRect(left_top_corner.X + move_dist.X, left_top_corner.Y + move_dist.Y, left_top_corner.X + Length + move_dist.X, left_top_corner.Y + Heigth + move_dist.Y, Color4f(0.9f, 0.9f, 0.9f, 1.0f));
		}
		else
		{
			G->DrawRect(left_top_corner.X + move_dist.X, left_top_corner.Y + move_dist.Y, left_top_corner.X + Length + move_dist.X, left_top_corner.Y + Heigth + move_dist.Y, 0.5f, 0.5f, 0.5f, 1.0f);
		}
	}

	bool check(float x, float y, bool is_controled)
	{
		if (active && area(x, y, left_top_corner.X + move_dist.X, left_top_corner.Y + move_dist.Y, left_top_corner.X + Length + move_dist.X, left_top_corner.Y + Heigth + move_dist.Y))
		{
			condition = !condition;
			return true;
		}
		else
		{
			if (!is_controled)
				condition = false;
			return false;
		}
	}

	void move(float x, float y)
	{
		move_dist.X = x;
		move_dist.Y = y;
	}

	void set_condition(bool cond)
	{
		condition = cond;
	}

	bool get_condition()
	{
		return condition;
	}

	bool area(float x, float y, float x1, float y1, float x2, float y2)
	{
		if (x1 < x && x < x2)
			if (y2 > y && y > y1)
				return true;
		return false;
	}
};

class Massage
{
public:
	Coordinate left_top_corner;
	float Heigth;
	float Length;
	float x1, x2, x3, y1, y2, y3;
	wstring* Text;
	bool active;

	Massage(Coordinate position, wstring* text, float l, float h)
	{
		Text = text;
		left_top_corner = position;
		Heigth = h;
		Length = l;
		active = false;
		x1 = left_top_corner.X + Length;
		y1 = left_top_corner.Y + Heigth;
		x2 = left_top_corner.X + 2;
		y2 = left_top_corner.Y + 2;
		x3 = left_top_corner.X + Length - 2;
		y3 = left_top_corner.Y + 2;
	}

	void render(Graphics* G)
	{
		if (Text != nullptr && active)
		{
			G->DrawRect(left_top_corner.X, left_top_corner.Y, left_top_corner.X + Length, left_top_corner.Y + Heigth, 0, 0, 0, 1);
			G->DrawRect(left_top_corner.X + Length - 20, left_top_corner.Y, left_top_corner.X + Length, left_top_corner.Y + 20, 0, 0, 0, 1);
			G->DrawLine(left_top_corner.X + Length - 18, left_top_corner.Y + 2, left_top_corner.X + Length - 2, left_top_corner.Y + 18, Color4f(0, 0, 0, 1));
			G->DrawLine(left_top_corner.X + Length - 2, left_top_corner.Y + 2, left_top_corner.X + Length - 18, left_top_corner.Y + 18, Color4f(0, 0, 0, 1));
			G->DrawTextCenterM(*Text, Coordinate(left_top_corner.X + Length / 2, left_top_corner.Y + Heigth / 2), Coordinate(Length - 40, Heigth - 40), Color4f(0, 0, 0, 1));
		}
	}

	void check(float x, float y)
	{
		if (active && area(x, y, left_top_corner.X + Length - 20, left_top_corner.Y, left_top_corner.X + Length, left_top_corner.Y + 20))
		{
			active = false;
		}
	}

	void set_active(bool is_active)
	{
		active = is_active;
	}

	void set_massage(wstring* text)
	{
		Text = text;
		active = true;
	}

	bool area(float x, float y, float x1, float y1, float x2, float y2)
	{
		if (x1 < x && x < x2)
			if (y2 > y && y > y1)
				return true;
		return false;
	}
};

class Table
{
public:
	Coordinate center;
	int count;
	size_t size;
	bool active;
	vector<string>* records;
	size_t wheel;
	float width;
	Table(Coordinate C, int Count, float Width)
	{
		records = NULL;
		size = -1;
		active = true;
		wheel = 0;
		center = C;
		count = Count;
		width = Width;
	}

	void Update_Records(vector<string>* rc)
	{
		records = rc;
		if (records != NULL)
			size = records->size();
		wheel = 0;
	}

	void Update_Wheel(size_t New)
	{
		if (size > count && wheel + New >= 0 && wheel + New + count <= size)
		{
			wheel += New;
		}
	}

	void Render(Graphics* G)
	{
		if (active)
		{
			G->DrawRect(center.X + width, center.Y - 10, center.X + width + 10, center.Y + 20 * (count)-10, 0, 0, 0, 1);
			float scale = ((float)count / (float)size) * 20.0f;
			if (scale > 20 || scale < 0)
				scale = 20;
			G->DrawRect(center.X - width, center.Y - 10, center.X + width - 1, center.Y + 20 * (count)-10, 0, 0, 0, 1);
			G->DrawRect(center.X + width + 1, center.Y - 10 + wheel * scale + 1, center.X + width + 10 - 1, center.Y + (wheel + count) * scale - 11, 0, 0, 0, 1);
			if (records != NULL && size > 0)
			{
				int iter = 0;
				int it = 0;
				for (auto& i : *records)
				{
					if (iter >= wheel && iter < wheel + count)
					{
						float y = center.Y + 20.0f * it;
						G->DrawTextM(i, center.X, y, width, 10, Color4f(0, 0, 0, 1));
						it++;
					}
					iter++;
				}
			}
		}
	}
};

class InputString_Int
{
public:
	Coordinate left_top_corner;
	float Heigth;
	float Length;
	float x1, x2, x3, y1, y2, y3;
	string text;
	int* value;
	string buf;
	bool active;
	void(*func)();

	InputString_Int(string name, int* Value, Coordinate position, float h, float l, void(*function)())
	{
		text = name;
		value = Value;
		left_top_corner = position;
		Heigth = h;
		Length = l;
		active = false;
		func = function;
		buf = to_string(*value);
		x1 = left_top_corner.X + Length;
		y1 = left_top_corner.Y + Heigth;
		x2 = left_top_corner.X + 2;
		y2 = left_top_corner.Y + 2;
		x3 = left_top_corner.X + Length - 2;
		y3 = left_top_corner.Y + 2;
	}

	void render(Graphics* G)
	{
		if (active)
		{
			G->DrawRect(left_top_corner.X, left_top_corner.Y, left_top_corner.X + Length, left_top_corner.Y + Heigth, 0, 0, 0, 1);
			G->DrawTextM(*value, left_top_corner.X + Length / 2, left_top_corner.Y + Heigth / 2, Length / 2, Heigth / 2, Color4f(0, 0, 0, 1));
		}
		else
		{
			G->DrawRect(left_top_corner.X, left_top_corner.Y, left_top_corner.X + Length, left_top_corner.Y + Heigth, 0, 0, 0, 1);
			G->DrawTextM(text, left_top_corner.X + Length / 2, left_top_corner.Y + Heigth / 2, Length / 2, Heigth / 2, Color4f(0, 0, 0, 1));
		}
	}

	void check(float x, float y)
	{
		if (area(x, y, left_top_corner.X, left_top_corner.Y, left_top_corner.X + Length, left_top_corner.Y + Heigth))
		{
			buf = to_string(*value);
			active = true;
		}
		else
		{
			*value = stoi(buf);
			active = false;
		}
	}

	void set_condition(wchar_t ch)
	{
		if (active)
		{
			if (ch > 95 && ch < 106)
			{
				buf += ch - 48;
				*value = stoi(buf);
			}
			else
			{
				if (ch == 8)
				{

					if (buf.size() > 0)
					{
						buf.pop_back();
						if (buf.size() > 0)
						{
							*value = stoi(buf);
						}
						else
						{
							*value = 0;
							buf = '0';
						}
					}
					else
						*value = 0;
				}
				else
				{
					if (ch == 13)
					{
						*value = stoi(buf);
						active = false;
						func();
					}
				}
			}
		}
	}

	bool area(float x, float y, float x1, float y1, float x2, float y2)
	{
		if (x1 < x && x < x2)
			if (y2 > y && y > y1)
				return true;
		return false;
	}
};

class InputString_WString
{
public:
	Coordinate left_top_corner;
	Coordinate move_dist;
	float Heigth;
	float Length;
	float x1, x2, x3, y1, y2, y3;
	wstring* value;
	wstring text;
	wstring buf;
	bool active;

	InputString_WString()
	{
		value = nullptr;
		left_top_corner = Coordinate(0,0);
		Heigth = 0;
		Length = 0;
		active = false;
		buf = L"";
		*value = buf;
		text = L"";
		x1 = left_top_corner.X + Length;
		y1 = left_top_corner.Y + Heigth;
		x2 = left_top_corner.X + 2;
		y2 = left_top_corner.Y + 2;
		x3 = left_top_corner.X + Length - 2;
		y3 = left_top_corner.Y + 2;
		move_dist = Coordinate(0, 0);
	}

	InputString_WString(wstring* Value, wstring ext_text, Coordinate position, float h, float l)
	{
		value = Value;
		left_top_corner = position;
		Heigth = h;
		Length = l;
		active = false;
		buf = *value;
		text = ext_text;
		x1 = left_top_corner.X + Length;
		y1 = left_top_corner.Y + Heigth;
		x2 = left_top_corner.X + 2;
		y2 = left_top_corner.Y + 2;
		x3 = left_top_corner.X + Length - 2;
		y3 = left_top_corner.Y + 2;
		move_dist = Coordinate(0, 0);
	}

	void render(Graphics* G)
	{
		if (active)
		{
			G->DrawRect(left_top_corner.X + move_dist.X - 1, left_top_corner.Y + move_dist.Y - 1, left_top_corner.X + Length + move_dist.X + 1, left_top_corner.Y + Heigth + move_dist.Y + 1, 0, 0, 0, 0.75);
			G->DrawRect(left_top_corner.X + move_dist.X, left_top_corner.Y + move_dist.Y, left_top_corner.X + Length + move_dist.X, left_top_corner.Y + Heigth + move_dist.Y, 0, 0, 0, 1);
			if (value->size() > 0)
				G->DrawTextM(*value, Coordinate(left_top_corner.X + Length / 2 + move_dist.X, left_top_corner.Y + Heigth / 2 + move_dist.Y), Coordinate(Length, Heigth), Color4f(0, 0, 0, 1));
			else
				G->DrawTextM(text, Coordinate(left_top_corner.X + Length / 2 + move_dist.X, left_top_corner.Y + Heigth / 2 + move_dist.Y), Coordinate(Length, Heigth), Color4f(0, 0, 0, 0.25));
		}
		else
		{
			G->DrawRect(left_top_corner.X + move_dist.X, left_top_corner.Y + move_dist.Y, left_top_corner.X + Length + move_dist.X, left_top_corner.Y + Heigth + move_dist.Y, 0, 0, 0, 1);
			if (value->size() > 0)
				G->DrawTextM(*value, Coordinate(left_top_corner.X + Length / 2 + move_dist.X, left_top_corner.Y + Heigth / 2 + move_dist.Y), Coordinate(Length, Heigth), Color4f(0, 0, 0, 1));
			else
				G->DrawTextM(text, Coordinate(left_top_corner.X + Length / 2 + move_dist.X, left_top_corner.Y + Heigth / 2 + move_dist.Y), Coordinate(Length, Heigth), Color4f(0, 0, 0, 0.5));
		}
	}

	void check(float x, float y)
	{
		if (area(x, y, left_top_corner.X + move_dist.X, left_top_corner.Y + move_dist.Y, left_top_corner.X + Length + move_dist.X, left_top_corner.Y + Heigth + move_dist.Y))
		{
			buf = *value;
			active = true;
		}
		else
		{
			if (active) 
			{
				*value = buf;
				active = false;
			}
		}
	}

	bool set_condition(wstring data)
	{
		if (active)
		{
			buf += data;
			*value = buf;
		}
		return false;
	}

	void move(float x, float y)
	{
		move_dist.X = x;
		move_dist.Y = y;
	}

	wstring get_data()
	{
		if (active)
			return buf;
		return L"";
	}

	bool set_condition(wchar_t ch, bool is_shifted)
	{
		if (active)
		{
			/*if (is_shifted)
			{
				if (ch > 64 && ch < 91)
				{
					buf += (char)ch;
					*value = buf;
					return false;
				}
			}
			else
			{
				if (ch > 64 && ch < 91)
				{
					buf += ch + 32;
					*value = buf;
					return false;
				}
			}

			if (ch == 190)
			{
				buf += '.';
				*value = buf;
				return false;
			}

			if (ch > 47 && ch < 59)
			{
				buf += (char)ch;
				*value = buf;
				return false;
			}

			if (ch > 95 && ch < 106)
			{
				buf += ch - 48;
				*value = buf;
			}
			else
			{
				if (ch == 8)
				{

					if (buf.size() > 0)
					{
						buf.pop_back();
						if (buf.size() > 0)
						{
							*value = buf;
						}
						else
						{
							*value = L"";
						}
					}
					else
						*value = L"";
				}
				else
				{
					if (ch == 13)
					{
						*value = buf;
						active = false;
						return true;
					}
				}
			}*/
			switch (ch)
			{
			case 8:
			{
				if (buf.size() > 0)
				{
					buf.pop_back();
					if (buf.size() > 0)
					{
						*value = buf;
					}
					else
					{
						*value = L"";
					}
				}
				else
					*value = L"";
			}
			break;
			case 13:
			{
				*value = buf;
				active = false;
				return true;
			}
			break;
			default:
			{
				buf += (wchar_t)ch;
				*value = buf;
			}
			}

		}
		return false;
	}

	bool area(float x, float y, float x1, float y1, float x2, float y2)
	{
		if (x1 < x && x < x2)
			if (y2 > y && y > y1)
				return true;
		return false;
	}
};

class InputString_Lyrics
{
public:
	Coordinate left_top_corner;
	Coordinate move_dist;
	float Heigth;
	float Length;
	float x1, x2, x3, y1, y2, y3;
	wstring* value;
	wstring text;
	wstring buf;
	bool active;

	InputString_Lyrics()
	{
		value = nullptr;
		left_top_corner = Coordinate(0, 0);
		Heigth = 0;
		Length = 0;
		active = false;
		buf = L"";
		*value = buf;
		text = L"";
		x1 = left_top_corner.X + Length;
		y1 = left_top_corner.Y + Heigth;
		x2 = left_top_corner.X + 2;
		y2 = left_top_corner.Y + 2;
		x3 = left_top_corner.X + Length - 2;
		y3 = left_top_corner.Y + 2;
		move_dist = Coordinate(0, 0);
	}

	InputString_Lyrics(wstring* Value, wstring ext_text, Coordinate position, float h, float l)
	{
		value = Value;
		left_top_corner = position;
		Heigth = h;
		Length = l;
		active = false;
		buf = *value;
		text = ext_text;
		x1 = left_top_corner.X + Length;
		y1 = left_top_corner.Y + Heigth;
		x2 = left_top_corner.X + 2;
		y2 = left_top_corner.Y + 2;
		x3 = left_top_corner.X + Length - 2;
		y3 = left_top_corner.Y + 2;
		move_dist = Coordinate(0, 0);
	}

	void render(Graphics* G)
	{
		if (active)
		{
			G->DrawRect(left_top_corner.X + move_dist.X - 1, left_top_corner.Y + move_dist.Y - 1, left_top_corner.X + Length + move_dist.X + 1, left_top_corner.Y + Heigth + move_dist.Y + 1, 0, 0, 0, 0.75);
			G->DrawRect(left_top_corner.X + move_dist.X, left_top_corner.Y + move_dist.Y, left_top_corner.X + Length + move_dist.X, left_top_corner.Y + Heigth + move_dist.Y, 0, 0, 0, 1);
			if (value->size() > 0)
				G->DrawTextLyricsM(*value, Coordinate(left_top_corner.X + Length / 2 + move_dist.X, left_top_corner.Y + Heigth / 2 + move_dist.Y), Coordinate(Length, Heigth), Color4f(0, 0, 0, 1));
			else
				G->DrawTextLyricsM(text, Coordinate(left_top_corner.X + Length / 2 + move_dist.X, left_top_corner.Y + Heigth / 2 + move_dist.Y), Coordinate(Length, Heigth), Color4f(0, 0, 0, 0.25));
		}
		else
		{
			G->DrawRect(left_top_corner.X + move_dist.X, left_top_corner.Y + move_dist.Y, left_top_corner.X + Length + move_dist.X, left_top_corner.Y + Heigth + move_dist.Y, 0, 0, 0, 1);
			if (value->size() > 0)
				G->DrawTextLyricsM(*value, Coordinate(left_top_corner.X + Length / 2 + move_dist.X, left_top_corner.Y + Heigth / 2 + move_dist.Y), Coordinate(Length, Heigth), Color4f(0, 0, 0, 1));
			else
				G->DrawTextLyricsM(text, Coordinate(left_top_corner.X + Length / 2 + move_dist.X, left_top_corner.Y + Heigth / 2 + move_dist.Y), Coordinate(Length, Heigth), Color4f(0, 0, 0, 0.5));
		}
	}

	void check(float x, float y)
	{
		if (area(x, y, left_top_corner.X + move_dist.X, left_top_corner.Y + move_dist.Y, left_top_corner.X + Length + move_dist.X, left_top_corner.Y + Heigth + move_dist.Y))
		{
			buf = *value;
			active = true;
		}
		else
		{
			if (active)
			{
				*value = buf;
				active = false;
			}
		}
	}

	bool set_condition(wstring data)
	{
		if (active)
		{
			buf += data;
			*value = buf;
		}
		return false;
	}

	void move(float x, float y)
	{
		move_dist.X = x;
		move_dist.Y = y;
	}

	wstring get_data()
	{
		if (active)
			return buf;
		return L"";
	}

	bool set_condition(wchar_t ch, bool is_shifted)
	{
		if (active)
		{
			/*if (is_shifted)
			{
				if (ch > 64 && ch < 91)
				{
					buf += (char)ch;
					*value = buf;
					return false;
				}
			}
			else
			{
				if (ch > 64 && ch < 91)
				{
					buf += ch + 32;
					*value = buf;
					return false;
				}
			}

			if (ch == 190)
			{
				buf += '.';
				*value = buf;
				return false;
			}

			if (ch > 47 && ch < 59)
			{
				buf += (char)ch;
				*value = buf;
				return false;
			}

			if (ch > 95 && ch < 106)
			{
				buf += ch - 48;
				*value = buf;
			}
			else
			{
				if (ch == 8)
				{

					if (buf.size() > 0)
					{
						buf.pop_back();
						if (buf.size() > 0)
						{
							*value = buf;
						}
						else
						{
							*value = L"";
						}
					}
					else
						*value = L"";
				}
				else
				{
					if (ch == 13)
					{
						*value = buf;
						active = false;
						return true;
					}
				}
			}*/
			switch (ch)
			{
			case 8:
			{
				if (buf.size() > 0)
				{
					buf.pop_back();
					if (buf.size() > 0)
					{
						*value = buf;
					}
					else
					{
						*value = L"";
					}
				}
				else
					*value = L"";
			}
			break;
			case 13:
			{
				*value = buf;
				active = false;
				return true;
			}
			break;
			default:
			{
				buf += (wchar_t)ch;
				*value = buf;
			}
			}

		}
		return false;
	}

	bool area(float x, float y, float x1, float y1, float x2, float y2)
	{
		if (x1 < x && x < x2)
			if (y2 > y && y > y1)
				return true;
		return false;
	}
};

class FS_Table_Wstring
{
	Coordinate			Center;
	int					Width;
	vector<wstring>*	Records;
	vector<bool>*		Selected_records;
	size_t				Table_Size;
	int					Count;
	size_t				Wheel;
	bool				Active;
	float				Single_Higth;
	size_t				Selected;
	int					positionable = 0;

public:
	FS_Table_Wstring(Coordinate center, int width, float single_higth, int count)
	{
		Records = nullptr;
		Selected_records = nullptr;
		Table_Size = -1;
		Active = true;
		Wheel = 0;
		Center = center;
		Count = count;
		Width = width / 2;
		Single_Higth = single_higth;
		Selected = -1;
	};

	size_t area(float x, float y)
	{
		if (Center.X - Width < x && x < Center.X + Width)
		{
			positionable = (int)(y + 10 - (Center.Y - (Count / 2) * Single_Higth));
			int item = (int)floor(positionable / Single_Higth);
			if (0 <= item && item < (Count < Table_Size ? Count : Table_Size))
			{
				Selected = item + Wheel;
				return Selected;
			}
			Selected = -1;
			return -1;
		}
		else
		{
			Selected = -1;

			return -1;
		}
	}

	bool check(float x, float y)
	{
		if (Center.X - Width < x && x < Center.X + Width)
		{
			if (Center.Y - 10 - 20 * Count / 2 < y && y < Center.Y - 10 + 20 * Count / 2)
			{
				return true;
			}
			else
				return false;
		}
		else
		{
			if (Center.X + Width + 1 < x && x < Center.X + Width + 10)
			{
				if (Center.Y - 10 - 20 * Count / 2 < y && y < Center.Y - 10 + 20 * Count / 2)
				{
					positionable = (int)(y - (Center.Y - (Count / 2) * Single_Higth));
					float curs = (float)(positionable) / (Count * 20);
					curs *= (float)Table_Size;
					Wheel = (size_t)curs;
					cout << Wheel << endl;
				}
			}

			return false;
		}
	}

	void Render(Graphics* G)
	{
		if (Active)
		{
			G->DrawRect(Center.X + Width, Center.Y - 20 * (Count / 2) - 10, Center.X + Width + 10, Center.Y + 20 * (Count / 2) - 10, 0, 0, 0, 1);

			//G->DrawTextM(to_wstring(Wheel), Coordinate(850, 650), Coordinate(100, 20), Color4f(1, 0, 0, 1));
			G->DrawTextM(to_wstring(positionable), Coordinate(850, 675), Coordinate(100, 20), Color4f(1, 0, 0, 1));

			float scale = ((float)Count / (float)Table_Size) * 20.0f;
			if (scale > 20 || scale < 0)
				scale = 20;
			G->DrawRect(Center.X - Width, Center.Y - 20 * (Count / 2) - 10, Center.X + Width - 1, Center.Y + 20 * (Count / 2) - 10, 0, 0, 0, 1);
			G->DrawRect(Center.X + Width + 1, Center.Y - 20 * (Count / 2) - 10 + (Wheel) * scale + 1, Center.X + Width + 10 - 1, Center.Y - 20 * (Count / 2) + (Wheel + Count) * scale - 11, 1, 0, 0, 1);
			if (Selected >= 0)
				G->DrawRect(Center.X - Width, Center.Y + 20 * (Selected - Wheel - Count / 2) - 10, Center.X + Width, Center.Y + 20 * (Selected - Wheel - Count / 2) + 10, 0, 0, 0, 1);
			if (Records != NULL && Table_Size > 0)
			{
				int iter = 0;
				int it = 0;
				for (auto& i : *Records)
				{
					if (iter >= Wheel && iter < Wheel + Count)
					{
						float y = Center.Y + 20.0f * it;
						if ((*Selected_records)[iter])
							G->DrawFilledRect(Center.X - (float)Width, y - 20 * (Count / 2) - 10, Center.X + (float)Width, y - 20 * (Count / 2) + 9, Color4f(0.75, 0.75, 0.75, 1));
						G->DrawTextM(i, Coordinate(Center.X, y - 20 * (Count / 2)), Coordinate((float)Width * 2, 10), Color4f(0, 0, 0, 1));
						it++;
					}
					iter++;
				}
			}
		}
	}

	void Update_Records(vector<wstring>* rc, vector<bool>* sel)
	{
		Records = rc;
		Selected_records = sel;
		if (Records != nullptr && Selected_records != nullptr)
			Table_Size = Records->size();
		Wheel = 0;
	}

	void Update_Wheel(int New)
	{
		if (New < 0 && Wheel == 0)
		{
			return;
		}
		if (Table_Size > Count && Wheel + New >= 0 && Wheel + New + Count <= Table_Size)
		{
			Wheel += New;
		}
	}
};

class FS_Table_String
{
	Coordinate			Center;
	int					Width;
	vector<string>*		Records;
	size_t				Table_Size;
	int					Count;
	size_t				Wheel;
	bool				Active;
	float				Single_Higth;
	size_t				Selected;
	int					positionable = 0;
public:
	FS_Table_String(Coordinate center, int width, float single_higth, int count)
	{
		Records = nullptr;
		Table_Size = -1;
		Active = true;
		Wheel = 0;
		Center = center;
		Count = count;
		Width = width / 2;
		Single_Higth = single_higth;
		Selected = -1;
	};

	size_t area(float x, float y)
	{
		if (Center.X - Width < x && x < Center.X + Width)
		{
			positionable = (int)(y + 10 - (Center.Y - (Count / 2) * Single_Higth));
			int item = (int)floor(positionable / Single_Higth);
			if (0 <= item && item < (Count < Table_Size ? Count : Table_Size))
			{
				Selected = item + Wheel;
				return Selected;
			}
			Selected = -1;
			return -1;
		}
		else
		{
			Selected = -1;
			return -1;
		}
	}

	bool check(float x, float y)
	{
		if (Center.X - Width < x && x < Center.X + Width)
		{
			if (Center.Y - 10 - 20 * Count / 2 < y && y < Center.Y - 10 + 20 * Count / 2)
			{
				return true;
			}
			else
				return false;
		}
		else
		{
			return false;
		}
	}

	void Render(Graphics* G)
	{
		if (Active)
		{
			G->DrawRect(Center.X + Width, Center.Y - 20 * (Count / 2) - 10, Center.X + Width + 10, Center.Y + 20 * (Count / 2) - 10, 0, 0, 0, 1);

			//G->DrawTextM(to_wstring(positionable), Coordinate(800, 650), Coordinate(100, 20), Color4f(1, 0, 0, 1));

			float scale = ((float)Count / (float)Table_Size) * 20.0f;
			if (scale > 20 || scale < 0)
				scale = 20;
			G->DrawRect(Center.X - Width, Center.Y - 20 * (Count / 2) - 10, Center.X + Width - 1, Center.Y + 20 * (Count / 2) - 10, 0, 0, 0, 1);
			G->DrawRect(Center.X + Width + 1, Center.Y - 20 * (Count / 2) - 10 + (Wheel)*scale + 1, Center.X + Width + 10 - 1, Center.Y - 20 * (Count / 2) + (Wheel + Count) * scale - 11, 0, 0, 0, 1);
			if (Selected >= 0)
				G->DrawRect(Center.X - Width, Center.Y + 20 * (Selected - Wheel - Count / 2) - 10, Center.X + Width, Center.Y + 20 * (Selected - Wheel - Count / 2) + 10, 0, 0, 0, 1);
			if (Records != NULL && Table_Size > 0)
			{
				int iter = 0;
				int it = 0;
				for (auto& i : *Records)
				{
					if (iter >= Wheel && iter < Wheel + Count)
					{
						float y = Center.Y + 20.0f * it;
						G->DrawTextM(i, Coordinate(Center.X, y - 20 * (Count / 2)), Coordinate((float)Width * 2, 10), Color4f(0, 0, 0, 1));
						it++;
					}
					iter++;
				}
			}
		}
	}

	void Update_Records(vector<string>* rc)
	{
		Records = rc;
		if (Records != NULL)
			Table_Size = Records->size();
		Wheel = 0;
	}

	void Update_Wheel(int New)
	{
		if (New < 0 && Wheel == 0)
		{
			return;
		}
		if (Table_Size > Count && Wheel + New >= 0 && Wheel + New + Count <= Table_Size)
		{
			Wheel += New;
		}
	}
};