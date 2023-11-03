//
// Created by cx9ps3 on 03.01.23.
//

#include "../profiling/Profiling.hpp"
#include "../render_context/RenderContext.hpp"
#include "ShaderAsset.hpp"
#include <fstream>

std::string hexen::engine::graphics::ShaderAsset::parseShaderType()
{
	HEXEN_ADD_TO_PROFILE();
	std::string typeToken = "#type";
	auto tokenPosition = shaderText.find(typeToken);
	HEXEN_ASSERT(tokenPosition != std::string::npos, "ERROR: Token #type in shader file " + path + " not found! Please specify shader type!");
	std::string buffer;

	for (auto i = tokenPosition; i < shaderText.size(); i++)
	{
		buffer += shaderText[i];
		if (shaderText[i] == '\n')
		{
			break;
		}
	}

	tokenPosition = shaderText.find(buffer);
	shaderText.erase(tokenPosition, buffer.size());

	std::string token = buffer.substr(typeToken.size(), buffer.size());

	token.erase(std::remove(token.begin(), token.end(), ' '), token.end());
	token.erase(std::remove(token.begin(), token.end(), '\r'), token.end());
	token.erase(std::remove(token.begin(), token.end(), '\n'), token.end());

	return token;
}
void hexen::engine::graphics::ShaderAsset::setShaderType(const std::string &shaderType)
{
	HEXEN_ADD_TO_PROFILE();
	if (shaderType == "vertex")
	{
		type = ShaderType::VERTEX;
	}
	else if (shaderType == "fragment" || shaderType == "pixel")
	{
		type = ShaderType::FRAGMENT;
	}
	else if (shaderType == "geometry")
	{
		type = ShaderType::GEOMETRY;
	}
	else
	{
		type = ShaderType::UNKNOWN;
		HEXEN_ASSERT(false, "ERROR: " + shaderType + " is unknown shader type!Please specify shader type!");
	}
}

hexen::engine::graphics::ShaderType hexen::engine::graphics::ShaderAsset::getType() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	return type;
}

void hexen::engine::graphics::ShaderAsset::save(const std::filesystem::path &pathToAsset, const std::filesystem::path &pathToRawShader)
{
	HEXEN_ADD_TO_PROFILE();
	std::ofstream outFile(pathToAsset, std::ios::binary);
	std::ifstream rawShaderFile(pathToRawShader);

	std::stringstream ss;
	ss << rawShaderFile.rdbuf();
	shaderText = ss.str();

	auto stringShaderType = parseShaderType();
	setShaderType(stringShaderType);

	assetDataFile["shader_asset"]["name"] = pathToAsset.filename();
	assetDataFile["shader_asset"]["raw_data"] = shaderText;
	assetDataFile["shader_asset"]["shader_type"] = stringShaderType;

	auto binaryJsonData = nlohmann::json::to_bson(assetDataFile);

	outFile.write((char*)binaryJsonData.data(), binaryJsonData.size()  * sizeof(core::u8));
}

void hexen::engine::graphics::ShaderAsset::load(const std::filesystem::path &pathToAsset)
{
	std::ifstream inFile(pathToAsset);
	std::stringstream ss;
	ss << inFile.rdbuf();

	assetDataFile = nlohmann::json::from_bson(ss);
	setShaderType(assetDataFile["shader_asset"]["shader_type"]);
}

std::string hexen::engine::graphics::ShaderAsset::getName() const
{
	return assetDataFile["shader_asset"]["name"];
}

std::vector<hexen::engine::core::u8> hexen::engine::graphics::ShaderAsset::getRawData() const
{
	std::vector<core::u8> shaderData;
	auto shaderString = assetDataFile["shader_asset"]["raw_data"];
	shaderData.assign(shaderString.begin(), shaderString.end());

	return shaderData;
}
