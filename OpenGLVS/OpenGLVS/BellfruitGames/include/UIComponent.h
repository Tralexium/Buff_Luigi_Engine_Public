#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <stdio.h>

#include "Component.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>




using namespace std;

class UIComponent : public Component
{
public:
	int scoreCounter = 0;
	bool windowOpen;
	bool show_demo_window;
	bool show_another_window;
	ImVec4 clear_color;
	ImVec2 imGuiWindowSize;

	void initGUI(GLFWwindow* window) {


		// GUI WANG ---------------------------------------------------------------------------------------
		const char* glsl_version = "#version 130";
		// Setup Dear ImGui context
		ImGui::CreateContext();
		IMGUI_CHECKVERSION();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls
		// Setup Dear ImGui style
		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);
		ImGui::StyleColorsDark();
		show_demo_window = false;
		show_another_window = true;
		windowOpen = true;
		clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
		//imGuiWindowSize = ImVec2(g_window.getScreenWidth(), g_window.getScreenHeight());
	}

	void createGUI() {

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		//if (show_demo_window)
			//ImGui::ShowDemoWindow(&show_demo_window);

		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Game Menu");                          // Create a window called "Hello, world!" and append into it.

														
			if (ImGui::Button("Exit Game")) // Buttons return true when clicked (most widgets return true when edited/activated)
			{
				windowOpen = false;
			}

		/*	ImGui::SameLine();
			ImGui::Text("counter = %d", counter);*/

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}

		// 3. Show another simple window.
		if (show_another_window)
		{

			ImGui::Begin("Score:", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			ImGui::SameLine();
			ImGui::Text("Goals: %d", scoreCounter);
			
			
			ImGui::End();
		}
	}

	void renderGUI() {

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}


	UIComponent()
	{

		//// initialize lights

		////load from files
		//vertexFileName = "res/shaders/" + shadername + ".vert";
		//fragmentFileName = "res/shaders/" + shadername + ".frag";

		//// Load contents of vertex file
		//std::ifstream inFile(vertexFileName);
		//if (!inFile) {
		//	string errorMsg = "Error opening shader file: " + vertexFileName + "\n";
		//	fprintf(stderr, errorMsg.c_str());
		//	exit(1);
		//}

		//std::stringstream code;
		//code << inFile.rdbuf();
		//inFile.close();
		//std::string codeStr(code.str());
		//const GLchar* vertex_shader[] = { codeStr.c_str() };

		//// Load contents of fragment file
		//std::ifstream inFile2(fragmentFileName);
		//if (!inFile2) {
		//	string errorMsg = "Error opening shader file: " + fragmentFileName + "\n";
		//	fprintf(stderr, errorMsg.c_str());
		//	exit(1);
		//}

		//std::stringstream code2;
		//code2 << inFile2.rdbuf();
		//inFile2.close();
		//std::string codeStr2(code2.str());
		//const GLchar* fragment_shader[] = { codeStr2.c_str() };

		//// vertex shader
		//int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		//glShaderSource(vertexShader, 1, vertex_shader, NULL);
		//glCompileShader(vertexShader);
		//// check for shader compile errors
		//int success;
		//char infoLog[512];
		//glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		//if (!success)
		//{
		//	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		//	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		//}
		//// fragment shader
		//int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		//glShaderSource(fragmentShader, 1, fragment_shader, NULL);
		//glCompileShader(fragmentShader);
		//// check for shader compile errors
		//glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		//if (!success)
		//{
		//	glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		//	std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		//}
		//// link shaders
		//m_fontShaderProgram = glCreateProgram();
		//glAttachShader(m_fontShaderProgram, vertexShader);
		//glAttachShader(m_fontShaderProgram, fragmentShader);
		//glLinkProgram(m_fontShaderProgram);
		//// check for linking errors
		//glGetProgramiv(m_fontShaderProgram, GL_LINK_STATUS, &success);
		//if (!success) {
		//	glGetProgramInfoLog(m_fontShaderProgram, 512, NULL, infoLog);
		//	std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		//}


		//




		//glDeleteShader(vertexShader); // clean up
		//glDeleteShader(fragmentShader); // clean up

	}

	//void setupFont() {
	//
	//	// based on tutorial from https://learnopengl.com/#!In-Practice/Text-Rendering
	//// FreeType
	//	FT_Library ft;
	//	// All functions return a value different than 0 whenever an error occurred
	//	if (FT_Init_FreeType(&ft))
	//		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

	//	// Load font as face
	//	FT_Face face;
	//	if (FT_New_Face(ft, "res/fonts/arial.ttf", 0, &face))
	//	{
	//		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
	//		return;
	//	}
	//	// Set size to load glyphs as
	//	FT_Set_Pixel_Sizes(face, 0, 48);

	//	// Disable byte-alignment restriction
	//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	//	// Load first 128 characters of ASCII set
	//	for (GLubyte c = 0; c < 128; c++)
	//	{
	//		// Load character glyph 
	//		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
	//		{
	//			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
	//			continue;
	//		}
	//		// Generate texture
	//		GLuint texture;
	//		glGenTextures(1, &texture);
	//		glBindTexture(GL_TEXTURE_2D, texture);
	//		glTexImage2D(
	//			GL_TEXTURE_2D,
	//			0,
	//			GL_RED,
	//			face->glyph->bitmap.width,
	//			face->glyph->bitmap.rows,
	//			0,
	//			GL_RED,
	//			GL_UNSIGNED_BYTE,
	//			face->glyph->bitmap.buffer
	//		);
	//		// Set texture options
	//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//		// Now store character for later use
	//		Character character = {
	//			texture,
	//			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
	//			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
	//			face->glyph->advance.x
	//		};
	//		Characters.insert(std::pair<GLchar, Character>(c, character));
	//	}
	//	glBindTexture(GL_TEXTURE_2D, 0);
	//	// Destroy FreeType once we're finished
	//	FT_Done_Face(face);
	//	FT_Done_FreeType(ft);


	//	// Configure VAO/VBO for texture quads
	//	glGenVertexArrays(1, &font_VAO);
	//	glGenBuffers(1, &font_VBO);
	//	glBindVertexArray(font_VAO);
	//	glBindBuffer(GL_ARRAY_BUFFER, font_VBO);
	//	// dynamic draw as the text may change frequently
	//	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	//	glEnableVertexAttribArray(0);
	//	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	//	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//	glBindVertexArray(0);
	//}

	//void setTextTexture() {
	//	glUniform1i(glGetUniformLocation(m_fontShaderProgram, "text"), 0);
	//}

	//void use() // loading some default shaders to get things up and running
	//{
	//	glUseProgram(m_fontShaderProgram);// set the default shader
	//}

	//void renderText( std::string text, float x, float y, float scale, glm::vec3 colour) {

	//	

	//	glEnable(GL_BLEND);
	//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//	// set the window to orthographic
	//	glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);

	//	float pixelValueX = x * 800.0f;
	//	float pixelValueY = y * 600.0f;

	//	glUseProgram(m_fontShaderProgram);
	//	glUniformMatrix4fv(glGetUniformLocation(m_fontShaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	//
	//	glUniform3f(glGetUniformLocation(m_fontShaderProgram, "textColour"), colour.x, colour.y, colour.z);
	//	//glUniform1i(glGetUniformLocation(m_fontShaderProgram, "text"), 0);
	//	glActiveTexture(GL_TEXTURE0);
	//	glBindVertexArray(font_VAO);

	//	// Iterate through all characters
	//	std::string::const_iterator c;
	//	for (c = text.begin(); c != text.end(); c++)
	//	{
	//		Character ch = Characters[*c];

	//		GLfloat xpos = pixelValueX + ch.bearing.x * scale;
	//		GLfloat ypos = pixelValueY - (ch.size.y - ch.bearing.y) * scale;

	//		GLfloat w = ch.size.x * scale;
	//		GLfloat h = ch.size.y * scale;
	//		// Update VBO for each character
	//		GLfloat vertices[6][4] = {
	//			{ xpos,     ypos + h,   0.0, 0.0 },
	//			{ xpos,     ypos,       0.0, 1.0 },
	//			{ xpos + w, ypos,       1.0, 1.0 },

	//			{ xpos,     ypos + h,   0.0, 0.0 },
	//			{ xpos + w, ypos,       1.0, 1.0 },
	//			{ xpos + w, ypos + h,   1.0, 0.0 }
	//		};
	//		// Render glyph texture over quad
	//		glBindTexture(GL_TEXTURE_2D, ch.textureID);
	//		// Update content of VBO memory
	//		glBindBuffer(GL_ARRAY_BUFFER, font_VBO);
	//		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	//		glBindBuffer(GL_ARRAY_BUFFER, 0);
	//		// Render quad
	//		glDrawArrays(GL_TRIANGLES, 0, 6);
	//		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
	//		pixelValueX += (ch.advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
	//	}
	//	glBindVertexArray(0);
	//	glBindTexture(GL_TEXTURE_2D, 0);

	//	// go back to default shader
	//	//glUseProgram(shaderProgram);

	//}

	//
	//void setUniforms(CameraComponent* cam) { 
	//
	//	

	//		// set the view and projection components of our shader to the CameraComponent values
	//		glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
	//		glUniformMatrix4fv(glGetUniformLocation(m_fontShaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	//	

	//	


	//}

	void OnUpdate(float dt) {}
	void OnMessage(const std::string m) {}



	~UIComponent()
	{

	}

private:

};