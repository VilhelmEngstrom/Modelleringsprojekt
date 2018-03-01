#include "Shader.h"

namespace graphics {
	Shader::Shader(const std::string& shaderFile) : shaderProgramID(compile(shaderFile)) {}
	Shader::~Shader() {}

	void Shader::use() const {
		glUseProgram(shaderProgramID);
	}
	void Shader::detachAll() {
		glUseProgram(0);
	}

	unsigned int Shader::compile(const std::string& shaderPath) {
		// Read source code
		ShaderSource source = loadSource(shaderPath);

		// Compile shaders
		unsigned int vertexID = compileSource(&source.vertexSource[0], ShaderType::VERTEX);
		unsigned int fragmentID = compileSource(&source.fragmentSource[0], ShaderType::FRAGMENT);

		// Return linking success (0 == failure)
		return linkProgram(vertexID, fragmentID);
	}

	unsigned int Shader::compile(const std::string& vertexPath, const std::string& fragmentPath) {
		// Read source code
		ShaderSource source = loadSource(vertexPath, fragmentPath);

		// Compile shaders
		unsigned int vertexID = compileSource(&source.vertexSource[0], ShaderType::VERTEX);
		unsigned int fragmentID = compileSource(&source.fragmentSource[0], ShaderType::FRAGMENT);

		// Return linking success
		return linkProgram(vertexID, fragmentID);
	}

	unsigned int Shader::compileSource(const char* shaderSource, const ShaderType& type) {
		GLenum glShaderType;

		// Set shader type
		type == ShaderType::VERTEX ? glShaderType = GL_VERTEX_SHADER : glShaderType = GL_FRAGMENT_SHADER;

		unsigned int shaderID = glCreateShader(glShaderType);

		int success = 0;
		int logLen;

		glShaderSource(shaderID, 1, &shaderSource, NULL);
		glCompileShader(shaderID);

		// Check for errors
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (!success) {
			// Print errors
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLen);
			char* errMsg = new char[logLen + 1];
			glGetShaderInfoLog(shaderID, logLen, NULL, &errMsg[0]);
			printf("%s\n", &errMsg[0]);
			delete[] errMsg;

			// Exit program if shader compilation failed
			exit(EXIT_FAILURE);
		}

		return shaderID;
	}


	unsigned int Shader::linkProgram(unsigned int vertexShaderID, unsigned int fragmentShaderID) {
		unsigned int programID = glCreateProgram();
		// Attach shaders
		glAttachShader(programID, vertexShaderID);
		glAttachShader(programID, fragmentShaderID);

		// Link
		glLinkProgram(programID);

		int success = 0;
		int logLen;


		// Check that linking succeeded
		glGetProgramiv(programID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLen);
			char* errMsg = new char[logLen + 1];
			glGetProgramInfoLog(programID, logLen, NULL, &errMsg[0]);
			printf("%s\n", &errMsg[0]);
			delete[] errMsg;

			// Terminate
			exit(EXIT_FAILURE);
		}

		// Detach shaders
		glDetachShader(programID, vertexShaderID);
		glDetachShader(programID, fragmentShaderID);

		// Delete shaders
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);

		return programID;
	}

	ShaderSource Shader::loadSource(const std::string& shaderPath) {
		// C string
		const char* path = &shaderPath[0];

		FILE* stream = fopen(path, "r");

		// Error
		if (stream == NULL) {
			printf("Error opening stream %s \n", path);
			exit(EXIT_FAILURE);
		}

		ShaderType type = ShaderType::NONE;


		char str[100];
		std::stringstream ss[2];


		// Read until EOF
		while (fgets(str, sizeof(str), stream) != 0) {
			// String constains "#shader"
			if (strstr(str, "#shader") != NULL) {

				if (strstr(str, "vertex") != NULL)
					type = ShaderType::VERTEX;
				else if (strstr(str, "fragment") != NULL)
					type = ShaderType::FRAGMENT;
			}
			// Store string in correct stringstream
			else
				ss[(int)type] << str;
		}

		fclose(stream);

		// Return a ShaderSource object
		return { ss[0].str(), ss[1].str() };

	}

	ShaderSource Shader::loadSource(const std::string& vertexPath, const std::string& fragmentPath) {
		// C strings
		const char* vertexShader = &vertexPath[0];
		const char* fragmentShader = &fragmentPath[0];

		// Read vertex shader source code
		ShaderType type = ShaderType::VERTEX;

		char str[100];
		std::stringstream ss[2];

		FILE* stream = fopen(vertexShader, "r");

		// Error
		if (stream == NULL) {
			printf("Error opening stream %s \n", vertexShader);
			exit(EXIT_FAILURE);
		}

		// Read lines
		while (fgets(str, sizeof(str), stream) != 0) {
			// Store string in correct stringstream
			ss[(int)type] << str;
		}

		fclose(stream);

		// Read fragment shader source code
		type = ShaderType::FRAGMENT;

		stream = fopen(fragmentShader, "r");

		// Error
		if (stream == NULL) {
			printf("Error opening stream %s \n", fragmentShader);
			exit(EXIT_FAILURE);
		}

		// Read file
		while (fgets(str, sizeof(str), stream) != 0) {
			// Store string in correct stringstream
			ss[(int)type] << str;
		}

		fclose(stream);

		// Return shader source object
		return { ss[0].str(), ss[1].str() };
	}

	void Shader::passScalar(const std::string& handle, int uniform) const {
		glUniform1i(glGetUniformLocation(shaderProgramID, &handle[0]), uniform);
	}

	void Shader::passScalar(const std::string& handle, float uniform) const {
		glUniform1f(glGetUniformLocation(shaderProgramID, &handle[0]), uniform);
	}

	void Shader::passVec3(const std::string& handle, const glm::vec3& vec) const {
		glUniform3fv(glGetUniformLocation(shaderProgramID, &handle[0]), 1, &vec[0]);
	}


	void Shader::passMat4(const std::string& handle, float* matrix) const {
		glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, &handle[0]), 1, GL_FALSE, matrix);
	}

	void Shader::passMat4(const std::string& handle, const glm::mat4& matrix) const {
		glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, &handle[0]), 1, GL_FALSE, &matrix[0][0]);
	}

}
