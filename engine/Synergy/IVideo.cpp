#include "IVideo.h"
#include "VideoDecoder.h"
#include "Texture2D.h"
#include "SynUI.h"

IVideo::IVideo() {

	//_Decoder = new VideoDecoder;

}

void IVideo::PlayVideo(std::string path) {

	_Decoder = new VideoDecoder;
	_Decoder->OpenVideo(path.c_str());
	_Playing = true;
	
}

void IVideo::Update(float dt) {

	if (_Playing) {
		_Decoder->UpdateDecoder();
		if (_Decoder->IsVideoDone()) {
			_Decoder->Restart();
		}
	}

}

void IVideo::Render() {

	if (_Playing) {
		
		auto tex = _Decoder->GetImage();


		if (tex != nullptr) {
			SynUI::Draw(tex, GetRenderPosition(), GetSize(), glm::vec4(1, 1, 1, 1));
		}
	}

}

void IVideo::Stop() {

	_Playing = false;


}