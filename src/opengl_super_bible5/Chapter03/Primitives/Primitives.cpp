// Primitieves.cpp
// OpenGL SuperBible, Chapter 2
// Demonstrates the 7 Geometric Primitives
// Program by Richard S. Wright Jr.

#include <GLTools.h>	// OpenGL toolkit
#include <GLMatrixStack.h>
#include <GLFrame.h>
#include <GLFrustum.h>
#include <GLBatch.h>
#include <GLGeometryTransform.h>

#include <math.h>
#ifdef __APPLE__
#include <glut/glut.h>
#else
#ifdef ANGLE
#include "esGLUT/esGLUT.h"
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif
#endif

/////////////////////////////////////////////////////////////////////////////////
// An assortment of needed classes
GLShaderManager		shaderManager;
GLMatrixStack		modelViewMatrix;
GLMatrixStack		projectionMatrix;
GLFrame				cameraFrame;
GLFrame             objectFrame;
GLFrustum			viewFrustum;

GLBatch				pointBatch;
GLBatch				lineBatch;
GLBatch				lineStripBatch;
GLBatch				lineLoopBatch;
GLBatch				triangleBatch;
GLBatch             triangleStripBatch;
GLBatch             triangleFanBatch;

GLGeometryTransform	transformPipeline;
M3DMatrix44f		shadowMatrix;


GLfloat vGreen[] = { 0.0f, 1.0f, 0.0f, 1.0f };
GLfloat vBlack[] = { 0.0f, 0.0f, 0.0f, 1.0f };


// Keep track of effects step
int nStep = 0;

#ifdef ANGLE
GLBatch				wireFrameTriangleBatch;
GLBatch				wireFrameTriangleFanBatch;
GLBatch				wireFrameTriangleStripBatch;

GLuint				pointSizeShader;

///
// Flat Shader (GLT_SHADER_FLAT)
// This shader applies the given model view matrix to the verticies, 
// and uses a uniform color value.
static const char *szFlatShaderVP =	"uniform mat4 mvpMatrix;"
									"attribute vec4 vVertex;"
									"void main(void) "
									"{ gl_Position = mvpMatrix * vVertex; "
									" gl_PointSize = 4.0;"
									"}";

static const char *szFlatShaderFP = 
#ifdef OPENGL_ES
									"precision mediump float;"
#endif
									"uniform vec4 vColor;"
									"void main(void) "
									"{ gl_FragColor = vColor; "
									"}";

// pGeneratedVerts needs deleted by caller.
bool GenWireFrameTriangleFan(M3DVector3f *vVerts, GLuint nVerts, GLfloat **pGeneratedVerts, GLuint *nGeneratedVertsCount, GLenum *nPrimitiveType)
{
	if(nVerts < 3)
		return false;

	// First 2 point forms a segment, 2 vertex. After the 3rd point, each new point forms 2 segment, 4 vertex.
	// Total vertex count is 2 + (nVerts - 2) * 4 = (4 * nVerts) - 6.
	*nGeneratedVertsCount = (4 * nVerts) - 6;
	*pGeneratedVerts = new GLfloat[(*nGeneratedVertsCount) * 3];
	M3DVector3f* pOut = (M3DVector3f*)(*pGeneratedVerts);
	m3dCopyVector3(pOut[0], vVerts[0]);
	m3dCopyVector3(pOut[1], vVerts[1]);
	for(GLuint i = 0; i < nVerts - 2; ++i)
	{
		m3dCopyVector3(pOut[(i * 4) + 2], vVerts[0]);
		m3dCopyVector3(pOut[(i * 4) + 3], vVerts[i + 2]);
		m3dCopyVector3(pOut[(i * 4) + 4], vVerts[i + 2]);
		m3dCopyVector3(pOut[(i * 4) + 5], vVerts[i + 1]);
	}

	*nPrimitiveType = GL_LINES;
	return true;
}

