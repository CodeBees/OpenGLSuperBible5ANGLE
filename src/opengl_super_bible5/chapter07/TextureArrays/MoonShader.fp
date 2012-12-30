// MoonShader
// Fragment Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
#version 100

#if GL_ES
precision mediump float;
#endif

uniform sampler2D moonImage;

varying vec3 vMoonCoords;

void main(void)
   { 
   gl_FragColor = texture2D(moonImage, vMoonCoords.st);
   }