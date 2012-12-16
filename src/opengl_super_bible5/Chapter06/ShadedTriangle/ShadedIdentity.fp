// The ShadedIdentity Shader
// Fragment Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
#version 100

#if GL_ES
precision mediump float;
#endif
varying vec4 vVaryingColor;

void main(void)
   { 
   gl_FragColor = vVaryingColor;
   }
