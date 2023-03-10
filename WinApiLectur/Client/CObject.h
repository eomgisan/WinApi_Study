#pragma once
class CObject
{
private:
	Vec2	m_vPos;
	Vec2	m_vScale;


public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _Scale) { m_vScale = _Scale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

	virtual void update() = 0;
	virtual void render(HDC _hDc);

public:
	CObject();
	virtual ~CObject();
};

