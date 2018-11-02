#version 330

/******************************************************************************/
/*                                                                            */
/* Estruturas auxiliares                                                      */
/*                                                                            */
/******************************************************************************/

struct Ray
{
    vec3 orig;
    vec3 dir;
};

struct Plane
{
    vec3 point;
    vec3 normal;
};

struct Sphere
{
    vec3 center;
    float radius;
    vec4 color;
};

struct Material
{
    float diffuseK;
    vec4 diffuseColor;
    float specularK;
    float shininess;
};

struct Light
{
    vec3 position;
    vec4 color;
};

/******************************************************************************/
/*                                                                            */
/* Uniformes                                                                  */
/*                                                                            */
/******************************************************************************/

// Matrizes
uniform mat4 model;
uniform mat4 view;  
uniform mat4 projection;  
uniform vec2 viewport;  

// Planos near e far
uniform vec3 nearRight;                                                                                           
uniform vec3 nearUp;                                                                                             
uniform vec3 nearCenter;                                                                                               
uniform vec3 farRight;                                                                                            
uniform vec3 farUp;                                                                                              
uniform vec3 farCenter;  

// Luzes                                                                                        
uniform Light light; 

// Material de todas esferas
uniform Material material;

// Objetos de cena
uniform Sphere spheres[16];
uniform Plane ground;

// Cor de saída
out vec4 fragColor;

/******************************************************************************/
/*                                                                            */
/* Funções auxiliares                                                         */
/*                                                                            */
/******************************************************************************/

Ray getCurrentRay()
{
    // Normaliza frag coord para ir de -viewport/2 até +viewport/2
    vec2 normalizedFragCoord = 2.0 * gl_FragCoord.xy / viewport - 1.0;

    // Fragmento unprojected (mundo) no plano near
    vec4 fragmentNear = vec4(nearCenter + 
        nearRight * normalizedFragCoord.x + 
        nearUp   * normalizedFragCoord.y, 1);
        
    // Fragmento unprojected (mundo) no plano far
    vec4 fragmentFar = vec4(farCenter + 
        farRight * normalizedFragCoord.x + 
        farUp * normalizedFragCoord.y, 1);      

    Ray ray;
    ray.orig = fragmentNear.xyz;    
    ray.dir  = normalize((fragmentFar - fragmentNear).xyz);
    
    return ray;
}

vec4 phong(in vec3 point, in vec3 normal)
{
    vec3 L = light.position - point;
    vec3 r = reflect(-L, normal);
    vec3 eye = (view * model)[3].xyz;
    vec3 v = eye - point;
    
    vec4 cD = material.diffuseK * max(dot(normal, L), 0.f) * material.diffuseColor;
    vec4 cS = material.specularK * pow(max(dot(r, v), 0), material.shininess) * light.color;
    
    return cD + cS;
}

bool solve_bhaskara(
    in float a, in float b, in float c, 
    out float t0, out float t1)
{
    float delta = b*b - 4*a*c;
    if(delta < 0)
        return false;
        
    if(delta == 0)
    {
        t0 = t1 = -b / (2*a);
        return true;
    }
        
    t0 = (-b + sqrt(delta)) / (2*a);
    t1 = (-b - sqrt(delta)) / (2*a);
    
    // Swap
    if(t1 < t0)
    {
        float temp = t1;
        t1 = t0;
        t0 = temp;
    }
    
    return true;
}    

bool intersectRaySphere(
    in Ray ray, in Sphere sphere, 
    out vec3 intersection, out vec3 normal)
{
    vec4 worldCenter = view * model * vec4(sphere.center, 1);
    vec3 center2orig = ray.orig - worldCenter.xyz;
    
    float a = 1;
    float b = 2.0f * dot(center2orig, ray.dir);
    float c = dot(center2orig, center2orig) - sphere.radius * sphere.radius;
    
    float t0, t1;
    if(!solve_bhaskara(a, b, c, t0, t1))
        return false;
    
    // Se o maior tempo for negativo...
    if(t1 < 0)
        return false;
    
    float t = t0 < 0 ? t1 : t0;
    intersection = ray.orig + t * ray.dir;
    normal = normalize(intersection - sphere.center);
    
    return true;
}
 
void main(void)
{
    float time = 0;
    vec3 intersection, normal;

    // Testa intersecao com esferas
    if(!intersectRaySphere(getCurrentRay(), spheres[0], intersection, normal))
    {
        discard;
        return;
    }
    
    // Aplica iluminacao
//    fragColor = vec4(1); //phong(intersection, normal);
    vec3 axis = abs(normalize(intersection - spheres[0].center));
    fragColor = /*projection * view **/ vec4(axis, 1);

    // Projeta no espaço de clip o ponto da interceptacao
    vec4 newCoord = projection * view * vec4(intersection, 1);
    newCoord.z /= newCoord.w;

    // Atualiza profundidade do fragmento como a coordenada z do
    // ponto de intersecao no espaco de clip normalizado de [0..1]
    gl_FragDepth = (newCoord.z + 1.0f) / 2.0f;
}

