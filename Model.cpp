#include "Model.h"

#include<vector>
#include<fstream>
#include<sstream>
#include<string>

using namespace DirectX;
using namespace std;

 const float Model::radius = 5.0f;
 const float Model::prizmHeight = 8.0f;

 void Model::PointVertex()
 {
	 vertices.resize(1);
	 indices.resize(1);

	 vertices[0].pos = XMFLOAT3(0, 0, 0);

	 vertices[0].normal = { 0,0,-1 };

	 vertices[0].uv = { 0,0 };

	 indices[0] = 0;
 }
 void Model::LoadModel(const std::string& failename, bool smoothing)
 {
	 const string filename = failename + ".obj";
	 const string directoryPath = "Resources/";

	 // ファイルストリーム
	 std::ifstream file;
	 // .objファイルを開く
	 file.open(directoryPath + filename);
	 // ファイルオープン失敗をチェック
	 if (file.fail()) {
		 assert(0);
	 }
	 vector<XMFLOAT3> positions;	// 頂点座標
	 vector<XMFLOAT3> normals;	// 法線ベクトル
	 vector<XMFLOAT2> texcoords;	// テクスチャUV
	 // 1行ずつ読み込む
	 string line;
	 while (getline(file, line)) {

		 // 1行分の文字列をストリームに変換して解析しやすくする
		 std::istringstream line_stream(line);

		 // 半角スペース区切りで行の先頭文字列を取得
		 string key;
		 getline(line_stream, key, ' ');

		 // 先頭文字列がvなら頂点座標
		 if (key == "v") {
			 // X,Y,Z座標読み込み
			 XMFLOAT3 position{};
			 line_stream >> position.x;
			 line_stream >> position.y;
			 line_stream >> position.z;
			 positions.emplace_back(position);
		 }
		
		 // 先頭文字列がfならポリゴン（三角形）
		 if (key == "f")
		 {
			 int faceIndexCount = 0;
			 // 半角スペース区切りで行の続きを読み込む
			 string index_string;
			 while (getline(line_stream, index_string, ' ')) {
				 // 頂点インデックス1個分の文字列をストリームに変換して解析しやすくする
				 std::istringstream index_stream(index_string);
				 unsigned short indexPosition, indexNormal, indexTexcoord;
				 // 頂点番号
				 index_stream >> indexPosition;
				 index_stream.seekg(1, ios_base::cur);
				 index_stream >> indexTexcoord;
				 index_stream.seekg(1, ios_base::cur);
				 index_stream >> indexNormal;

				 //頂点データに追加
				Vertex vertex{};
				vertex.pos = positions[indexPosition-1];
				vertex.normal = normals[indexNormal -1];
				vertex.uv = texcoords[indexTexcoord -1];
				vertices.emplace_back(vertex);
				 //頂点インデックスに追加
				 indices.emplace_back((unsigned short)indices.size());
			 }
		 }
		 //先頭文字列がvtならテクスチャ
		 if (key == "vt") {
		 //U,V成分読み込み
			 XMFLOAT2 texcoord{};
			 line_stream >> texcoord.x;
			 line_stream >> texcoord.y;
			 //V方向反転
			 texcoord.y = 1.0f - texcoord.y;
			 //テクスチャ座標データに追加
			 texcoords.emplace_back(texcoord);
		 }
		 //先頭文字列がvnなら法線ベクトル
		 if (key == "vn") {
			 //X,Y,Z成分読み込み
			 XMFLOAT3 normal{};
			 line_stream >> normal.x;
			 line_stream >> normal.y;
			 line_stream >> normal.z;
			 //テクスチャ座標データに追加
			 normals.emplace_back(normal);
		 }
	 }
	 file.close();
 }

 void Model::LoadTriangle(Vector3 pos1, Vector3 pos2, Vector3 pos3)
 {
	 vertices.resize(3);
	 indices.resize(3);

	 vertices[0].pos = XMFLOAT3(pos1.x, pos1.y, pos1.z);
	 vertices[1].pos = XMFLOAT3(pos2.x, pos2.y, pos2.z);
	 vertices[2].pos = XMFLOAT3(pos3.x, pos3.y, pos3.z);;

	 vertices[0].normal = { 0,0,-1 };
	 vertices[1].normal = { 0,0,-1 };
	 vertices[2].normal = { 0,0,-1 };

	 vertices[0].uv = { 0,0 };
	 vertices[1].uv = { 0,0 };
	 vertices[2].uv = { 0,0 };

	 indices[0] = 0;
	 indices[1] = 1;
	 indices[2] = 2;
 }

 void Model::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNumber)
{
	this->textureManager = textureManager;
	this->texNumber = texNumber;

	HRESULT result = S_FALSE;
	
	//法線方向の計算

	for (int i = 0; i <	(UINT)indices.size()/3; i++)
	{
		//三角形1つずつ計算していく
		//三角形のインデックスを取得
		unsigned short index0 = indices[i * 3 + 0];
		unsigned short index1 = indices[i * 3 + 1];
		unsigned short index2 = indices[i * 3 + 2];
		//三角形を構成する頂点座標をベクトルに代入
		XMVECTOR p0 = XMLoadFloat3(&vertices[index0].pos);
		XMVECTOR p1 = XMLoadFloat3(&vertices[index1].pos);
		XMVECTOR p2 = XMLoadFloat3(&vertices[index2].pos);
		//p0→p1ベクトル、p0→p2ベクトルを計算
		XMVECTOR v1 = XMVectorSubtract(p1, p0);
		XMVECTOR v2 = XMVectorSubtract(p2, p0);
		//外積は両方から垂直なベクトル
		XMVECTOR normal = XMVector3Cross(v1, v2);
		//正規化
		normal = XMVector3Normalize(normal);
		//求めた法線を頂点データに代入
		XMStoreFloat3(&vertices[index0].normal, normal);
		XMStoreFloat3(&vertices[index1].normal, normal);
		XMStoreFloat3(&vertices[index2].normal, normal);
	}

	UINT sizeVB = static_cast<UINT>(sizeof(Vertex) * vertices.size());
	UINT sizeIB = static_cast<UINT>(sizeof(unsigned short) * indices.size());

	//頂点バッファ生成
	result = dxCommon->GetDevice()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeVB),
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&vertBuff));
	if (FAILED(result)) {
		assert(0);
	}
	//インデックスバッファ生成
	result = dxCommon->GetDevice()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeIB),
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&indexBuff));
	if (FAILED(result)) {
		assert(0);
	}
	//バッファへのデータ転送
	Vertex* vertMap = nullptr;
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	std::copy(vertices.begin(), vertices.end(), vertMap);

	vertBuff->Unmap(0, nullptr);

	//GPU上のバッファに対応した仮想メモリを取得
	unsigned short* indexMap = nullptr;
	result = indexBuff->Map(0, nullptr, (void**)&indexMap);

	//全インデックスに対して
	std::copy(indices.begin(), indices.end(), indexMap);

	indexBuff->Unmap(0, nullptr);

	//頂点バッファビューの作成
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	vbView.SizeInBytes = sizeVB;
	vbView.StrideInBytes = sizeof(vertices[0]);

	//インデックスバッファビューの作成
	ibView.BufferLocation = indexBuff->GetGPUVirtualAddress();
	ibView.Format = DXGI_FORMAT_R16_UINT;
	ibView.SizeInBytes = sizeIB;

}

void Model::Draw(ID3D12GraphicsCommandList* cmdList)
{
	//頂点バッファの設定
	cmdList->IASetVertexBuffers(0, 1, &vbView);
	//インデックスバッファのセットコマンド
	cmdList->IASetIndexBuffer(&ibView);
	//デスクリプタヒープの配列
	textureManager->SetDescripterHeaps(cmdList);
	//シェーダリソースビューをセット
	textureManager->SetShaderResourceView(cmdList, 1, texNumber);
	// 描画コマンド
	cmdList->DrawIndexedInstanced((UINT)indices.size(), 1, 0, 0, 0);

}
void Model::Draw(ID3D12GraphicsCommandList* cmdList, int instanceIndex)
{
	//頂点バッファの設定
	cmdList->IASetVertexBuffers(0, 1, &vbView);
	//インデックスバッファのセットコマンド
	cmdList->IASetIndexBuffer(&ibView);
	//デスクリプタヒープの配列
	textureManager->SetDescripterHeaps(cmdList);
	//シェーダリソースビューをセット
	textureManager->SetShaderResourceView(cmdList, 1, texNumber);
	// 描画コマンド
	cmdList->DrawIndexedInstanced((UINT)indices.size(), instanceIndex, 0, 0, 0);

}