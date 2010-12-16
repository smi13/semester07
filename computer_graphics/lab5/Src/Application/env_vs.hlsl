float4x4 mvp, mv; 
float4 eyepos;
float fresnel_pow;

struct VS_INPUT
{
   float4 position : POSITION;
   float3 normal : NORMAL;	
   float2 texCoord : TEXCOORD;
};

struct VS_OUTPUT
{
   float4 position : POSITION;      
   float2 texCoord : TEXCOORD0;
   
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
   
   //Vector from camera to position
   float3 v = float3(eyepos.x, eyepos.y, eyepos.z) - p;  
   
   //Rransofrmed normal
   float3 n = mul(IN.normal, (float3x3)normalMatrix);   

   //Fresnel coef for mixing texture colors: 1 / (1 + cos(i))^8
   OUT.fresnel_coef = clamp(pow(1 + dot(normalize(n), normalize(v)), fresnel_pow), 0.1, 0.9);   
   
   //Calculating reflection vector
   OUT.refl_vector = reflect(v, n);
   
   //Passing parameters to PS
   OUT.texCoord = IN.texCoord;
   OUT.position = mul(IN.position, mvp);
  
   return OUT;	
}
