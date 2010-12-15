float4x4 mvp, mv; 
float4 eyepos;
float fresnel_pow;

struct VS_INPUT
{
   float4 position : POSITION0;
   float3 normal : NORMAL0;	
   float2 texCoord : TEXCOORD0;
};

struct VS_OUTPUT
{
   float4 position : POSITION0;      
   float2 texCoord : TEXCOORD0;
   
   //I really do not know the other way to pass sth to PS :(
   float fresnel_coef : TEXCOORD6;
   float3 refl_vector : TEXCOORD7;
};

VS_OUTPUT main( VS_INPUT IN ) 
{
   VS_OUTPUT OUT;
      
   float3 tangent = -float3(abs(IN.normal.y) + abs(IN.normal.z), abs(IN.normal.x), 0); 
   float3 binormal = cross(tangent, IN.normal); 
   float3x3 normalMatrix = float3x3(tangent, binormal, IN.normal); 

   float3 p = mul(IN.position, mv);   
   float3 v = normalize(float3(eyepos.x, eyepos.y, eyepos.z) - p);  
   float3 n = normalize(mul(IN.normal, (float3x3)normalMatrix));   

   OUT.fresnel_coef = clamp(pow(1 + dot(normalize(n), normalize(v)), fresnel_pow), 0.1, 0.9);   
   OUT.refl_vector = reflect(v, n);
   OUT.texCoord = IN.texCoord;
   OUT.position = mul(IN.position, mvp);
  
   return OUT;	
}
