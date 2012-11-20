// GeoTest.cpp
// OpenGL SuperBible
// Demonstrates OpenGL Backface culling, depth testing, and polygon mode
// Program by Richard S. Wright Jr.
#include <GLTools.h>	// OpenGL toolkit
#include <GLMatrixStack.h>
#include <GLFrame.h>
#include <GLFrustum.h>
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


GLFrame             viewFrame;
GLFrustum           viewFrustum;
GLTriangleBatch     torusBatch;
GLMatrixStack       modelViewMatix;
GLMatrixStack       projectionMatrix;
GLGeometryTransform transformPipeline;
GLShaderManager     shaderManager;

// Flags for effects
int iCull = 0;
int iDepth = 0;

#ifdef OPENGL_ES
#include <string>
GLenum primitiveType = GL_TRIANGLES;

GLuint uiShaderDefaultLightPointSize4;

// GLT_SHADER_DEFAULT_LIGHT
// Simple diffuse, directional, and vertex based light
static const char *szDefaultLightVP =	
"uniform mat4 mvMatrix;"
"uniform mat4 pMatrix;"
"varying vec4 vFragColor;"
"attribute vec4 vVertex;"
"attribute vec3 vNormal;"
"uniform vec4 vColor;"
"void main(void) { "
" mat3 mNormalMatrix;"
" mNormalMatrix[0] = mvMatrix[0].xyz;"
" mNormalMatrix[1] = mvMatrix[1].xyz;"
" mNormalMatrix[2] = mvMatrix[2].xyz;"
" vec3 vNorm = normalize(mNormalMatrix * vNormal);"
" vec3 vLightDir = vec3(0.0, 0.0, 1.0); "
" float fDot = max(0.0, dot(vNorm, vLightDir)); "
" vFragColor.rgb = vColor.rgb * fDot;"
" vFragColor.a = vColor.a;"
" mat4 mvpMatrix;"
" mvpMatrix = pMatrix * mvMatrix;"
" gl_Position = mvpMatrix * vVertex; "
" gl_PointSize = 4.0; "
"}";

static const char *szDefaultLightFP =	
#ifdef OPENGL_ES
"precision mediump float;"
#endif
"varying vec4 vFragColor; "
"void main(void) { "
" gl_FragColor = vFragColor; "
"}";
#endif//OPENGL_ES

#ifdef ANGLE
void UpdateTitle()
{
	std::string strTitle = "Geometry Test Program";
	strTitle += iDepth ? " - GL_DEPTH_TEST Enabled" : " - GL_DEPTH_TEST Disabled";
	strTitle += iCull ? " - GL_CULL_FACE Enabled" : " - GL_CULL_FACE Disabled";
	switch(primitiveType)
	{
	case GL_TRIANGLES:
		strTitle += " - Fill Mode";
		break;
	case GL_LINE_LOOP:
		strTitle += " - Line Mode";
		break;
	case GL_POINTS:
		strTitle += " - Point Mode";
		break;
	}

	glutSetWindowTitle(strTitle.c_str());
}

///////////////////////////////////////////////////////////////////////////////
// A normal ASCII key has been pressed.
void KeyPressFunc(unsigned char key, int x, int y)
{
	// 48 is ASCII's zero
	int nNum = key - 48;
	switch(nNum)
		{
		case 1:
			iDepth = !iDepth;
			break;
		case 2:
			iCull = !iCull;
			break;
        case 3:
			primitiveType = GL_TRIANGLES;
            break;
        case 4:
			primitiveType = GL_LINE_LOOP;
            break;
        case 5:
			primitiveType = GL_POINTS;
            break;
		}

	glutPostRedisplay();
	UpdateTitle();
}
#else//ANGLE

///////////////////////////////////////////////////////////////////////////////
// Reset flags as appropriate in response to menu selections
void ProcessMenu(int value)
	{
	switch(value)
		{
		case 1:
			iDepth = !iDepth;
			break;

		case 2:
			iCull = !iCull;
			break;

        case 3:
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            break;

        case 4:
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            break;
                
        case 5:
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            break;
		}

	glutPostRedisplay();
	}
#endif//ANGLE


