// Cell lighting Shader
// Fragment Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
#version 100

#if GL_ES
precision mediump float;
#endif
uniform sampler2D colorTable;

varying vec2 textureCoordinate;


void main(void)
   { 
   gl_FragColor = texture2D(colorTable, textureCoordinate);
   }