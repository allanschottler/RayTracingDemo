#version 330
#define FLT_MAX 3.402823466e+38
#define MAX_SPHERES 16

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
/* Entrada e Saida                                                            */
/*                                                                            */
/******************************************************************************/

// Camera
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
uniform Sphere spheres[MAX_SPHERES];
uniform Plane ground;

// Cor de saída do fragmento
out vec4 fragColor;

// Profundidade normalizada do fragmento
out float fragDepth;

/******************************************************************************/
/*                                                                            */
/* Funções auxiliares                                                         */
/*                                                                            */
/******************************************************************************/

/*
 * Retorna o olho da camera corrente
 * 
 * out [return] Olho da camera no mundo
 */
vec3 camera_eye()
{
    //return inverse(view)[3].xyz;
    return vec3(0);
}

/*
 * Converte ponto descrito localmente para coordenadas de mundo
 * 
 * in localPoint Ponto descrito localmente
 * out [return] Ponto em coordenada de mundo
 */
vec4 to_world(vec3 localPoint)
{    
    return model * vec4(localPoint, 1);
}

/*
 * Converte ponto descrito localmente para coordenadas de camera
 * 
 * in localPoint Ponto descrito localmente
 * out [return] Ponto em coordenada de camera
 */
vec4 to_camera(vec3 localPoint)
{    
    return view * model * vec4(localPoint, 1);
}

/*
 * Converte ponto descrito localmente para coordenadas de tela
 * 
 * in localPoint Ponto descrito localmente
 * out [return] Ponto em coordenada de tela
 */
vec4 to_screen(vec3 localPoint)
{
    return projection * view * model * vec4(localPoint, 1);
}

/*
 * Converte ponto descrito localmente para coordenadas normalizadas (NDC)
 * 
 * in localPoint Ponto descrito localmente
 * out [return] Ponto em NDC
 */
vec3 to_ndc(vec3 localPoint)
{
    vec4 screenSpace = to_screen(localPoint);
    return screenSpace.xyz/screenSpace.w;
}

/*
 * Retorna o raio tracado por este fragmento
 * 
 * out [return] Raio tracado
 */
Ray getCurrentRay()
{
    // Normaliza frag coord para ir de -viewport/2 até +viewport/2
    vec2 normalizedFragCoord = 2.0 * gl_FragCoord.xy / viewport - 1.0;

    // Fragmento unprojected (mundo) no plano near
    vec4 fragmentNear = vec4(nearCenter + 
        nearRight * normalizedFragCoord.x + 
        nearUp * normalizedFragCoord.y, 1);
        
    // Fragmento unprojected (mundo) no plano far
    vec4 fragmentFar = vec4(farCenter + 
        farRight * normalizedFragCoord.x + 
        farUp * normalizedFragCoord.y, 1);      
    
    // Retorna raio que vai de near a far
    Ray ray;
    ray.orig = fragmentNear.xyz;    
    ray.dir  = normalize((fragmentFar - fragmentNear).xyz);
    
    return ray;
}

/*
 * Soluciona uma equacao de segundo grau usando o metodo de Bhaskara.
 * Recebe como entrada os 3 coeficientes A, B e C da equacao de forma:
 *      
 *      Ax^2 + Bx + C = 0
 * 
 * e retorna true caso seja solucionavel. Se existirem 2 solucoes, t0 e t1 
 * retornam com solucoes distintas, caso contrario (apenas 1 solucao), 
 * t0 e t1 contem a mesma solucao. t0 sempre retorna com valor menor ou igual a t1.
 * 
 * in a, b, c Coeficiente da equacao de segundo grau
 * out t0, t1 Solucoes da equacao
 * out [return] true se houver solucao
 */
