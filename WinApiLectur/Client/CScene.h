#pragma once
// ���漱�� : �ִ��� ������ �ӵ��� ���� ���ַ���
// ���� ��� include �ϸ� ������ �Ź� ���涧���� Ȯ���ؾ��ϴ� �� �̷��� ��
// ����� ������� ���� ���ϰ� �ϴ°� ����
// ���� �̷��� �ϸ� ������Ÿ�����θ� ���ٰ�����

class CObject;

class CScene
{
private:
	vector<CObject*> vecObj;

public:
	CScene();
	~CScene();

};

