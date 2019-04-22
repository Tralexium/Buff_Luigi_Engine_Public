#pragma once
/*!
\file Model.h
*/
#include <string>
#include <vector>
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>

/*!
\class Model
\brief Handles model loading, meshes and textures.
*/
class Model
{
public:

	//! Model Constructor.
	/*!
	\param filepath.
	*/
	Model(string filepath);

	//! Render Function.
	/*!
	\param shaderProgram.
	*/
	void render(const unsigned int shaderProgram);

	//! Texture from file function.
	/*!
	\param filepath ptr.
	\param directory reference.
	\param gamma.
	*/
	static unsigned int TextureFromFile(const char* filepath, const string& directory, bool gamma = false);

private:

	std::vector<Mesh> v_meshes; //!< vector of meshes.
	string directory; //!< string variable for directory.
	vector<Texture> v_textures;  //<! Vector of textures.

	//! Load model function.
	/*!
	\param path.
	*/
	void loadModel(string path);

	//! Process node function.
	/*!
	\param node ptr.
	\param scene ptr.
	*/
	void processNode(aiNode* node, const aiScene* scene);

	//! Process mesh function.
	/*!
	\param mesh ptr.
	\param scene ptr.
	*/
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	//! loadMaterialTextures vector function.
	/*!
	\param pat ptr.
	\param type.
	\param typeName.
	\returns texture.
	*/
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
		std::string typeName);
};
