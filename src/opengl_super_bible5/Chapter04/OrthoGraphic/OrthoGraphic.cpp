// Orthographic.cpp
// OpenGL SuperBible
// Demonstrates OpenGL Orthographic Projections
// Program by Richard S. Wright Jr.
#include <GLTools.h>	// OpenGL toolkit
#include <GLMatrixStack.h>
#include <GLFrame.h>
#include <GLFrustum.h>
#include <GLGeometryTransform.h>
#include <GLBatch.h>

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
GLBatch             tubeBatch;
GLBatch             innerBatch;
GLMatrixStack       modelViewMatix;
GLMatrixStack       projectionMatrix;
GLGeometryTransform transformPipeline;
GLShaderManager     shaderManager;



// Called to draw scene
void RenderScene(void)
	{
	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

		
    modelViewMatix.PushMatrix(viewFrame);
            
    GLfloat vRed[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    GLfloat vGray[] = { 0.75f, 0.75f, 0.75f, 1.0f };
    shaderManager.UseStockShader(GLT_SHADER_DEFAULT_LIGHT, transformPipeline.GetModelViewMatrix(), transformPipeline.GetProjectionMatrix(), vRed);
    tubeBatch.Draw();


    shaderManager.UseStockShader(GLT_SHADER_DEFAULT_LIGHT, transformPipeline.GetModelViewMatrix(), transformPipeline.GetProjectionMatrix(), vGray);
    innerBatch.Draw();

    modelViewMatix.PopMatrix();


    glutSwapBuffers();
	}

// This function does any needed initialization on the rendering
// context. 
void SetupRC()
	{
	// Black background
	glClearColor(0.0f, 0.0f, 0.75f, 1.0f );

//    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    shaderManager.InitializeStockShaders();
  
#ifdef OPENGL_ES
    tubeBatch.Begin(GL_TRIANGLES, 200);
#else
    tubeBatch.Begin(GL_QUADS, 200);
#endif
    
    float fZ = 100.0f;
    float bZ = -100.0f;

    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
    tubeBatch.Vertex3f(-50.0f, 50.0f, 100.0f);
    
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
    tubeBatch.Vertex3f(-50.0f, -50.0f, fZ);

    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
    tubeBatch.Vertex3f(-35.0f, -50.0f, fZ);
    
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
    tubeBatch.Vertex3f(-35.0f,50.0f,fZ);
    
#ifdef OPENGL_ES
	tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
	tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
	tubeBatch.Vertex3f(-50.0f, 50.0f, 100.0f);

	tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
	tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
	tubeBatch.Vertex3f(-35.0f, -50.0f, fZ);
#endif

    // Right Panel
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
    tubeBatch.Vertex3f(50.0f, 50.0f, fZ);
    
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
    tubeBatch.Vertex3f(35.0f, 50.0f, fZ);
    
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
    tubeBatch.Vertex3f(35.0f, -50.0f, fZ);

    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
    tubeBatch.Vertex3f(50.0f,-50.0f,fZ);

#ifdef OPENGL_ES
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
    tubeBatch.Vertex3f(50.0f, 50.0f, fZ);

    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
    tubeBatch.Vertex3f(35.0f, -50.0f, fZ);
#endif
    
    // Top Panel
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
    tubeBatch.Vertex3f(-35.0f, 50.0f, fZ);
    
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
    tubeBatch.Vertex3f(-35.0f, 35.0f, fZ);
    
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
    tubeBatch.Vertex3f(35.0f, 35.0f, fZ);

    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
    tubeBatch.Vertex3f(35.0f, 50.0f,fZ);

#ifdef OPENGL_ES
	tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
	tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
	tubeBatch.Vertex3f(-35.0f, 50.0f, fZ);

	tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
	tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
	tubeBatch.Vertex3f(35.0f, 35.0f, fZ);
#endif
    
    // Bottom Panel
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
    tubeBatch.Vertex3f(-35.0f, -35.0f, fZ);
    
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
    tubeBatch.Vertex3f(-35.0f, -50.0f, fZ);
    
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
    tubeBatch.Vertex3f(35.0f, -50.0f, fZ);
    
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
    tubeBatch.Vertex3f(35.0f, -35.0f,fZ);

#ifdef OPENGL_ES
	tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
	tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
	tubeBatch.Vertex3f(-35.0f, -35.0f, fZ);

	tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
	tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
	tubeBatch.Vertex3f(35.0f, -50.0f, fZ);
#endif
    
    // Top length section ////////////////////////////
    // Normal points up Y axis
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 1.0f, 0.0f);
    tubeBatch.Vertex3f(-50.0f, 50.0f, fZ);

    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 1.0f, 0.0f);
    tubeBatch.Vertex3f(50.0f, 50.0f, fZ);
    
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 1.0f, 0.0f);
    tubeBatch.Vertex3f(50.0f, 50.0f, bZ);
    
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 1.0f, 0.0f);
    tubeBatch.Vertex3f(-50.0f,50.0f,bZ);

