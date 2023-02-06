#include "stdafx.h"
#include "Animation.h"

Animation::Animation(Context* const context)
	: IResource(context, ResourceType::Animation)
{
}

Animation::~Animation()
{
}

bool Animation::SaveToFile(const std::string& path)
{
	Xml::XMLDocument doc;

	Xml::XMLDeclaration* decl = doc.NewDeclaration();
	doc.LinkEndChild(decl);
	
	Xml::XMLElement* root = doc.NewElement("Animation");
	doc.LinkEndChild(root);

	root->SetAttribute("Name", resource_name.c_str());
	root->SetAttribute("Type", static_cast<uint>(repeat_type));
	root->SetAttribute("TexturePath", sprite_texture_path.c_str());
	root->SetAttribute("TextureSizeX", sprite_texture_size.x);
	root->SetAttribute("TextureSizeY", sprite_texture_size.y);

	for (const auto& keyframe : keyframes)
	{
		Xml::XMLElement* element = doc.NewElement("Keyframe");
		root->LinkEndChild(element);

		element->SetAttribute("OffsetX", keyframe.offset.x);
		element->SetAttribute("OffsetY", keyframe.offset.y);

		element->SetAttribute("SizeX", keyframe.size.x);
		element->SetAttribute("SizeY", keyframe.size.y);

		element->SetAttribute("Time", keyframe.time);
	}


	return Xml::XMLError::XML_SUCCESS == doc.SaveFile(path.c_str());

	/*
		doc
		ㄴ decl
		ㄴ Animation -> repeat_type, sprite_size...
			ㄴ 키프레임1 -> 키프레임 데이터
			ㄴ 키프레임2 -> 키프레임 데이터
			ㄴ 키프레임3 -> 키프레임 데이터
	*/
}

bool Animation::LoadFromFile(const std::string& path)
{
	Xml::XMLDocument doc;

	Xml::XMLError error = doc.LoadFile(path.c_str());
	if (error != Xml::XMLError::XML_SUCCESS)
	{
		assert(false);
		return false;
	}

	Xml::XMLElement* root = doc.FirstChildElement();

	resource_name = root->Attribute("Name");
	repeat_type = static_cast<RepeatType>(root->UnsignedAttribute("Type"));

	sprite_texture_path = root->Attribute("TexturePath");
	SetSpriteTexture(sprite_texture_path);

	sprite_texture_size.x = root->FloatAttribute("TextureSizeX");
	sprite_texture_size.y = root->FloatAttribute("TextureSizeY");


	for (
		auto element = root->FirstChildElement();
		element != nullptr;
		element = element->NextSiblingElement()
		)
	{
		D3DXVECTOR2 offset;
		offset.x = element->FloatAttribute("OffsetX");
		offset.y = element->FloatAttribute("OffsetY");

		D3DXVECTOR2 size;
		size.x = element->FloatAttribute("SizeX");
		size.y = element->FloatAttribute("SizeY");

		float time = element->FloatAttribute("Time");

		AddKeyframe(offset, size, time);
	}

	return true;
}

void Animation::SetSpriteTexture(const std::string& path)
{
	this->sprite_texture_path = path;

	sprite_texture = std::make_shared<D3D11_Texture>(context->GetSubSystem<Graphics>());
	sprite_texture->Create(path);
}

void Animation::AddKeyframe(const Keyframe& keyframe)
{
	keyframes.emplace_back(keyframe);
}

void Animation::AddKeyframe(const D3DXVECTOR2& offset, const D3DXVECTOR2& size, const double& time)
{
	keyframes.emplace_back(offset, size, time);
}

const Keyframe* const Animation::GetKeyframeFromIndex(const uint& index)
{
	if (index >= keyframes.size())
	{
		assert(false);
		return nullptr;
	}

	return &keyframes[index];
}
