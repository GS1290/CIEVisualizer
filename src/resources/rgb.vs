#ifdef C_GLSL_INCLUDE
const char* rgb_vs_src = R"(
#version 330

// Input vertex attributes
in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec3 vertexNormal;
in vec4 vertexColor;

// Input uniform values
uniform mat4 mvp;
uniform float uTime;

// Output vertex attributes (to fragment shader)
out vec2 fragTexCoord;
out vec4 fragColor;

// NOTE: Add your custom variables here
float den;
vec3 xyY;
vec3 r;

void main()
{
    // Send vertex attributes to fragment shader
    fragTexCoord = vertexTexCoord;
    fragColor = vertexColor;

    // Calculate final vertex position
    den = 0.6442*vertexPosition.x + 1.1920*vertexPosition.y + 1.2033*vertexPosition.z;
    xyY.x = (0.4123*vertexPosition.x + 0.3576*vertexPosition.y + 0.1805*vertexPosition.z)/den;
    xyY.z = 1-(0.2126*vertexPosition.x + 0.7152*vertexPosition.y + 0.0722*vertexPosition.z)/den;
    xyY.y = 0.2126*vertexPosition.x + 0.7152*vertexPosition.y + 0.0722*vertexPosition.z;

    // move the vertex
    r = (xyY - vertexPosition)*2*abs(fract(uTime/5) - 0.5f);
    gl_Position = mvp*vec4(vertexPosition+r, 1.0);
}
)";
#endif