#ifdef OPENGL_ES
	tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
	tubeBatch.Normal3f(0.0f, 1.0f, 0.0f);
	tubeBatch.Vertex3f(-50.0f, 50.0f, fZ);

	tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
	tubeBatch.Normal3f(0.0f, 1.0f, 0.0f);
	tubeBatch.Vertex3f(50.0f, 50.0f, bZ);
#endif
    
    // Bottom section
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, -1.0f, 0.0f);
    tubeBatch.Vertex3f(-50.0f, -50.0f, fZ);

    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, -1.0f, 0.0f);
    tubeBatch.Vertex3f(-50.0f, -50.0f, bZ);
    
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, -1.0f, 0.0f);
    tubeBatch.Vertex3f(50.0f, -50.0f, bZ);
    
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, -1.0f, 0.0f);
    tubeBatch.Vertex3f(50.0f, -50.0f, fZ);

#ifdef OPENGL_ES
	tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
	tubeBatch.Normal3f(0.0f, -1.0f, 0.0f);
	tubeBatch.Vertex3f(-50.0f, -50.0f, fZ);

	tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
	tubeBatch.Normal3f(0.0f, -1.0f, 0.0f);
	tubeBatch.Vertex3f(50.0f, -50.0f, bZ);
#endif
    
    // Left section
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(1.0f, 0.0f, 0.0f);
    tubeBatch.Vertex3f(50.0f, 50.0f, fZ);
    
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(1.0f, 0.0f, 0.0f);
    tubeBatch.Vertex3f(50.0f, -50.0f, fZ);
    
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(1.0f, 0.0f, 0.0f);
    tubeBatch.Vertex3f(50.0f, -50.0f, bZ);
    
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(1.0f, 0.0f, 0.0f);
    tubeBatch.Vertex3f(50.0f, 50.0f, bZ);

#ifdef OPENGL_ES
	tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
	tubeBatch.Normal3f(1.0f, 0.0f, 0.0f);
	tubeBatch.Vertex3f(50.0f, 50.0f, fZ);

	tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
	tubeBatch.Normal3f(1.0f, 0.0f, 0.0f);
	tubeBatch.Vertex3f(50.0f, -50.0f, bZ);
#endif
    
    // Right Section
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(-1.0f, 0.0f, 0.0f);
    tubeBatch.Vertex3f(-50.0f, 50.0f, fZ);
    
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(-1.0f, 0.0f, 0.0f);
    tubeBatch.Vertex3f(-50.0f, 50.0f, bZ);
    
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(-1.0f, 0.0f, 0.0f);
    tubeBatch.Vertex3f(-50.0f, -50.0f, bZ);

    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(-1.0f, 0.0f, 0.0f);
    tubeBatch.Vertex3f(-50.0f, -50.0f, fZ);
        
#ifdef OPENGL_ES
	tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
	tubeBatch.Normal3f(-1.0f, 0.0f, 0.0f);
	tubeBatch.Vertex3f(-50.0f, 50.0f, fZ);

	tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
	tubeBatch.Normal3f(-1.0f, 0.0f, 0.0f);
	tubeBatch.Vertex3f(-50.0f, -50.0f, bZ);
#endif    
    
    // Pointing straight out Z        
    // Left Panel
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
    tubeBatch.Vertex3f(-50.0f, 50.0f, fZ);
    
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
    tubeBatch.Vertex3f(-50.0f, -50.0f, fZ);
    
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
    tubeBatch.Vertex3f(-35.0f, -50.0f, fZ);
    
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
    tubeBatch.Vertex3f(-35.0f,50.0f,fZ);

#ifdef OPENGL_ES
	tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
	tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
	tubeBatch.Vertex3f(-50.0f, 50.0f, fZ);

	tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
	tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
	tubeBatch.Vertex3f(-35.0f, -50.0f, fZ);
