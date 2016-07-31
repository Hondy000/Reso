#include "BaseShading.hlsl"

// フォンシェーディング
class SimpleNomalShading : iBaseLight
{
						  // 色を計算する
	float4 GetColor(PixelInputType In)
	{
		float4 Out;

		// 合成	 
		// // Sample the normals from the normal render texture using the point sampler at this texture coordinate location.
		Out = normalTexture.Sample(SampleTypePoint, input.tex);
		return Out;
	}
};