//
//Effect.h
//
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "billboard.h"

class CEffect : public CBillboard
{
public:
	enum EType
	{
		EFFECT_NONE = 0,
		EFFECT_DEFAULT,
		EFFECT_MAX
	};

	CEffect();
	~CEffect() override;

	static CEffect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int life, EType type);

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetLife(int life) { m_life = life; }
	void SetType(EType type) { m_type = type; }

	int GetLife() { return m_life; }
	EType GetType() { return m_type; }

private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_scale;
	D3DXCOLOR m_col;
	EType m_type;
	int m_life;
};

#endif