#endif
    
    // Right Panel
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
    tubeBatch.Vertex3f(50.0f, 50.0f, fZ);
    
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
    tubeBatch.Vertex3f(35.0f, 50.0f, fZ);
    
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
    tubeBatch.Vertex3f(35.0f, -50.0f, fZ);
    
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
    tubeBatch.Vertex3f(50.0f,-50.0f,fZ);

#ifdef OPENGL_ES
	tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
	tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
	tubeBatch.Vertex3f(50.0f, 50.0f, fZ);

	tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
	tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
	tubeBatch.Vertex3f(35.0f, -50.0f, fZ);
#endif
    
    // Top Panel
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
    tubeBatch.Vertex3f(-35.0f, 50.0f, fZ);
    
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
    tubeBatch.Vertex3f(-35.0f, 35.0f, fZ);
    
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
    tubeBatch.Vertex3f(35.0f, 35.0f, fZ);

        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
    tubeBatch.Vertex3f(35.0f, 50.0f,fZ);

#ifdef OPENGL_ES
	tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
	tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
	tubeBatch.Vertex3f(-35.0f, 50.0f, fZ);

	tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
	tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
	tubeBatch.Vertex3f(35.0f, 35.0f, fZ);
#endif
    
    // Bottom Panel
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
    tubeBatch.Vertex3f(-35.0f, -35.0f, fZ);
    
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
    tubeBatch.Vertex3f(-35.0f, -50.0f, fZ);
    
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
    tubeBatch.Vertex3f(35.0f, -50.0f, fZ);
    
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
    tubeBatch.Vertex3f(35.0f, -35.0f,fZ);

#ifdef OPENGL_ES
	tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
	tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
	tubeBatch.Vertex3f(-35.0f, -35.0f, fZ);

	tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
	tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
	tubeBatch.Vertex3f(35.0f, -50.0f, fZ);
#endif
        
    // Top length section ////////////////////////////
    // Normal points up Y axis
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 1.0f, 0.0f);
    tubeBatch.Vertex3f(-50.0f, 50.0f, fZ);

        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 1.0f, 0.0f);
    tubeBatch.Vertex3f(50.0f, 50.0f, fZ);

        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 1.0f, 0.0f);
    tubeBatch.Vertex3f(50.0f, 50.0f, bZ);

        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 1.0f, 0.0f);
    tubeBatch.Vertex3f(-50.0f,50.0f,bZ);

#ifdef OPENGL_ES
	tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
	tubeBatch.Normal3f(0.0f, 1.0f, 0.0f);
	tubeBatch.Vertex3f(-50.0f, 50.0f, fZ);

	tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
	tubeBatch.Normal3f(0.0f, 1.0f, 0.0f);
	tubeBatch.Vertex3f(50.0f, 50.0f, bZ);
#endif
    
    // Bottom section
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, -1.0f, 0.0f);
    tubeBatch.Vertex3f(-50.0f, -50.0f, fZ);

        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, -1.0f, 0.0f);
    tubeBatch.Vertex3f(-50.0f, -50.0f, bZ);

        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, -1.0f, 0.0f);
    tubeBatch.Vertex3f(50.0f, -50.0f, bZ);

        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, -1.0f, 0.0f);
    tubeBatch.Vertex3f(50.0f, -50.0f, fZ);

#ifdef OPENGL_ES
	tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
	tubeBatch.Normal3f(0.0f, -1.0f, 0.0f);
	tubeBatch.Vertex3f(-50.0f, -50.0f, fZ);

	tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
	tubeBatch.Normal3f(0.0f, -1.0f, 0.0f);
	tubeBatch.Vertex3f(50.0f, -50.0f, bZ);
#endif
    
    // Left section
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(1.0f, 0.0f, 0.0f);
    tubeBatch.Vertex3f(50.0f, 50.0f, fZ);

        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(1.0f, 0.0f, 0.0f);
    tubeBatch.Vertex3f(50.0f, -50.0f, fZ);

        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(1.0f, 0.0f, 0.0f);
    tubeBatch.Vertex3f(50.0f, -50.0f, bZ);

        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(1.0f, 0.0f, 0.0f);
    tubeBatch.Vertex3f(50.0f, 50.0f, bZ);

