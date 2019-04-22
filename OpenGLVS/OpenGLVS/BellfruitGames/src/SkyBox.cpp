#include "SkyBox.h"
#include "Bitmap.h"

using glm::mat4;
using glm::vec4;


SkyBox::SkyBox(int fvert, unsigned int shader)
{
	float v[] = { //! array of vertices

		-fvert, -fvert, -fvert, // V0
		-fvert,  fvert, -fvert, // V1
		 fvert,  fvert, -fvert, // V2
		 fvert, -fvert, -fvert, // V3

		-fvert, -fvert, fvert,  // V4
		-fvert,  fvert, fvert,  // V5
		 fvert,  fvert, fvert,  // V6
		 fvert, -fvert, fvert,  // V7
	};

	unsigned int idx[] = { //! array of faces
		0,1,2,
		0,2,3,
		7,6,5,
		7,5,4,
		1,5,6,
		1,6,2,
		4,0,3,
		4,3,7,
		3,2,6,
		3,6,7,
		4,5,1,
		4,1,0,
	};

	GLuint handle[2]; //! GLuint handle value
	glGenBuffers(2, handle);

	glGenVertexArrays(1, &vaoHandle);
	glBindVertexArray(vaoHandle); //! Bind vertex array object

	glBindBuffer(GL_ARRAY_BUFFER, handle[0]); //! Bind buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);

	//vertices
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, FALSE, 0, ((GLubyte *)NULL + (0))); //! setup vertex attribute pointer
	glEnableVertexAttribArray(0); //! enable vertex attribute pointer

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle[1]); //! Bind Buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx), idx, GL_STATIC_DRAW); //! set bufferdata.

	glBindVertexArray(0); //! Bind VAO

	glGenTextures(1, &textureID); //! Return texture id
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID); //! Bind textureID

	GLuint CubeMapFaces[6] = { //! Array of faces	
		GL_TEXTURE_CUBE_MAP_POSITIVE_X, //! Right
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X, //! Left
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y, //! Up
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, //! Down
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z, //! Front
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, //! Back
	};

	for (GLint i = 0; i < faces; i++) //! Loop through size of faces array 
	{
		std::string TextureDir = "res/images/space/cubemap" + std::to_string(i) + ".png"; //! takes image from filepath, then set neccesary values for 2d texture image
		
		Bitmap bmp = Bitmap::bitmapFromFile(TextureDir);
			glTexImage2D(CubeMapFaces[i],0,GL_RGB,bmp.width(),bmp.height(),0,GL_RGB,GL_UNSIGNED_BYTE,bmp.pixelBuffer());
	}

	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //! Returns the weighted average of the four texture elements that are closest to the specified texture coordinates. 
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); //! Sets the wrap parameter for texture coordinate to CLAMP_TO_EDGE
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	GLuint loc = glGetUniformLocation(shader, "cubemap"); //! Gets the uniform location
	glUniform1i(loc, textureID);

	glActiveTexture(GL_TEXTURE0); //! Sets active texture
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID); //! binds it


	



}



void SkyBox::render() const
{
	glBindVertexArray(vaoHandle); //! Bind VAO
	glDrawElements(GL_TRIANGLES, 6 * faces, GL_UNSIGNED_INT, ((GLubyte *)NULL + (0))); //! Draws faces
}


