
float4 eyepos;
float fresnel_pow;
float4x4 mvp, m, inv_trans_m; 

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
      
   float4 p = mul(IN.position, m);
   
   //Vector from camera to position
   float3 v = float3(eyepos.xyz) - float3(p.xyz);  
   
   //Transofrmed normal   
   float3 n = mul(IN.normal, inv_trans_m);   

   //Fresnel coef for mixing texture colors: 1 / (1 + cos(i))^8
   OUT.fresnel_coef = clamp(pow(1 + dot(normalize(n), normalize(v)), fresnel_pow), 0.1, 0.9);   
   
   //Calculating reflection vector
   OUT.refl_vector = reflect(v, n);
      
   //Passing parameters to PS
   OUT.texCoord = IN.texCoord;
   OUT.position = mul(IN.position, mvp);
  
   return OUT;	
}