#ifdef OPENGL_ES
	tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
	tubeBatch.Normal3f(1.0f, 0.0f, 0.0f);
	tubeBatch.Vertex3f(50.0f, 50.0f, fZ);

	tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
	tubeBatch.Normal3f(1.0f, 0.0f, 0.0f);
	tubeBatch.Vertex3f(50.0f, -50.0f, bZ);
#endif
    
    // Right Section
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(-1.0f, 0.0f, 0.0f);
    tubeBatch.Vertex3f(-50.0f, 50.0f, fZ);

        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(-1.0f, 0.0f, 0.0f);
    tubeBatch.Vertex3f(-50.0f, 50.0f, bZ);

        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(-1.0f, 0.0f, 0.0f);
    tubeBatch.Vertex3f(-50.0f, -50.0f, bZ);

        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(-1.0f, 0.0f, 0.0f);
    tubeBatch.Vertex3f(-50.0f, -50.0f, fZ);

#ifdef OPENGL_ES
	tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
	tubeBatch.Normal3f(-1.0f, 0.0f, 0.0f);
	tubeBatch.Vertex3f(-50.0f, 50.0f, fZ);

	tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
	tubeBatch.Normal3f(-1.0f, 0.0f, 0.0f);
	tubeBatch.Vertex3f(-50.0f, -50.0f, bZ);
#endif

        // Left Panel
        tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
        tubeBatch.Vertex3f(-35.0f,50.0f,bZ);

        tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
        tubeBatch.Vertex3f(-35.0f, -50.0f, bZ);
        
        tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
        tubeBatch.Vertex3f(-50.0f, -50.0f, bZ);
        
        tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
        tubeBatch.Vertex3f(-50.0f, 50.0f, bZ);

#ifdef OPENGL_ES
		tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
		tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
		tubeBatch.Vertex3f(-35.0f,50.0f,bZ);

		tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
		tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
		tubeBatch.Vertex3f(-50.0f, -50.0f, bZ);
#endif
        
        // Right Panel
        tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);

        tubeBatch.Vertex3f(50.0f,-50.0f,bZ);

        tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);

        tubeBatch.Vertex3f(35.0f, -50.0f, bZ);

        tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);

        tubeBatch.Vertex3f(35.0f, 50.0f, bZ);
        
        tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
        
        tubeBatch.Vertex3f(50.0f, 50.0f, bZ);

#ifdef OPENGL_ES
		tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
		tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);

		tubeBatch.Vertex3f(50.0f,-50.0f,bZ);

		tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
		tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);

		tubeBatch.Vertex3f(35.0f, 50.0f, bZ);
#endif
        
        // Top Panel
        tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
        tubeBatch.Vertex3f(35.0f, 50.0f, bZ);
        tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
        tubeBatch.Vertex3f(35.0f, 35.0f, bZ);
        tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
        tubeBatch.Vertex3f(-35.0f, 35.0f, bZ);


        tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
        tubeBatch.Vertex3f(-35.0f, 50.0f, bZ);

#ifdef OPENGL_ES
		tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
		tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
		tubeBatch.Vertex3f(35.0f, 50.0f, bZ);
		tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
		tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
		tubeBatch.Vertex3f(-35.0f, 35.0f, bZ);
#endif
    
        // Bottom Panel
        tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
        tubeBatch.Vertex3f(35.0f, -35.0f,bZ);
        tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
        tubeBatch.Vertex3f(35.0f, -50.0f, bZ);
        tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
        tubeBatch.Vertex3f(-35.0f, -50.0f, bZ);


        tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
        tubeBatch.Vertex3f(-35.0f, -35.0f, bZ);

#ifdef OPENGL_ES
		tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
		tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
		tubeBatch.Vertex3f(35.0f, -35.0f,bZ);
		tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
		tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
		tubeBatch.Vertex3f(-35.0f, -50.0f, bZ);
#endif
    
        tubeBatch.End();

#ifndef OPENGL_ES
        innerBatch.Begin(GL_QUADS, 40);
#else
        innerBatch.Begin(GL_TRIANGLES, 40);
