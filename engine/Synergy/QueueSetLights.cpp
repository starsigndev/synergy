#include "QueueSetLights.h"
#include "Light.h"
#include "Renderer.h"

QueueSetLights::QueueSetLights(std::vector<Light*>lights) {

	_Lights = lights;
}

void QueueSetLights::Render(Renderer* renderer) {

	renderer->SetLights(_Lights);

}