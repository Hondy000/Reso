#include "HFMath.h"



inline HFVECTOR4 XM_CALLCONV HFLoadFloat2
(
	const HFVECTOR2* pSource
)
{
	assert(pSource);
	HFVECTOR4 V;
	V.vector4_f32[0] = pSource->x;
	V.vector4_f32[1] = pSource->y;
	V.vector4_f32[2] = 0.f;
	V.vector4_f32[3] = 0.f;
	return V;
	float32x2_t x = vld1_f32(reinterpret_cast<const float*>(pSource));
	float32x2_t zero = vdup_n_f32(0);
	return vcombine_f32(x, zero);
#elif defined(_XM_SSE_INTRINSICS_)
	__m128 x = _mm_load_ss(&pSource->x);
	__m128 y = _mm_load_ss(&pSource->y);
	return _mm_unpacklo_ps(x, y);
#endif
}