// pGeneratedVerts needs deleted by caller.
bool GenWireFrameTriangleStrip(M3DVector3f *vVerts, GLuint nVerts, GLfloat **pGeneratedVerts, GLuint *nGeneratedVertsCount, GLenum *nPrimitiveType)
{
	if(nVerts < 3)
		return false;

	// First 2 point forms a segment, 2 vertex. After the 3rd point, each new point forms 2 segment, 4 vertex.
	// Total vertex count is 2 + (nVerts - 2) * 4 = (4 * nVerts) - 6.
	*nGeneratedVertsCount = (4 * nVerts) - 6;
	*pGeneratedVerts = new GLfloat[(*nGeneratedVertsCount) * 3];
	M3DVector3f* pOut = (M3DVector3f*)(*pGeneratedVerts);
	m3dCopyVector3(pOut[0], vVerts[0]);
	m3dCopyVector3(pOut[1], vVerts[1]);
	for(GLuint i = 0; i < nVerts - 2; ++i)
	{
		m3dCopyVector3(pOut[(i * 4) + 2], vVerts[i]);
		m3dCopyVector3(pOut[(i * 4) + 3], vVerts[i + 2]);
		m3dCopyVector3(pOut[(i * 4) + 4], vVerts[i + 2]);
		m3dCopyVector3(pOut[(i * 4) + 5], vVerts[i + 1]);
	}

	*nPrimitiveType = GL_LINES;
	return true;
}
#endif//ANGLE

///////////////////////////////////////////////////////////////////////////////
// This function does any needed initialization on the rendering context. 
// This is the first opportunity to do any OpenGL related tasks.
void SetupRC()
	{
    // Black background
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f );

	shaderManager.InitializeStockShaders();
	
#ifdef ANGLE
	pointSizeShader = gltLoadShaderPairSrcWithAttributes(szFlatShaderVP, szFlatShaderFP, 1, GLT_ATTRIBUTE_VERTEX, "vVertex");
#endif//ANGLE

	glEnable(GL_DEPTH_TEST);

	transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);

	cameraFrame.MoveForward(-15.0f);
    
    //////////////////////////////////////////////////////////////////////
    // Some points, more or less in the shape of Florida
    GLfloat vCoast[24][3] = {{2.80f, 1.20f, 0.0f }, {2.0f,  1.20f, 0.0f },
                            {2.0f,  1.08f, 0.0f },  {2.0f,  1.08f, 0.0f },
                            {0.0f,  0.80f, 0.0f },  {-.32f, 0.40f, 0.0f },
                            {-.48f, 0.2f, 0.0f },   {-.40f, 0.0f, 0.0f },
                            {-.60f, -.40f, 0.0f },  {-.80f, -.80f, 0.0f },
                            {-.80f, -1.4f, 0.0f },  {-.40f, -1.60f, 0.0f },
                            {0.0f, -1.20f, 0.0f },  { .2f, -.80f, 0.0f },
                            {.48f, -.40f, 0.0f },   {.52f, -.20f, 0.0f },
                            {.48f,  .20f, 0.0f },   {.80f,  .40f, 0.0f },
                            {1.20f, .80f, 0.0f },   {1.60f, .60f, 0.0f },
                            {2.0f, .60f, 0.0f },    {2.2f, .80f, 0.0f },
                            {2.40f, 1.0f, 0.0f },   {2.80f, 1.0f, 0.0f }};
    
    // Load point batch
    pointBatch.Begin(GL_POINTS, 24);
    pointBatch.CopyVertexData3f(vCoast);
    pointBatch.End();
    
    // Load as a bunch of line segments
    lineBatch.Begin(GL_LINES, 24);
    lineBatch.CopyVertexData3f(vCoast);
    lineBatch.End();
    
    // Load as a single line segment
    lineStripBatch.Begin(GL_LINE_STRIP, 24);
    lineStripBatch.CopyVertexData3f(vCoast);
    lineStripBatch.End();
    
    // Single line, connect first and last points
    lineLoopBatch.Begin(GL_LINE_LOOP, 24);
    lineLoopBatch.CopyVertexData3f(vCoast);
    lineLoopBatch.End();
    
    // For Triangles, we'll make a Pyramid
    GLfloat vPyramid[12][3] = { -2.0f, 0.0f, -2.0f, 
                                2.0f, 0.0f, -2.0f, 
                                0.0f, 4.0f, 0.0f,
                                
                                2.0f, 0.0f, -2.0f,
                                2.0f, 0.0f, 2.0f,
                                0.0f, 4.0f, 0.0f,
                                
                                2.0f, 0.0f, 2.0f,
                                -2.0f, 0.0f, 2.0f,
                                0.0f, 4.0f, 0.0f,
                                
                                -2.0f, 0.0f, 2.0f,
                                -2.0f, 0.0f, -2.0f,
                                 0.0f, 4.0f, 0.0f};
    
    triangleBatch.Begin(GL_TRIANGLES, 12);
    triangleBatch.CopyVertexData3f(vPyramid);
    triangleBatch.End();

