#include "IImage.h"
#include "SynUI.h"

IImage::IImage(Texture2D* image) {

	_Image = image;
	_Outline = false;
	_ScissorTest = false;
}

void IImage::Render() {

	SynUI::Draw(_Image, GetRenderPosition(), GetSize(), GetColor());

}