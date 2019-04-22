#pragma once
/*!
\file Mesh.h
*/
#include <assimp/Importer.hpp>
#include <glm/glm.hpp>
#include <string>
#include <vector>
using namespace std;

/*!
\struct Vertex
\brief holds vertices,  normals and texture coordinates.
*/
struct Vertex
{
	glm::vec3 position; //!< 3 float position
	glm::vec3 normal; //!< normals
	glm::vec2 textureCoords; //!< texture coordinates
	glm::vec3 tangent; //!< tangents
	glm::vec3 bitangent; //!< bitangents 
};

/*!
\struct Texture
\brief holds id, type and filepath.
*/
struct Texture {
	unsigned int id; //!< ID of texture
	string type; //!< texture type string
	aiString filepath; //!< filepath
};

/*!
\Class Mesh
\brief handles mesh logic.
*/
class Mesh
{
public:
	vector<Vertex> vertices; //!< vetctor of vertices.
	vector<unsigned int> indices; //!< vector of indices.
	vector<Texture> textures; //!< vector of textures.
	unsigned int VAO; //!< VAO variable.

	//! Mesh Constructor.
	/*!
	\param vertices
	\param indices
	\param textures
	*/
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);

	//! Mesh Constructor.
	/*!
	\param shaderProgram
	*/
	void render(const unsigned int shaderProgram);

private:
	
	unsigned int VBO, EBO; //!< buffer objects.

	//! Mesh Constructor.
	/*!
	\initialises all the buffer arrays.
	*/
	void setupMesh();

};