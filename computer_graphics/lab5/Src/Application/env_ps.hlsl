
struct PS_INPUT
{
   float2 texCoord : TEXCOORD0;
   float fresnel_coef : TEXCOORD6;
   float3 refl_vector : TEXCOORD7;
};

struct PS_OUTPUT
{
   float4 color : COLOR;
};

sampler tex : register(s0);
sampler cube_tex : register(s1);

PS_OUTPUT main( PS_INPUT IN )
{
   PS_OUTPUT OUT;   
      
   float4 c1 = texCUBE(cube_tex, IN.refl_vector);
   float4 c2 = tex2D(tex, IN.texCoord);
   
   OUT.color = c1 * (1 - IN.fresnel_coef) + IN.fresnel_coef * c2;
   
   return OUT;
}
