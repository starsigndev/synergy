#include "SynResources.h"
#include "VFile.h"
#include "ResourceGroup.h"
#include "Resource.h"
#include "GameResources.h"

void SynResources::SaveDefault(SynResources* resources) {

	VFile* file = new VFile("default.res", FileMode::Write);

	file->WriteString(resources->GetPath().c_str());

	file->Close();

}

void SynResources::LoadDefault() {

	if (VFile::Exists("default.res"))
	{

		VFile* file = new VFile("default.res", FileMode::Read);

		std::string path = file->ReadString();
		std::string cpath = path + ".idx";

		if (VFile::Exists(cpath.c_str())) {

			file->Close();

			GameResources::Resources->SetResources(new SynResources(path));
		}
	}

}

SynResources::SynResources(std::string path) {

	_Path = path;
	_IndexPath = path + ".idx";
	_ContentPath = path + ".content";

	if (VFile::Exists(_IndexPath.c_str())) {

		LoadIndex();

	}
	else {

		SaveIndex();

	}

}

void SynResources::LoadIndex() {

	VFile* file = new VFile(_IndexPath.c_str(), FileMode::Read);

	int groups = file->ReadInt();

	for (int i = 0; i < groups; i++) {

		std::string name = file->ReadString();

		ResourceGroup* group = new ResourceGroup(name);

		_Groups.push_back(group);

		int rc = file->ReadInt();

		for (int j = 0; j < rc; j++) {

			std::string name = file->ReadString();
			Resource* res = new Resource(name,this);
			res->SetData(file->ReadString());
			res->SetStart(file->ReadLong());
			res->SetSize(file->ReadLong());
			res->SetCompressed(file->ReadBool());

			ResourceType type = (ResourceType)file->ReadInt();
			switch (type) {
			case RT_Entity:

				auto x = file->ReadFloat();
				auto y = file->ReadFloat();
				auto z = file->ReadFloat();
				auto name = file->ReadString();

				res->SetEntity(name, glm::vec3(x, y, z));

				break;
			}


			group->AddResource(res);

		}

	}

	file->Close();

}

void SynResources::SaveIndex() {

	VFile* file = new VFile(_IndexPath.c_str(), FileMode::Write);

	file->WriteInt(_Groups.size());

	for (auto const& group : _Groups) {

	
		file->WriteString(group->GetName().c_str());

		auto res = group->GetResources();

		file->WriteInt(res.size());

		for (auto const& r : res) {

			file->WriteString(r->GetName().c_str());
			file->WriteString(r->GetPath().c_str());
			file->WriteLong(r->GetStart());
			file->WriteLong(r->GetSize());
			file->WriteBool(r->IsCompressed());

			file->WriteInt((int)r->GetType());
			switch (r->GetType()) {
			case RT_Entity:

				file->WriteFloat(r->GetScale().x);
				file->WriteFloat(r->GetScale().y);
				file->WriteFloat(r->GetScale().z);
				file->WriteString(r->GetEntityName().c_str());

				break;
			}


		}

		//group->Save(file);


	}

	file->Close();

}

void SynResources::AddGroup(ResourceGroup* group)
{

	_Groups.push_back(group);
	SaveIndex();

}

void SynResources::SaveContent() {

	VFile* file = new VFile(_ContentPath.c_str(), FileMode::Write);

	long cur_byte = 0;
	long cur_size = 0;

	for (auto const& group : _Groups)
	{

		for (auto const& res : group->GetResources()) {

			std::string path = res->GetPath();

			long len = VFile::Length(path.c_str());

			VFile* res_f = new VFile(path.c_str(), FileMode::Read);

			file->WriteBytes(res_f->ReadBytes(len),len);

			res_f->Close();

			res->SetStart(cur_byte);
			res->SetSize(len);
			res->SetCompressed(false);
		

			int b = 5;
			cur_byte += len;
			cur_size += len;

			

			
		}

	}

	file->Close();

}

bool ContainsString(const std::string& toSearch, const std::string& searchTerm) {
	return toSearch.find(searchTerm) != std::string::npos;
}

Resource* SynResources::FindResource(std::string term)
{

	for (auto const& g : _Groups)
	{

		for (auto const& r : g->GetResources()) {

			if (ContainsString(r->GetPath(), term)) {

				return r; 

			}

		}

	}

	return nullptr;

}