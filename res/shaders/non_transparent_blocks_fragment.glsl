#version 460 core
out vec4 FragColor;

in VS_OUT {
    vec4 vEyeSpacePosVertex;
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
    vec4 FragProjection;
} fs_in;

uniform sampler2D shadowMap;
uniform sampler2D blockTexture;
uniform sampler2D ssao;

uniform vec3 lightPos;
uniform vec3 viewPos;



vec4 vFogColor = vec4(0.1, 0.5, 0.8, 1.0); // Fog color
float fStart = 0.0; // This is only for linear fog
float fEnd = 16.0 * 3.0; // This is only for linear fog
float fDensity = 0.010; // For exp and exp2 equation
	
int iEquation = 2;


float getFogFactor(float fFogCoord)
{
	float fResult = 0.0;
	if(iEquation == 0)
		fResult = (fEnd-fFogCoord)/(fEnd-fStart);
	else if(iEquation == 1)
		fResult = exp(-fDensity*fFogCoord);
	else if(iEquation == 2)
		fResult = exp(-pow(fDensity*fFogCoord, 2.0));
		
	fResult = 1.0-clamp(fResult, 0.0, 1.0);
	
	return fResult;
}


float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // calculate bias (based on depth map resolution and slope)
    vec3 normal = normalize(fs_in.Normal);
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    float bias = max(0.0007 * (1.0 - dot(normal, lightDir)), 0.00007);
    // check whether current frag pos is in shadow
    float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    // PCF
    //float shadow = 0.0;
    int pcfSize = 4;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -pcfSize; x <= pcfSize; ++x)
    {
        for(int y = -pcfSize; y <= pcfSize; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
        }    
    }
    shadow /= (pcfSize * 2 * pcfSize * 2 - 4);
    
    // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
        shadow = 0.0;
        
    return shadow;
}

void main()
{   
    vec4 color = texture(blockTexture, fs_in.TexCoords).rgba;
    vec3 normal = normalize(fs_in.Normal);
    //normal = normalize(normal * 2.0 - 1.0); 
    vec3 projCoords = fs_in.FragProjection.xyz / fs_in.FragProjection.w;
    projCoords = projCoords * 0.5 + 0.5;
    vec3 lightColor = vec3(0.8);
    float AmbientOcclusion = texture(ssao, projCoords.xy).r;
    // ambient
    vec3 ambient = vec3(0.9 * AmbientOcclusion);

    // diffuse
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * lightColor;
    // specular
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = spec * lightColor;    
    // calculate shadow
    float shadow = ShadowCalculation(fs_in.FragPosLightSpace);

    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular));
    
    float fFogCoord = abs(fs_in.vEyeSpacePosVertex.z/fs_in.vEyeSpacePosVertex.w);

    FragColor = vec4(lighting, 1.0) * color;

    //FragColor = mix(FragColor, vFogColor, getFogFactor(fFogCoord));
}