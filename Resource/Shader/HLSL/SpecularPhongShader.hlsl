
cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};


cbuffer MaterialBuffer
{
	float4 ambient;
	float4 diffuse;
	float4 emissive;
	float4 specular;
	float power;
	float range;
	float2 dummy;
};

cbuffer CBuffer
{
	float4 g_cameraPosition;
	float4 g_LightDirection;
};

struct VertexInputType
{
	float4 position : POSITION;
	float3 normal : NORMAL;
	float2 tex : TEXCOORD0;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 worldPosition : POSITION;
};


PixelInputType VS_Main(VertexInputType input)
{
	PixelInputType output;


	input.position.w = 1.0f;

	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	output.tex = input.tex;
	output.worldPosition = mul(input.position, worldMatrix);
	output.normal = mul(input.normal, (float3x3)worldMatrix);

	output.normal = normalize(output.normal);



	return output;
}

Texture2D shaderTexture : register(t0);

SamplerState SampleTypeWrap : register(s0);






float4 PS_Main(PixelInputType input) : SV_TARGET0
{

	float3 N = normalize(input.normal.xyz);
	//ライト方向で入力されるので、頂点 -> ライト位置とするために逆向きに変換する。なおアプリケーションで必ず正規化すること
	float3 L = normalize(-float3(g_LightDirection.xyz));
	float3 V = normalize(input.worldPosition.xyz - g_cameraPosition.xyz);
	float3 R;



	//ライトベクトルと法線ベクトルの内積を計算し、計算結果の色の最低値を環境光( m_Ambient )に制限する
	//float4 diffuseColor = min( max( ambient, dot( N, L ) ) + emissive, 1.0f );
	float4 diffuseColor = ambient + diffuse * max(0.0,dot(L,N));


	//頂点 -> ライト位置ベクトル + 頂点 -> 視点ベクトル(注意１)
	float3 H = normalize(L + (V));
	R = reflect(V, N);
	R = normalize(R);


	//スペキュラーカラーを計算する(注意２)
	float4 S = pow(max(0.0f, dot(L,R)), power)*range * specular;
	S = saturate(S);
	//スペキュラーカラーを加算する
	float4 Out = diffuseColor * shaderTexture.Sample(SampleTypeWrap, input.tex) + S;

	return Out;
}



