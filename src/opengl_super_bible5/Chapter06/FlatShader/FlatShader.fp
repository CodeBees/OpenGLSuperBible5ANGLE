// Flat Shader
// Fragment Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
#version 100

#if GL_ES
precision mediump float;
#endif

// Make geometry solid
uniform vec4 vColorValue;

// Output fragment color
varying vec4 vFragColor;


void main(void)
   { 
   gl_FragColor = vColorValue;
   }