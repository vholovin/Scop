#version 410

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

uniform mat4        mvpMatrix;
uniform mat4        modelMatrix;

smooth  out vec4    grayColor;
flat    out vec4    flatColor;
smooth  out vec4    smoothColor;

        out         VS_OUT
        {
            vec3    fragPosition;
            vec3    fragNormal;
            vec2    uvCoordinate;
            mat3    TBN;
        }           vs_out;

vec4 setColor(int id)
{
    vec4 color;

    color = vec4(vertex.y * 0.4f + 0.4f, vertex.z * 0.1f + vertex.y * 0.4f + 0.1f, 0.2f, 1.0f);
    return color;
}

vec4 setGray(int id)
{
    vec4 gray;
    int  res;

    res = id % 3;
    if (res == 0)
        gray = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    else if (res == 1)
        gray = vec4(0.5f, 0.5f, 0.5f, 1.0f);
    else
        gray = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    return gray;
}

void main()
{
    gl_Position = mvpMatrix * vec4(vertex, 1.0);

    grayColor = setGray(gl_VertexID);
    flatColor = setColor(gl_VertexID);
    smoothColor = flatColor;

    vs_out.fragPosition = vec3(modelMatrix * vec4(vertex, 1.0f));
    vs_out.fragNormal = mat3(transpose(inverse(modelMatrix))) * normal;
    vs_out.uvCoordinate = uv;

    mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
    vec3 T = normalize(normalMatrix * tangent);
    vec3 B = normalize(normalMatrix * bitangent);
    vec3 N = normalize(normalMatrix * normal);
    vs_out.TBN = mat3(T, B, N);
}