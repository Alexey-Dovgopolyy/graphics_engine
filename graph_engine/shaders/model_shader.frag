#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

//uniform vec3 lightDir;
uniform vec3 viewPos;
uniform vec3 lightPos;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

void main()
{   
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    vec3 ambient = vec3(texture(texture_diffuse1, TexCoords)) * 0.2;

    float diff = max(dot(normalize(lightDir), normal), 0.0);
    vec3 diffuse = diff * vec3(texture(texture_diffuse1, TexCoords));

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflected = reflect(-lightDir, normal);
    float spec = pow(max(dot(reflected, viewDir), 0.0), 32.0);
    vec3 specular = spec * vec3(texture(texture_specular1, TexCoords));

    vec3 result = (ambient + diffuse + specular);

    FragColor = vec4(result, 1.0);
}