#endif
        
        // Insides /////////////////////////////
        // Normal points up Y axis
        innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
        innerBatch.Normal3f(0.0f, 1.0f, 0.0f);
        innerBatch.Vertex3f(-35.0f, 35.0f, fZ);
        innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
        innerBatch.Normal3f(0.0f, 1.0f, 0.0f);
        innerBatch.Vertex3f(35.0f, 35.0f, fZ);
        innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
        innerBatch.Normal3f(0.0f, 1.0f, 0.0f);
        innerBatch.Vertex3f(35.0f, 35.0f, bZ);
        innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
        innerBatch.Normal3f(0.0f, 1.0f, 0.0f);
        innerBatch.Vertex3f(-35.0f,35.0f,bZ);

#ifdef OPENGL_ES
		innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
		innerBatch.Normal3f(0.0f, 1.0f, 0.0f);
		innerBatch.Vertex3f(-35.0f, 35.0f, fZ);
		innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
		innerBatch.Normal3f(0.0f, 1.0f, 0.0f);
		innerBatch.Vertex3f(35.0f, 35.0f, bZ);
#endif
		
        // Bottom section
        innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
        innerBatch.Normal3f(0.0f, 1.0f, 0.0f);
        innerBatch.Vertex3f(-35.0f, -35.0f, fZ);
        innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
        innerBatch.Normal3f(0.0f, 1.0f, 0.0f);
        innerBatch.Vertex3f(-35.0f, -35.0f, bZ);
        innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
        innerBatch.Normal3f(0.0f, 1.0f, 0.0f);
        innerBatch.Vertex3f(35.0f, -35.0f, bZ);
        innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
        innerBatch.Normal3f(0.0f, 1.0f, 0.0f);
        innerBatch.Vertex3f(35.0f, -35.0f, fZ);

#ifdef OPENGL_ES
		innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
		innerBatch.Normal3f(0.0f, 1.0f, 0.0f);
		innerBatch.Vertex3f(-35.0f, -35.0f, fZ);
		innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
		innerBatch.Normal3f(0.0f, 1.0f, 0.0f);
		innerBatch.Vertex3f(35.0f, -35.0f, bZ);
#endif
        
        // Left section
        innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
        innerBatch.Normal3f(1.0f, 0.0f, 0.0f);
        innerBatch.Vertex3f(-35.0f, 35.0f, fZ);
        innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
        innerBatch.Normal3f(1.0f, 0.0f, 0.0f);
        innerBatch.Vertex3f(-35.0f, 35.0f, bZ);
        innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
        innerBatch.Normal3f(1.0f, 0.0f, 0.0f);
        innerBatch.Vertex3f(-35.0f, -35.0f, bZ);
        innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
        innerBatch.Normal3f(1.0f, 0.0f, 0.0f);
        innerBatch.Vertex3f(-35.0f, -35.0f, fZ);

#ifdef OPENGL_ES
		innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
		innerBatch.Normal3f(1.0f, 0.0f, 0.0f);
		innerBatch.Vertex3f(-35.0f, 35.0f, fZ);
		innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
		innerBatch.Normal3f(1.0f, 0.0f, 0.0f);
		innerBatch.Vertex3f(-35.0f, -35.0f, bZ);
#endif
        
        // Right Section
        innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
        innerBatch.Normal3f(-1.0f, 0.0f, 0.0f);
        innerBatch.Vertex3f(35.0f, 35.0f, fZ);
        innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
        innerBatch.Normal3f(-1.0f, 0.0f, 0.0f);
        innerBatch.Vertex3f(35.0f, -35.0f, fZ);
        innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
        innerBatch.Normal3f(-1.0f, 0.0f, 0.0f);
        innerBatch.Vertex3f(35.0f, -35.0f, bZ);
        innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
        innerBatch.Normal3f(-1.0f, 0.0f, 0.0f);
        innerBatch.Vertex3f(35.0f, 35.0f, bZ);

#ifdef OPENGL_ES
		innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
		innerBatch.Normal3f(-1.0f, 0.0f, 0.0f);
		innerBatch.Vertex3f(35.0f, 35.0f, fZ);
		innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
		innerBatch.Normal3f(-1.0f, 0.0f, 0.0f);
		innerBatch.Vertex3f(35.0f, -35.0f, bZ);
#endif
        
        innerBatch.End();

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

    viewFrustum.SetOrthographic(-130.0f, 130.0f, -130.0f, 130.0f, -130.0f, 130.0f);
    
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
	glutCreateWindow("Orthographic Projection Example");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
        
#ifndef ANGLE
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		return 1;
    }
#endif

	SetupRC();
    
	glutMainLoop();
	return 0;
    }
