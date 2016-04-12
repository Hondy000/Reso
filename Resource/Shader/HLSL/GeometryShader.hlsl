#include "BaseShading.hlsl"

// �t�H���V�F�[�f�B���O
class SimpleNomalShading : iBaseLight
{
						  // �F���v�Z����
	float4 GetColor(PixelInputType In)
	{
		float4 Out;

		// ����	 
		// // Sample the normals from the normal render texture using the point sampler at this texture coordinate location.
		Out = normalTexture.Sample(SampleTypePoint, input.tex);
		return Out;
	}
};