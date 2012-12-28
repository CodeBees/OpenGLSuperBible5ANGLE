// Rectangle Texture (replace) Shader
// Fragment Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
#version 100

#if GL_ES
precision mediump float;
#endif
uniform sampler2D  rectangleImage;

varying vec2 vVaryingTexCoord;

void main(void)
    { 
    gl_FragColor = texture2D(rectangleImage, vVaryingTexCoord);
    }
    