#ifdef ANGLE
	wireFrameTriangleBatch.Begin(GL_LINE_LOOP, 12);
	wireFrameTriangleBatch.CopyVertexData3f(vPyramid);
    wireFrameTriangleBatch.End();
#endif//ANGLE

    // For a Triangle fan, just a 6 sided hex. Raise the center up a bit
    GLfloat vPoints[100][3];    // Scratch array, more than we need
    int nVerts = 0;
    GLfloat r = 3.0f;
    vPoints[nVerts][0] = 0.0f;
    vPoints[nVerts][1] = 0.0f;
    vPoints[nVerts][2] = 0.0f;

    for(GLfloat angle = 0; angle < M3D_2PI; angle += M3D_2PI / 6.0f) {
        nVerts++;
        vPoints[nVerts][0] = float(cos(angle)) * r;
        vPoints[nVerts][1] = float(sin(angle)) * r;
        vPoints[nVerts][2] = -0.5f;
        }

    // Close the fan
    nVerts++;
    vPoints[nVerts][0] = r;
    vPoints[nVerts][1] = 0;
    vPoints[nVerts][2] = 0.0f;
        
    // Load it up
    triangleFanBatch.Begin(GL_TRIANGLE_FAN, 8);
    triangleFanBatch.CopyVertexData3f(vPoints);
    triangleFanBatch.End();     

#ifdef ANGLE
	GLfloat* pGeneratedVerts = NULL;
	GLuint nGeneratedVertCount = 0;
	GLenum nPrimitiveType = 0;
	if(GenWireFrameTriangleFan(vPoints, 8, &pGeneratedVerts, &nGeneratedVertCount, &nPrimitiveType))
	{
		wireFrameTriangleFanBatch.Begin(nPrimitiveType, nGeneratedVertCount);
		wireFrameTriangleFanBatch.CopyVertexData3f(pGeneratedVerts);
		wireFrameTriangleFanBatch.End();
		delete pGeneratedVerts;
		pGeneratedVerts = NULL;
	}
