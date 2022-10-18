//����������������������������������������
//model.h
//����������������������������������������
#ifndef _MODEL_H_	//���̃}�N����`������ĂȂ�������
#define _MODEL_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

#include <d3d9.h>
#include <d3dx9.h>

class CModel
{
public:
	enum EModel
	{
		MODEL_FOKKO = 0,
		MODEL_STAR,
		MODEL_MAX,
		MODEL_NONE
	};

	struct ModelData
	{
		LPD3DXBUFFER m_buffMat;
		DWORD m_dwNum;
		LPD3DXMESH m_mesh;
	};

	static const char* s_FileName[];	// �t�@�C���p�X

public:
	CModel();		// �f�t�H���g�R���X�g���N�^
	~CModel();	// �f�X�g���N�^

public: /* �����o�֐� */
	void LoadAll();										// �S�Ă̓ǂݍ���
	void Load(EModel Model);							// �w��̓ǂݍ���
	void ReleaseAll();									// �S�Ă̔j��
	void Release(EModel Model);							// �w��̔j��
	ModelData GetModel(EModel Model);					// ���̎擾

private: /* �����o�ϐ� */
	ModelData m_model[MODEL_MAX];
};

#endif // !_TEXTURE_H_
