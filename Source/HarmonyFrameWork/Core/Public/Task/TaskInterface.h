#pragma once

#include "../Common.h"
#include "../BaseObject.h"

/**********************************************************************************************//**
 * @interface	IBaseTask TaskInterface.h Source\HarmonyFrame\Core\TaskInterface.h
 *
 * @brief	�^�X�N�C���^�[�t�F�[�X(�W���u�����A�N�^�[�����Q�[���I�u�W�F�N�g�ɓ�����z)
 * @brief	�ׂ����d�����s��
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

class IBaseTask
	:
	virtual public BaseObject
{
public:
	typedef DWORD PRIORITY;

protected:
	IBaseTask();
	bool m_isUsage;	// �^�X�N�L���t���O�itrue�łȂ��ƃ^�X�N�������Ȃ��Ƃ��܂��j

	PRIORITY m_priority;
public:
	friend class TaskFactory;
	friend class ActorFactory;
	virtual ~IBaseTask() {};
	virtual bool Init() = 0;
	// �X�V����
	virtual bool Update() = 0;

	// �^�X�N�̏�Ԃ����Z�b�g����
	virtual void Reset() = 0;

	// ���݂̏�Ԃ��擾����
	bool CheckUsageFlag() { return m_isUsage; }

	// �X�V�����������Ă��邩�`�F�b�N����
	virtual bool AllowUpdate() { return true; }


	// Access the Priority
	const PRIORITY& GetPriority(void) const
	{
		return(m_priority);
	};

	void SetPriority(const PRIORITY& priority)
	{
		m_priority = priority;
	};
};



// �`��֌W�^�X�N
class IDrawTask
	:
	virtual public IBaseTask
{
protected:
	IDrawTask() {};
public:
	virtual bool Draw() = 0;
	virtual ~IDrawTask() {};
};