#version 410

uniform vec3        lightColor;
uniform vec3        lightPosition;

uniform vec3        viewPosition;

uniform int         modeColor;

uniform bool        mappingDiffuse;
uniform bool        mappingNormal;

uniform bool        switchNormal;
uniform bool        switchDiffuse;
uniform bool        switchSpecular;
uniform float       indexSpecular;

uniform sampler2D   diffuseTexture;
uniform sampler2D   normalTexture;

smooth  in vec4     grayColor;
flat    in vec4     flatColor;
smooth  in vec4     smoothColor;

        in          VS_OUT
        {
            vec3    fragPosition;
            vec3    fragNormal;
            vec2    uvCoordinate;
            mat3    TBN;
        }           fs_in;

        out vec4    fragColor;


vec3 calcAmbient()
{
    float ambientStrength;
    vec3  ambient;

    ambientStrength = 0.1f;
    ambient = ambientStrength * lightColor;
    return ambient;
}

vec3 calcNormal()
{
    vec3 normal;

    normal = normalize(fs_in.fragNormal);
    if (mappingNormal && switchNormal)
    {
        normal = texture(normalTexture, fs_in.uvCoordinate).rgb;
        normal = normalize(normal * 2.0f - 1.0f);
        normal = normalize(fs_in.TBN * normal);
    }
    return normal;
}

vec3 calcDiffuse(vec3 normal, vec3 lightDir)
{
    float diff;
    vec3 diffuse;

   diff = 1.0f;
   diffuse =  vec3(1.0f, 1.0f, 1.0f);
   if (switchDiffuse)
        diff = max(dot(normal, lightDir), 0.0);
    diffuse =  diff * lightColor;
    return diffuse;
}

vec3 calcSpecular(vec3 normal, vec3 lightDir, vec3 viewDir, vec3 reflectDir)
{
    float spec;
    vec3 specular;

    spec = 0.0f;
    specular = vec3(0.0f ,0.0f ,0.0f);

    if (switchSpecular)
    {
        spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        if (switchNormal)
        {
            vec3 halfwayDir = normalize(lightDir + viewDir);
            spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
        }
    }
    specular = indexSpecular * spec * lightColor;
    return specular;
}

void main()
{
    vec3    normal;
    vec3    lightDir;
    vec3    viewDir;
    vec3    reflectDir;

    normal = calcNormal();
    lightDir = normalize(lightPosition - fs_in.fragPosition);
    viewDir = normalize(viewPosition - fs_in.fragPosition);
    reflectDir = reflect(-lightDir, normal);

    vec3    ambient;
    vec3    diffuse;
    vec3    specular;

    ambient = calcAmbient();
    diffuse = calcDiffuse(normal, lightDir);
    specular = calcSpecular(normal, lightDir ,viewDir, reflectDir);

    if (modeColor == 0)
    {
        fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    }
    else if (modeColor == 1)
    {
        fragColor = grayColor;
    }
    else if (modeColor == 2)
    {
       fragColor = flatColor;
    }
    else if (modeColor == 3)
    {
        vec3 result = (ambient + diffuse + specular) * vec3(smoothColor);
           fragColor = vec4(result, 1.0f);
    }
    else if (modeColor == 4)
    {
        vec4 color;

        color = vec4(1.0f, 0.0f, 1.0f, 1.0f);
        if (mappingDiffuse)
            color = texture(diffuseTexture, fs_in.uvCoordinate);

        vec3 result = (ambient + diffuse + specular) * vec3(color);
       fragColor = vec4(result, 1.0f);
    }
}