// Called to draw scene
void RenderScene(void)
	{
	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Turn culling on if flag is set
	if(iCull)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);

	// Enable depth testing if flag is set
	if(iDepth)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);

		
    modelViewMatix.PushMatrix(viewFrame);
            
    GLfloat vRed[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    //shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vRed);
#ifndef OPENGL_ES
    shaderManager.UseStockShader(GLT_SHADER_DEFAULT_LIGHT, transformPipeline.GetModelViewMatrix(), transformPipeline.GetProjectionMatrix(), vRed);
#else//OPENGL_ES
	glUseProgram(uiShaderDefaultLightPointSize4);
	GLint iModelMatrix, iProjMatrix, iColor;
	iModelMatrix = glGetUniformLocation(uiShaderDefaultLightPointSize4, "mvMatrix");
	glUniformMatrix4fv(iModelMatrix, 1, GL_FALSE, transformPipeline.GetModelViewMatrix());

	iProjMatrix = glGetUniformLocation(uiShaderDefaultLightPointSize4, "pMatrix");
	glUniformMatrix4fv(iProjMatrix, 1, GL_FALSE, transformPipeline.GetProjectionMatrix());

	iColor = glGetUniformLocation(uiShaderDefaultLightPointSize4, "vColor");
	glUniform4fv(iColor, 1, vRed);

	torusBatch.SetPrimitiveType(primitiveType);
#endif//OPENGL_ES

    torusBatch.Draw();

    modelViewMatix.PopMatrix();


    glutSwapBuffers();
	}

// This function does any needed initialization on the rendering
// context. 
void SetupRC()
	{
	// Black background
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f );

    shaderManager.InitializeStockShaders();
#ifdef OPENGL_ES
	uiShaderDefaultLightPointSize4 = gltLoadShaderPairSrcWithAttributes(szDefaultLightVP, szDefaultLightFP, 2,
		GLT_ATTRIBUTE_VERTEX, "vVertex", GLT_ATTRIBUTE_NORMAL, "vNormal");
#endif//OPENGL_ES
    viewFrame.MoveForward(7.0f);

    // Make the torus
    gltMakeTorus(torusBatch, 1.0f, 0.3f, 52, 26);

#ifndef OPENGL_ES
    glPointSize(4.0f);
#endif//OPENGL_ES
}

void SpecialKeys(int key, int x, int y)
	{
	if(key == GLUT_KEY_UP)
		viewFrame.RotateWorld(m3dDegToRad(-5.0f), 1.0f, 0.0f, 0.0f);

	if(key == GLUT_KEY_DOWN)
		viewFrame.RotateWorld(m3dDegToRad(5.0f), 1.0f, 0.0f, 0.0f);
        
	if(key == GLUT_KEY_LEFT)
		viewFrame.RotateWorld(m3dDegToRad(-5.0f), 0.0f, 1.0f, 0.0f);
        
	if(key == GLUT_KEY_RIGHT)
		viewFrame.RotateWorld(m3dDegToRad(5.0f), 0.0f, 1.0f, 0.0f);

	// Refresh the Window
	glutPostRedisplay();
	}


void ChangeSize(int w, int h)
	{
	// Prevent a divide by zero
	if(h == 0)
		h = 1;

	// Set Viewport to window dimensions
    glViewport(0, 0, w, h);

    viewFrustum.SetPerspective(35.0f, float(w)/float(h), 1.0f, 100.0f);
    
    projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
    transformPipeline.SetMatrixStacks(modelViewMatix, projectionMatrix);
	}

///////////////////////////////////////////////////////////////////////////////
// Main entry point for GLUT based programs
int main(int argc, char* argv[])
    {
	gltSetWorkingDirectory(argv[0]);
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Geometry Test Program");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);

#ifdef ANGLE
	glutKeyboardFunc(KeyPressFunc);
	UpdateTitle();
#else//ANGLE
    // Create the Menu
    glutCreateMenu(ProcessMenu);
    glutAddMenuEntry("Toggle depth test",1);
    glutAddMenuEntry("Toggle cull backface",2);
    glutAddMenuEntry("Set Fill Mode", 3);
    glutAddMenuEntry("Set Line Mode", 4);
    glutAddMenuEntry("Set Point Mode", 5);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
        
    
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		return 1;
    }
#endif//ANGLE

	SetupRC();
    
	glutMainLoop();
#ifdef OPENGL_ES
	glDeleteProgram(uiShaderDefaultLightPointSize4);
#endif//OPENGL_ES
	return 0;
    }
