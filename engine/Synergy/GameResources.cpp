#include "GameResources.h"

GameResources* GameResources::Resources = nullptr;


GameResources::GameResources(std::string path) {

	Resources = this;

}

SynResources* GameResources::GetResources() {

	return _Resources;

}

void GameResources::SetResources(SynResources* resources) {

	_Resources = resources;

}