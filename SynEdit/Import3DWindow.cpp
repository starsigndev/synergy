#include "Import3DWindow.h"
#include "ITextBox.h"
#include "INumeric.h"
#include "ILabel.h"
#include "PathHelper.h"
#include "IVec3.h"
#include "IButton.h"
#include "GameResources.h"
#include "Resource.h"
#include "ResourceGroup.h"
#include "SynResources.h"

Import3DWindow::Import3DWindow(std::string path,ResourceGroup* group) {

	_Path = path;
	SetPosition(glm::vec2(200, 200));
	SetSize(glm::vec2(550, 210));
	SetText("Import 3D Entity");
	_Group = group;
	_EntityName = new ITextBox;
	AddControl(_EntityName);
	_EntityName->SetPosition(glm::vec2(90, 40));
	_EntityName->SetSize(glm::vec2(240, 30));

	_EntityName->SetText(PathHelper::ExtractFileName(path));

	auto lab = new ILabel("Name");
	lab->SetPosition(glm::vec2(10, 45));

	AddControl(lab);

	_EntityScale = new IVec3("Scale");
	_EntityScale->SetPosition(glm::vec2(65, 90));
	AddControl(_EntityScale);
	_EntityScale->SetValue(glm::vec3(1, 1, 1));
	_EntityScale->SetIncrement(0.05f);

	auto imp = new IButton;
	imp->Set(glm::vec2(10, 160), glm::vec2(80, 30), "Import");

	AddControl(imp);

	imp->OnClick = [&](IControl* c, void* data) {

		Resource* new_res = new Resource(PathHelper::ExtractFileName(_Path), GameResources::Resources->GetResources());
		new_res->SetType(ResourceType::RT_Entity);
		new_res->SetEntity(_EntityName->GetText(),_EntityScale->GetValue());
		new_res->SetData(_Path);

		_Group->AddResource(new_res);

		GameResources::Resources->GetResources()->SaveIndex();

		};

}

