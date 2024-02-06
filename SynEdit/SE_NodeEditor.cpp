#include "SE_NodeEditor.h"
#include "Node3D.h"
#include "IWindowContent.h"
#include "IVec3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"
//#include <glm/gtc/matrix_transform.hpp>
#include "glm/gtc/quaternion.hpp"
#include "ITextBox.h"
#include "SE_GraphExplorer.h"
#include "ILabel.h"
#include "ISelector.h"
#include "Entity.h"
#include "IButton.h"
#include "IFileRequestor.h"
#include "GameProject.h"
#include "SynUI.h"
#include "SE_Global.h"
#include "ScriptHost.h"
#include "INumeric.h"
SE_NodeEditor* SE_NodeEditor::This = nullptr;



SE_NodeEditor::SE_NodeEditor() {

	This = this;
	SetText("Node Editor");
	_ScissorTest = true;

}

void SE_NodeEditor::SetNode(Node3D* node) {

	_EditNode = node;
	if (node) {
		_NodeHost = SE_Global::_SelectedNode->GetHost();
	}
	RebuildUI();


}

glm::quat mat4ToQuat(const glm::mat4& rotationMatrix) {
	return glm::quat_cast(rotationMatrix);
}

glm::vec3 extractEulerAngles(const glm::mat4& rotationMatrix) {
	// Extract Euler angles from the rotation matrix

	glm::vec3 eulerAngles = glm::eulerAngles(mat4ToQuat(rotationMatrix));
	glm::vec3 eulerAnglesDegrees = glm::degrees(eulerAngles);
	// Convert radians to degrees if necessary
	// eulerAngles = glm::degrees(eulerAngles);

	return eulerAnglesDegrees;
}
glm::mat4 eulerToMat4Degrees(const glm::vec3& eulerAnglesDegrees) {
	glm::vec3 eulerAnglesRadians = glm::radians(eulerAnglesDegrees);
	glm::mat4 rotationMatrix = glm::mat4(glm::eulerAngleXYZ(eulerAnglesRadians.x, eulerAnglesRadians.y, eulerAnglesRadians.z));
	return rotationMatrix;
}

void SE_NodeEditor::RebuildUI() {

	_Content->ClearControls();

	if (_EditNode == nullptr) {
		return;
	}

	_NodePosition = new IVec3("Position");
	_NodeRotation = new  IVec3("Rotation");
	_NodeScale = new IVec3("Scale");
	_NodeName = new ITextBox;

	_Content->AddControl(_NodePosition);
	_Content->AddControl(_NodeRotation);
	_Content->AddControl(_NodeScale);
	_Content->AddControl(_NodeName);


	_NodePosition->SetIncrement(1.0f);
	_NodeRotation->SetIncrement(5.0f);
	_NodeScale->SetIncrement(0.1f);

	_NodeName->SetPosition(glm::vec2(100, 50));
	_NodeName->SetSize(glm::vec2(220, 30));
	
	auto name_l = new ILabel("Name");
	name_l->SetPosition(glm::vec2(25, 50));

	_Content->AddControl(name_l);

	_NodePosition->SetPosition(glm::vec2(75, 90));
	_NodeRotation->SetPosition(glm::vec2(75, 130));
	_NodeScale->SetPosition(glm::vec2(75, 170));
	_NodeName->SetText(_EditNode->GetName());

	_NodePosition->SetValue(_EditNode->GetPosition());
	_NodeRotation->SetValue(extractEulerAngles(_EditNode->GetRotation()));
	_NodeScale->SetValue(_EditNode->GetScale());

	_NodeName->OnChanged = [&](std::string val) {

		_EditNode->SetName(val);
		SE_GraphExplorer::This->RebuildUI();

		};

	_NodePosition->ValueChanged = [&](glm::vec3 val) {

		if (_EditNode) {
			_EditNode->SetPosition(val);
		}
		};

	_NodeRotation->ValueChanged = [&](glm::vec3 val) {

		if (_EditNode) {
			_EditNode->SetRotation(eulerToMat4Degrees(val));
		}

		};
	
	_NodeScale->ValueChanged = [&](glm::vec3 val) {

		if (_EditNode) {

			_EditNode->SetScale(val);

		}

		};

	_NodePhysics = new ISelector;
	_NodePhysics->SetPosition(glm::vec2(100, 215));
	_NodePhysics->SetSize(glm::vec2(150, 30));
	_Content->AddControl(_NodePhysics);
	_NodePhysics->AddItems({ "None","Box","Sphere","Capsule","Convex","Mesh" });
	auto phy_l = new ILabel("Physics");
	phy_l->SetPosition(glm::vec2(25, 225));
	AddControl(phy_l);

	_AddScript = new IButton;
	_AddScript->Set(glm::vec2(25, 260), glm::vec2(80, 30), "Add Script");
	_Content->AddControl(_AddScript);

	_AddScript->OnClick = [&](auto c, auto d)
		{

			IFileRequestor* freq = new IFileRequestor(GameProject::_ProjectPath);
			freq->SetText("Select script file");
			SynUI::This->SetTop(freq);

			freq->FileSelected = [&](auto file) {

				SE_Global::_SelectedNode->AddScript(file);
				
				RebuildUI();
				

				};

		};


	_NodePhysics->ItemSelected = [&](ListItem* type) {

		PhysicsType p_type = PhysicsType::PT_None;
		if (type->Text == "None")
		{
			p_type = PhysicsType::PT_None;
		}
		if (type->Text == "Box")
		{
			p_type = PhysicsType::PT_Box;
		}
		if (type->Text == "Convex")
		{
			p_type = PhysicsType::PT_Convex;
		}
		if (type->Text == "Sphere")
		{
			p_type = PhysicsType::PT_Sphere;
		}
		if (type->Text == "Mesh")
		{
			p_type = PhysicsType::PT_Mesh;
		}

		auto entity = dynamic_cast<Entity*>(_EditNode);

		if (entity) {
			entity->SetPhysics(p_type);
		}

		};

	auto params = _NodeHost->GetParams();

	int cy = 310;


	for (auto const& p : params) {

		auto lab = new ILabel(p.Name + ":" + p.ClassName);
		lab->SetPosition(glm::vec2(10, cy));
		_Content->AddControl(lab);


		if (p.Type == PT_Number) {

			auto num = new INumeric;
			num->Set(glm::vec2(100, cy), glm::vec2(80, 30), "");
			_Content->AddControl(num);

			num->SetNumber(_NodeHost->GetNumberFromTable("params", p.Name));

			auto np = new Param;
			np->Name = p.Name;
			np->Type = p.Type;
			np->ClassName = p.ClassName;
			num->_OtherData = np;

			num->ValueChanged = [&](auto n, float value) {

				auto nu = (Param*)n->_OtherData;
				_NodeHost->SetNumberInTable("params", nu->Name, value);

				};

			//auto nlab = new ILabel("Value:"+std::to_string(_NodeHost->GetNumberFromTable("params", p.Name)));
			//nlab->SetPosition(glm::vec2(10, cy));
			//cy += 30;
			//_Content->AddControl(nlab);

		}

		cy = cy + 30;
	}
	




}