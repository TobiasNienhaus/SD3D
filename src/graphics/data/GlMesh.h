//
// Created by Tobias on 10/13/2020.
//

#ifndef SD3D_GLMESH_H
#define SD3D_GLMESH_H

#include <GLFW/glfw3.h>
#include "DataLayout.h"
#include "Model.h"

// TODO maybe template on useEbo?
class GlMesh {
private:
	// Vertex Array Object
	// - This object holds info about data layout, the VBO the data is coming from
	//   and the linked EBO (if applicable)
	GLuint m_vao;
	GLuint m_drawCount;

	// TODO save references to textures here, because they are per model (i think)

	// The VBO is implicitly saved in the VAO

	// Notify if an EBO was created and bound to the VAO
	// If yes, glDrawElements has to be used.
	bool m_usesEbo;

	GlMesh(GLuint vao, GLuint drawCount, bool useEbo);

public:
	void draw() const;

	// for now only float
	static GlMesh from_data(const DataLayout &dataLayout, const float *data, GLuint amount);

	// TODO maybe make one without indices
	static GlMesh from_data(const std::vector<Model::Vertex> &data, const std::vector<GLuint> &indices);

};


#endif //SD3D_GLMESH_H