#endif//ANGLE
        
    // For triangle strips, a little ring or cylinder segment
    int iCounter = 0;
    GLfloat radius = 3.0f;
    for(GLfloat angle = 0.0f; angle <= (2.0f*M3D_PI); angle += 0.3f)
		{
        GLfloat x = radius * sin(angle);
        GLfloat y = radius * cos(angle);
            
        // Specify the point and move the Z value up a little	
        vPoints[iCounter][0] = x;
        vPoints[iCounter][1] = y;
        vPoints[iCounter][2] = -0.5;
        iCounter++;

        vPoints[iCounter][0] = x;
        vPoints[iCounter][1] = y;
        vPoints[iCounter][2] = 0.5;
        iCounter++;            
		}

    // Close up the loop
    vPoints[iCounter][0] = vPoints[0][0];
    vPoints[iCounter][1] = vPoints[0][1];
    vPoints[iCounter][2] = -0.5;
    iCounter++;
    
    vPoints[iCounter][0] = vPoints[1][0];
    vPoints[iCounter][1] = vPoints[1][1];
    vPoints[iCounter][2] = 0.5;
    iCounter++;            
        
    // Load the triangle strip
    triangleStripBatch.Begin(GL_TRIANGLE_STRIP, iCounter);
    triangleStripBatch.CopyVertexData3f(vPoints);
    triangleStripBatch.End();    

#ifdef ANGLE
	if(GenWireFrameTriangleStrip(vPoints, iCounter, &pGeneratedVerts, &nGeneratedVertCount, &nPrimitiveType))
	{
		wireFrameTriangleStripBatch.Begin(nPrimitiveType, nGeneratedVertCount);
		wireFrameTriangleStripBatch.CopyVertexData3f(pGeneratedVerts);
		wireFrameTriangleStripBatch.End();
		delete pGeneratedVerts;
		pGeneratedVerts = NULL;
	}
#endif//ANGLE
    }


/////////////////////////////////////////////////////////////////////////
#ifdef ANGLE
	void DrawWireFramedBatchES(GLBatch* pBatch, GLBatch* pBatchWireFrame)
	{
		// Draw the batch solid green
		shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vGreen);
		pBatch->Draw();

		// Draw black outline
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Draw black wireframe version of geometry
		shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vBlack);
		pBatchWireFrame->Draw();

		// Put everything back the way we found it
		glDisable(GL_BLEND);
	}
#else//ANGLE
void DrawWireFramedBatch(GLBatch* pBatch)
    {
    // Draw the batch solid green
    shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vGreen);
    pBatch->Draw();
    
    // Draw black outline
    glPolygonOffset(-1.0f, -1.0f);      // Shift depth values
    glEnable(GL_POLYGON_OFFSET_LINE);

    // Draw lines antialiased
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Draw black wireframe version of geometry
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.5f);
    shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vBlack);
    pBatch->Draw();
    
    // Put everything back the way we found it
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_POLYGON_OFFSET_LINE);
    glLineWidth(1.0f);
    glDisable(GL_BLEND);
    glDisable(GL_LINE_SMOOTH);
    }
#endif//ANGLE

///////////////////////////////////////////////////////////////////////////////
// Called to draw scene
void RenderScene(void)
	{    
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	modelViewMatrix.PushMatrix();
		M3DMatrix44f mCamera;
		cameraFrame.GetCameraMatrix(mCamera);
		modelViewMatrix.MultMatrix(mCamera);

        M3DMatrix44f mObjectFrame;
        objectFrame.GetMatrix(mObjectFrame);
        modelViewMatrix.MultMatrix(mObjectFrame);

        shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vBlack);

        switch(nStep) {
            case 0:
#ifndef ANGLE
				glPointSize(4.0f);
				pointBatch.Draw();
				glPointSize(1.0f);
#else//ANGLE
				glUseProgram(pointSizeShader);
				GLint iTransform, iColor;
				iTransform = glGetUniformLocation(pointSizeShader, "mvpMatrix");
				glUniformMatrix4fv(iTransform, 1, GL_FALSE, transformPipeline.GetModelViewProjectionMatrix());

				iColor = glGetUniformLocation(pointSizeShader, "vColor");
				glUniform4fv(iColor, 1, vBlack);

				pointBatch.Draw();
#endif//ANGLE
                break;
            case 1:
                glLineWidth(2.0f);
                lineBatch.Draw();
                glLineWidth(1.0f);
                break;
            case 2:
                glLineWidth(2.0f);
                lineStripBatch.Draw();
                glLineWidth(1.0f);
                break;
            case 3:
                glLineWidth(2.0f);
                lineLoopBatch.Draw();
                glLineWidth(1.0f);
                break;
            case 4:
#ifndef ANGLE
                DrawWireFramedBatch(&triangleBatch);
#else
				DrawWireFramedBatchES(&triangleBatch, &wireFrameTriangleBatch);
#endif
				break;
            case 5:
#ifndef ANGLE
                DrawWireFramedBatch(&triangleStripBatch);
#else
				DrawWireFramedBatchES(&triangleStripBatch, &wireFrameTriangleStripBatch);
#endif
				break;
            case 6:
#ifndef ANGLE
                DrawWireFramedBatch(&triangleFanBatch);
#else
				DrawWireFramedBatchES(&triangleFanBatch, &wireFrameTriangleFanBatch);
#endif
				break;
            }
		
	modelViewMatrix.PopMatrix();

	// Flush drawing commands
	glutSwapBuffers();
    }


