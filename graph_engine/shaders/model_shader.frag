#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 viewPos;

uniform sampler2D shadowMap;

struct Material
{
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    float shininess;
};
uniform Material material;

struct DirectionLight
{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirectionLight dirLight;

struct PointLight
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic; 
};
# define POINT_LIGHTS_MAX 4
uniform int pointLightsCount;
uniform PointLight pointLights[POINT_LIGHTS_MAX];

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} fs_in;

vec3 calculateDirectionLight(DirectionLight light, vec3 viewDir, vec3 normal);
vec3 calculatePointLight(PointLight pointLight, vec3 viewDir, vec3 normal);

float shadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float bias = 0.005;
    float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0; 

    return shadow;
}

void main()
{   
    vec3 normal = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    vec3 result = calculateDirectionLight(dirLight, viewDir, normal);

    for (int i = 0; i < pointLightsCount; i++)
    {
        result += calculatePointLight(pointLights[i], viewDir, normal);
    }

    FragColor = vec4(result, 1.0);
}

vec3 calculateDirectionLight(DirectionLight light, vec3 viewDir, vec3 normal)
{
    vec3 lightDir = normalize(-light.direction);

    vec3 ambient = vec3(texture(material.texture_diffuse1, TexCoords)) * light.ambient;

    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * vec3(texture(material.texture_diffuse1, TexCoords)) * light.diffuse;

    vec3 reflected = reflect(-lightDir, normal);
    float spec = pow(max(dot(reflected, viewDir), 0.0), material.shininess);
    vec3 specular = spec * vec3(texture(material.texture_specular1, TexCoords)) * light.specular;

    //vec3 result = (ambient + diffuse + specular);  

    vec3 color = texture(material.texture_diffuse1, fs_in.TexCoords).rgb;
    float shadow = shadowCalculation(fs_in.FragPosLightSpace);                      
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;    
    
    return lighting;

    //return result;
}

vec3 calculatePointLight(PointLight pointLight, vec3 viewDir, vec3 normal)
{
    vec3 lightDir = normalize(pointLight.position - FragPos);

    vec3 ambient = vec3(texture(material.texture_diffuse1, TexCoords)) * pointLight.ambient;

    float diff = max(dot(normalize(lightDir), normal), 0.0);
    vec3 diffuse = diff * vec3(texture(material.texture_diffuse1, TexCoords)) * pointLight.diffuse;

    vec3 reflected = reflect(-lightDir, normal);
    float spec = pow(max(dot(reflected, viewDir), 0.0), material.shininess);
    vec3 specular = spec * vec3(texture(material.texture_specular1, TexCoords)) * pointLight.specular;

    vec3 result = (ambient + diffuse + specular);

    float distance = length(pointLight.position - FragPos);
    float attenuation = 1.0 / (pointLight.constant + pointLight.linear * distance + 
  			     pointLight.quadratic * (distance * distance));  

    result *= attenuation;

    return result;
}