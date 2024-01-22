#include "IDragZone.h"

IDragZone::IDragZone() {

	SetOutline(false);

}

void IDragZone::OnMouseDrag(glm::vec2 pos, glm::vec2 delta) {

	if (OnDrag) {
		OnDrag(delta);
	}

}