bool solve_bhaskara(
    in float a, in float b, in float c, 
    out float t0, out float t1)
{
    float delta = b*b - 4*a*c;
    
    // Nao existe solucao
    if(delta < 0)
        return false;
        
    // Apenas uma solucao
    if(delta == 0)
    {
        t0 = t1 = -b / (2*a);
        return true;
    }
        
    // Duas solucoes
    t0 = (-b + sqrt(delta)) / (2*a);
    t1 = (-b - sqrt(delta)) / (2*a);
    
    // Swap para t0 ser menor que t1
    if(t1 < t0)
    {
        float temp = t1;
        t1 = t0;
        t0 = temp;
    }
    
    return true;
}    

/******************************************************************************/
/*                                                                            */
/* Funcoes para implementar                                                   */
/*                                                                            */
/******************************************************************************/

/*
 * Retorna a cor em um dado ponto de uma superficie
 * 
 * in point Ponto da superficie no mundo
 * in normal Normal associada ao ponto
 * out [return] Cor RGBA
 */
vec4 phong(in vec3 point, in vec3 normal)
{
    vec3 lightPos = to_camera(light.position).xyz;
    vec3 L = normalize(lightPos - point);
    vec3 r = normalize(reflect(-L, normal));
    vec3 eye = camera_eye();
    vec3 v = normalize(eye - point);
    
    vec4 cA = material.diffuseColor * 0.33f;
    vec4 cD = max(dot(L, normal), 0.f) * material.diffuseColor;
    cD = clamp(cD, 0.f, 1.f);
    vec4 cS;
    if(max(dot(L, normal), 0.f) > 0.f)
        cS = pow(max(dot(r, v), 0.f), material.shininess) * light.color;
    cS = clamp(cS, 0.f, 1.f);
    
    return cA + cD + cS;
}

/*
 * Intercepta um raio com uma esfera e retorna o ponto de intersecao
 * e a normal associada.
 * 
 * in ray Raio tracado
 * in sphere Esfera a ser testada contra raio
 * out intersection Ponto de intersecao na esfera
 * out normal Normal associada ao ponto
 * out [return] true se raio intercepta esfera
 */
bool intersectRaySphere(
    in Ray ray, in Sphere sphere, 
    out float t, out vec3 normal)
{
    vec3 worldCenter = to_camera(sphere.center).xyz;
    vec3 center2orig = ray.orig - worldCenter;
    
    float a = 1;
    float b = 2.0f * dot(center2orig, ray.dir);
    float c = dot(center2orig, center2orig) - sphere.radius * sphere.radius;
        
    float t0 = FLT_MAX, t1 = FLT_MAX;
    if(!solve_bhaskara(a, b, c, t0, t1))
        return false;
    
    // Apenas interceptou na direcao negativa
    if(t1 < 0)
        return false;
    
    t = t0 < 0 ? t1 : t0;
    vec3 intersection = ray.orig + t * ray.dir;
    normal = normalize(intersection - worldCenter.xyz);
    
    return true;
}
 
/*
 * Funcao principal
 * 
 * out fragColor Cor final do fragmento
 * out fragDepth Profundidade normalizada do fragmento
 */
void main(void)
{
    int pickedObj = -1;
    float pickedT = FLT_MAX;
    vec3 pickedNormal;
    Ray ray = getCurrentRay();
    
    // Testa intersecao com objetos
    float time = 0;
    vec3 normal;
    
    // Testa intersecao com esferas
    for(int iSphere = 0; iSphere < MAX_SPHERES; iSphere++)
    {
        if(intersectRaySphere(ray, spheres[iSphere], time, normal))
        {
            if(time < pickedT)
            {
                pickedT = time;
                pickedObj = iSphere;
                pickedNormal = normal;
            }
        }
    }
    
    // Se acertou nenhuma esfera
    if(pickedObj == -1)
    {
        discard;
        return;
    }
    
    // Calcula ponto de intersecao
    vec3 intersection = ray.orig + pickedT * ray.dir;
    
    // Aplica iluminacao
    fragColor = phong(intersection, pickedNormal);
   

    // Atualiza profundidade do fragmento como a coordenada z do
    // ponto de intersecao no espaco de clip normalizado de [0..1]
    fragDepth = (to_ndc(intersection).z + 1.0f) / 2.0f;;
}

