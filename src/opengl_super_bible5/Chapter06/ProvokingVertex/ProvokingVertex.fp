// ProvokingVertex flat shader demo
// Fragment Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
#version 100

#if GL_ES
precision mediump float;
varying vec4 vVaryingColor;
#else
out vec4 vFragColor;
flat varying vec4 vVaryingColor;
#endif

void main(void)
   { 
#ifndef GL_ES
   vFragColor = vVaryingColor;
#else
   gl_FragColor = vVaryingColor;
#endif
   }