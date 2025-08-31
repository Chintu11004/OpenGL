//
//  Basic.fsh
//  LearnOpenGL
//
//  Created by Tejas Srinivasan on 07/06/25.
//
#version 330 core

struct Material {
	//vec3 ambient;
	//vec3 diffuse;
	sampler2D diffuseTexture;
	//vec3 specular;
	sampler2D specularTexture;
	sampler2D emissiveMap;
	float shininess;
};

struct Light {
	vec3 direction;

	vec3 ambientStrength;
	vec3 diffuseStrength;
	vec3 specularStrength;
};

out vec4 FragColor;

//in vec3 vertColor;
in vec2 texCoord;
in vec3 Normal;
in vec3 FragPos;

//uniform sampler2D texture0;
//uniform sampler2D texture1;
uniform vec3 lightColor;
uniform Material material;
uniform Light light;

void main(){
	// ambientl light
	vec3 ambientLight = lightColor * pow(vec3(texture(material.diffuseTexture, texCoord)), vec3(2.2f)) * light.ambientStrength;// * ambientStrength;
	//FragColor = pow(vec4(pow(texture(texture0, texCoord).rgb, vec3(2.2f)) * vertColor, 1.0f), vec4(1/2.2f));
	//FragColor = mix(texture(texture0, texCoord), texture(texture1, texCoord), 0.2f);
	
	//diffused light
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuseLight = diff * lightColor * pow(vec3(texture(material.diffuseTexture, texCoord)), vec3(2.2f)) * light.diffuseStrength;
	
	//specular light
	float specularStrength = 0.5;
	vec3 viewDir = normalize(-FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specularLight = spec * lightColor * pow(vec3(texture(material.specularTexture, texCoord)), vec3(2.2f)) * light.specularStrength;
	
	vec3 result;
	//if (texture(material.specularTexture, texCoord).rgb == vec3(0.0))
	//{
		//result = (ambientLight + diffuseLight + specularLight) + pow(vec3(texture(material.emissiveMap, texCoord)), vec3(2.2));
	//}
	//else {
		result = (ambientLight + diffuseLight + specularLight);
	//}
	
	FragColor = vec4(pow(result, vec3(1/2.2f)), 1.0f);
	//FragColor = vec4(result, 1.0f);
}