// Respond to arrow keys by moving the camera frame of reference
void SpecialKeys(int key, int x, int y)
    {
	if(key == GLUT_KEY_UP)
		objectFrame.RotateWorld(m3dDegToRad(-5.0f), 1.0f, 0.0f, 0.0f);
    
	if(key == GLUT_KEY_DOWN)
		objectFrame.RotateWorld(m3dDegToRad(5.0f), 1.0f, 0.0f, 0.0f);
	
	if(key == GLUT_KEY_LEFT)
		objectFrame.RotateWorld(m3dDegToRad(-5.0f), 0.0f, 1.0f, 0.0f);
    
	if(key == GLUT_KEY_RIGHT)
		objectFrame.RotateWorld(m3dDegToRad(5.0f), 0.0f, 1.0f, 0.0f);
    
	glutPostRedisplay();
    }




///////////////////////////////////////////////////////////////////////////////
// A normal ASCII key has been pressed.
// In this case, advance the scene when the space bar is pressed
void KeyPressFunc(unsigned char key, int x, int y)
	{
	if(key == 32)
		{
		nStep++;

		if(nStep > 6)
			nStep = 0;
		}
        
    switch(nStep)
        {
        case 0: 
            glutSetWindowTitle("GL_POINTS");
            break;
        case 1:
            glutSetWindowTitle("GL_LINES");
            break;
        case 2:
            glutSetWindowTitle("GL_LINE_STRIP");
            break;
        case 3:
            glutSetWindowTitle("GL_LINE_LOOP");
            break;
        case 4:
            glutSetWindowTitle("GL_TRIANGLES");
            break;
        case 5:
            glutSetWindowTitle("GL_TRIANGLE_STRIP");
            break;
        case 6:
            glutSetWindowTitle("GL_TRIANGLE_FAN");
            break;
        }
                
    glutPostRedisplay();
	}

///////////////////////////////////////////////////////////////////////////////
// Window has changed size, or has just been created. In either case, we need
// to use the window dimensions to set the viewport and the projection matrix.
void ChangeSize(int w, int h)
	{
	glViewport(0, 0, w, h);
	viewFrustum.SetPerspective(35.0f, float(w) / float(h), 1.0f, 500.0f);
	projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
	modelViewMatrix.LoadIdentity();
	}

///////////////////////////////////////////////////////////////////////////////
// Main entry point for GLUT based programs
int main(int argc, char* argv[])
	{
	gltSetWorkingDirectory(argv[0]);
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(800, 600);
	glutCreateWindow("GL_POINTS");
    glutReshapeFunc(ChangeSize);
    glutKeyboardFunc(KeyPressFunc);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
        
#ifndef ANGLE
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		return 1;
		}
#endif//ANGLE
	
	SetupRC();

	glutMainLoop();

#ifdef ANGLE
	glDeleteProgram(pointSizeShader);
#endif//ANGLE

	return 0;
	}
