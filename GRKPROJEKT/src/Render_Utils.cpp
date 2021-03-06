#include "Render_Utils.h"

#include <algorithm>

#include <glew.h>
#include <freeglut.h>

void Core::DrawVertexArray(const float * vertexArray, int numVertices, int elementSize )
{
	glVertexAttribPointer(0, elementSize, GL_FLOAT, false, 0, vertexArray);
	glEnableVertexAttribArray(0);

	glDrawArrays(GL_TRIANGLES, 0, numVertices);
}

void Core::DrawVertexArrayIndexed( const float * vertexArray, const int * indexArray, int numIndexes, int elementSize )
{
	glVertexAttribPointer(0, elementSize, GL_FLOAT, false, 0, vertexArray);
	glEnableVertexAttribArray(0);

	glDrawElements(GL_TRIANGLES, numIndexes, GL_UNSIGNED_INT, indexArray);
}


void Core::DrawVertexArray( const VertexData & data )
{
	int numAttribs = std::min(8, data.NumActiveAttribs);
	for(int i = 0; i < numAttribs; i++)
	{
		glVertexAttribPointer(i, data.Attribs[i].Size, GL_FLOAT, false, 0, data.Attribs[i].Pointer);
		glEnableVertexAttribArray(i);
	}
	glDrawArrays(GL_TRIANGLES, 0, data.NumVertices);
}

void Core::DrawModel( obj::Model * model )
{
	if (model->vertex.size() != (size_t)0)
		glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, &model->vertex[0]);
	if (model->texCoord.size() != (size_t)0)
		glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, &model->texCoord[0]);
	if (model->normal.size() != (size_t)0)
		glVertexAttribPointer(2, 3, GL_FLOAT, false, 0, &model->normal[0]);

	//if (model->vertex.size() != (size_t)0)
		glEnableVertexAttribArray(0);
	//if (model->texCoord.size() != (size_t)0)
		glEnableVertexAttribArray(1);
	//if (model->normal.size() != (size_t)0)
		glEnableVertexAttribArray(2);


	unsigned short * tmp = &model->faces["default"][0];
	glDrawElements(GL_TRIANGLES, model->faces["default"].size(), GL_UNSIGNED_SHORT, tmp);
}
