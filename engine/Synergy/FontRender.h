#pragma once
#define STB_TRUETYPE_IMPLEMENTATION
#include <string>
#include <unordered_map>
#include <string>
#include "glm/glm.hpp"

class SmartDraw;
class Texture2D;
class SMFont2D;

class FontRender
{
public:
	FontRender(std::string path);
	void DrawText(std::string text,int x,int y);
	void DrawTextUI(std::string text, int x, int y,glm::vec4 col);
	int Width(std::string text);
	int Height() {
		return fontSize;
	}
private:
	unsigned char* fontData;
	float fontSize = 18.0f;  // Adjust this as needed
	int bitmapWidth = 400;  // Width of your image
	int bitmapHeight = 200; // Height of your image
	unsigned char* bitmap;
	SmartDraw* mDraw;
	std::unordered_map<std::string, Texture2D*> cache;
	//SMFont2D* mShader;
};

