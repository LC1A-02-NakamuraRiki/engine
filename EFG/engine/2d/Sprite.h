#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>

class Sprite
{
private: // �G�C���A�X
// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: // �T�u�N���X

	struct ConstBufferData
	{
		XMFLOAT4 color;    //�F(RGBA)
		XMMATRIX mat;      //3D�ϊ��s��
		bool flag;
		bool pad;
		bool effectFlag;
		float alpha;
		XMFLOAT4 alartColor;
	};

	struct VertexPosUv
	{
		XMFLOAT3 pos;
		XMFLOAT2 uv;
	};
public: // �ÓI�����o�֐�
	
		//�ÓI������
	static bool StaticInitialize(ID3D12Device *device, int window_width, int window_height);

	//�e�N�X�`���ǂݍ���
	static bool LoadTexture(UINT texnumber, const wchar_t *filename);

	//�`��O����
	static void PreDraw(ID3D12GraphicsCommandList *cmdList);

	//�`��㏈��
	static void PostDraw();

	//�X�v���C�g����
	static Sprite *Create(UINT texNumber, XMFLOAT2 position, XMFLOAT4 color = { 1, 1, 1, 1 }, XMFLOAT2 anchorpoint = { 0.0f, 0.0f }, bool isFlipX = false, bool isFlipY = false);

protected: // �ÓI�����o�ϐ�
	// �e�N�X�`���̍ő喇��
	static const int srvCount = 512;
	
	// ���_��
	static const int vertNum = 4;
	
	// �f�o�C�X
	static ID3D12Device *device;
	
	// �f�X�N���v�^�T�C�Y
	static UINT descriptorHandleIncrementSize;
	
	// �R�}���h���X�g
	static ID3D12GraphicsCommandList *cmdList;
	
	// ���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature> rootSignature;
	
	// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static ComPtr<ID3D12PipelineState> pipelineState;
	
	// �ˉe�s��
	static XMMATRIX matProjection;
	
	// �f�X�N���v�^�q�[�v
	static ComPtr<ID3D12DescriptorHeap> descHeap;
	
	// �e�N�X�`���o�b�t�@
	static ComPtr<ID3D12Resource> texBuff[srvCount];

public: // �����o�֐�
	//�R���X�g���N�^
	Sprite(UINT texNumber, XMFLOAT2 position, XMFLOAT2 size, XMFLOAT4 color, XMFLOAT2 anchorpoint, bool isFlipX, bool isFlipY);

	//������
	bool Initialize();

	//�p�x�̐ݒ�
	void SetRotation(float rotation);

	//���W�̐ݒ�
	void SetPosition(XMFLOAT2 position);
	XMFLOAT2 GetPosition() { return position; };

	//�T�C�Y�̐ݒ�
	void SetSize(XMFLOAT2 size);

	//�A���J�[�|�C���g�̐ݒ�
	void SetAnchorPoint(XMFLOAT2 anchorpoint);

	//���E���]�̐ݒ�
	void SetIsFlipX(bool isFlipX);

	//�㉺���]�̐ݒ�
	void SetIsFlipY(bool isFlipY);

	//�e�N�X�`���͈͐ݒ�
	void SetTextureRect(XMFLOAT2 texBase, XMFLOAT2 texSize);

	//�`��
	void Draw(float alpha);

protected: // �����o�ϐ�
	// ���_�o�b�t�@
		ComPtr<ID3D12Resource> vertBuff;

		// �萔�o�b�t�@
		ComPtr<ID3D12Resource> constBuff;

		// ���_�o�b�t�@�r���[
		D3D12_VERTEX_BUFFER_VIEW vbView{};

		// �e�N�X�`���ԍ�
		UINT texNumber = 0;

		// Z�����̉�]�p
		float rotation = 0.0f;

		// ���W
		XMFLOAT2 position{};

		// �X�v���C�g���A����
		XMFLOAT2 size = { 100.0f, 100.0f };

		// �A���J�[�|�C���g
		XMFLOAT2 anchorpoint = { 0, 0 };

		// ���[���h�s��
		XMMATRIX matWorld{};

		// �F
		XMFLOAT4 color = { 1, 1, 1, 1 };

		// ���E���]
		bool isFlipX = false;

		// �㉺���]
		bool isFlipY = false;

		// �e�N�X�`���n�_
		XMFLOAT2 texBase = { 0, 0 };

		// �e�N�X�`�����A����
		XMFLOAT2 texSize = { 100.0f, 100.0f };

private: // �����o�֐�
	/// <summary>
	/// ���_�f�[�^�]��
	/// </summary>
	void TransferVertices();
};