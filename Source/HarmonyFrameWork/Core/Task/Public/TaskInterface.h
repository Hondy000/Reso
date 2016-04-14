#pragma once
#include "../../Public/IBaseObject.h"
#include "../../Public/VariableManager.h"


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
	virtual public IBaseObject
{
public:
	typedef unsigned long PRIORITY;


protected:
	IBaseTask()
		:
		m_isUsage(true),m_isDestroy(false)
	{
	};
	BOOL m_isUsage;	// �^�X�N�L���t���O�itrue�łȂ��ƃ^�X�N�������Ȃ��Ƃ��܂��j
	BOOL m_isDestroy;	// �����t���O
	PRIORITY m_updatePriority;
	unsigned long m_taskId;
	std::string m_name;
	std::unordered_map<std::string, std::shared_ptr<IVariable>> m_varMap;
public:

	friend class TaskFactory;
	friend class ActorFactory;
	virtual ~IBaseTask() {}

	BOOL Init();
	// �X�V����
	virtual BOOL Update() = 0;

	// �^�X�N�̏�Ԃ����Z�b�g����
	virtual void Reset() = 0;

	virtual BOOL LoadTaskData(const std::string& path);

	// ���݂̏�Ԃ��擾����
	BOOL CheckUsageFlag() { return m_isUsage; }

	BOOL CheckDestroy() { return m_isDestroy; }


	// �X�V�����������Ă��邩�`�F�b�N����
	virtual BOOL AllowUpdate() { return true; } 

	// Access the Priority
	const PRIORITY& GetUpdatePriority(void) const
	{
		return(m_updatePriority);
	};

	void SetUpdatePriority(const PRIORITY& priority)
	{
		m_updatePriority = priority;
	};


	// Access the TaskId
	const unsigned long& GetTaskId(void) const
	{
		return(m_taskId);
	};
	void SetTaskId(const unsigned long& taskId)
	{
		m_taskId = taskId;
	};

	const std::string& GetTaskName(void)const
	{
		return m_name;
	};

	void SetTaskName(const std::string& name)
	{
		m_name = name;
	};

	template<typename T>
	std::shared_ptr<Variable<T>> GetVariable(const std::string& variableName)
	{				  
		return VariableManagersManager::GetInstance()->GetVariable<T>(m_globalID, variableName);
	};

	std::shared_ptr<IVariable> GetVariable(const std::string& variableName)
	{
		auto res = m_varMap.find(variableName);
		if (res != m_varMap.end())
		{
			return res->second;
		}
		return nullptr;
	};
	public:
	template <typename T>
	BOOL RegisterVariable(const std::string& variableName, std::shared_ptr<Variable<T>> variable)
	{

		std::pair<std::string, std::shared_ptr<IVariable>> key;
		key.first = variableName;
		key.second = variable;
		auto res = m_varMap.insert(key);
		if(res.second)
		{
			if (VariableManagersManager::GetInstance()->RegsigterVariable<T>(this->m_globalID, variableName, variable))
			{
				return true;
			}
		}
		return false;
	};

	template <typename T>
	BOOL RegisterVariable(const std::string& variableName, std::shared_ptr<T> constant)
	{
		std::shared_ptr<Variable<T>> wrapVar = std::make_shared<Variable<T>>();

		wrapVar->SetValue(constant);   
		std::pair<std::string, std::shared_ptr<IVariable>> key;
		key.first = variableName;
		key.second = wrapVar;
		auto res = m_varMap.insert(key);
		if (res.second)
		{
			if (VariableManagersManager::GetInstance()->RegsigterVariable<T>(this->m_globalID, variableName, wrapVar))
			{
				return true;
			}
		}
	};

	template <typename T>
	BOOL RegisterVariable(const std::string& variableName, T variable)
	{
		std::shared_ptr<Variable<T>> wrapVar = std::make_shared<Variable<T>>();

		std::shared_ptr<T> constant = make_shared<T>();
		*constant = variable;
		wrapVar->SetValue(constant);
		std::pair<std::string, std::shared_ptr<IVariable>> key;
		key.first = variableName;
		key.second = wrapVar;
		auto res = m_varMap.insert(key);
		if (res.second)
		{
			if (VariableManagersManager::GetInstance()->RegsigterVariable<T>(this->m_globalID, variableName, wrapVar))
			{
				return true;
			}
		}
	};
	BOOL CreateVariable(const std::string& variableName,std::string typeName)
	{
		return VariableManagersManager::GetInstance()->CreateVariable(this->m_globalID, variableName, typeName);
	}

};



// �`��֌W�^�X�N
class IDrawTask
	:
	virtual public IBaseTask
{

protected:
	IDrawTask() {};
	PRIORITY m_drawPriority;
public:
	virtual BOOL Draw() = 0;
	virtual ~IDrawTask() {};
	// Access the DrawPriority
	const PRIORITY& GetDrawPriority(void) const
	{
		return(m_drawPriority);
	};
	void SetDrawPriority(const PRIORITY& drawPriority)
	{
		m_drawPriority = drawPriority;
	};
};