#pragma once
#include "IControl.h"
#include <string>
class VideoDecoder;

class IVideo : public IControl
{
public:

	IVideo();
	void PlayVideo(std::string path);
	void Render();
	void Update(float dt);
	void Stop();

private:

	std::string _VideoPath;
	VideoDecoder* _Decoder;
	bool _Playing = false;

};

