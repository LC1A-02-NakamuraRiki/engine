#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "Mesh.h"
#include <DirectXTex.h>
#include <windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>

struct Node
{
	std::string name;
	DirectX::XMVECTOR scaling = { 1,1,1,0 };
	DirectX::XMVECTOR rotation = { 0,0,0,0 };
	DirectX::XMVECTOR translation = { 0,0,0,1 };
	DirectX::XMMATRIX transform;
	DirectX::XMMATRIX globalTransform;

	Node* parent = nullptr;
};
/// <summary>
/// モデルデータ
/// </summary>
class Model
{
public:
	friend class FbxLoader;
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

	using TexMetadata = DirectX::TexMetadata;
	using ScratchImage = DirectX::ScratchImage;

	using string = std::string;
	template <class T> using vector = std::vector<T>;


private:
	static const std::string baseDirectory;
public:
	struct VertexPosNormalUv
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 normal;
		DirectX::XMFLOAT2 uv;
	};
	private: // 静的メンバ変数
	// デバイス
	static ID3D12Device *device;
	// デスクリプタサイズ
	static UINT descriptorHandleIncrementSize;

public: // 静的メンバ関数

	/// <summary>
	/// 静的初期化
	/// </summary>
	/// <param name="device">デバイス</param>
	static void StaticInitialize(ID3D12Device *device);

	/// <summary>
	/// OBJファイルからメッシュ生成
	/// </summary>
	/// <param name="modelname">モデル名</param>
	/// <returns>生成されたモデル</returns>
	static Model *CreateFromObject(const std::string &text, bool smoothing = false);

public: // メンバ関数
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Model();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="modelname">モデル名</param>
	void Initialize(const std::string &text, bool smoothing);

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="cmdList">命令発行先コマンドリスト</param>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	void CreateBuffers(ID3D12Device* device);

	const XMMATRIX& GetModelTransform() { return meshNode->globalTransform; }
private: // メンバ変数
	// 名前
	std::string name;

	std::vector<Node> nodes;
	// メッシュコンテナ
	std::vector<Mesh *> meshes;
	// マテリアルコンテナ
	std::unordered_map<std::string, Material *> materials;
	// デフォルトマテリアル
	Material *defaultMaterial = nullptr;
	// デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeap;

	Node* meshNode = nullptr;
	
	std::vector<VertexPosNormalUv> vertices;
	
	std::vector<unsigned short> indices;

	DirectX::XMFLOAT3 ambient = { 1, 1, 1 };
	DirectX::XMFLOAT3 diffuse = { 1, 1,1 };
	DirectX::TexMetadata metadata = {};
	DirectX::ScratchImage scratchIng = {};

	ComPtr<ID3D12Resource> vertBuff;
	ComPtr<ID3D12Resource> indexBuff;
	ComPtr<ID3D12Resource> texbuff;

	D3D12_VERTEX_BUFFER_VIEW vbView = {};
	D3D12_INDEX_BUFFER_VIEW ibView = {};
	
	ComPtr<ID3D12DescriptorHeap> descHeapSRV;

private: // メンバ関数
	/// <summary>
	/// マテリアル読み込み
	/// </summary>
	void LoadMaterial(const std::string &directoryPath, const std::string &filename);

	/// <summary>
	/// マテリアル登録
	/// </summary>
	void AddMaterial(Material *material);

	/// <summary>
	/// デスクリプタヒープの生成
	/// </summary>
	void InitializeDescriptorHeap();

	/// <summary>
	/// テクスチャ読み込み
	/// </summary>
	void LoadTextures();

};