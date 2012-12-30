// SpaceFlight Shader
// Fragment Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
#version 100

#if GL_ES
precision mediump float;
#endif
varying vec4 vStarColor;

uniform sampler2D  starImage;

void main(void)
    { 
    gl_FragColor = texture2D(starImage, gl_PointCoord) * vStarColor;
    }
    