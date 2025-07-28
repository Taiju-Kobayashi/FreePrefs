#include "freePrefs.h"


namespace FreePrefsLib 
{

	std::string Literate::m_filepath{};
	std::unordered_map<std::string, int> Literate::m_IntMap{};
	std::unordered_map<std::string, float>Literate::m_floatMap{};
	std::unordered_map<std::string, std::string>Literate::m_StringMap{};


	void Literate::Init(const char* path) {
		m_filepath = path; //�t�@�C���p�X��ݒ�
		FILE* file = nullptr;
		fopen_s(&file,m_filepath.c_str(), "rb");
		if (file == nullptr) {
			//�t�@�C�������݂��Ȃ��ꍇ�͏��������s��
			PrefsSave(); //��̏�Ԃŕۑ�
			return;
		}
		int i, f, s;
		fread(&i, sizeof(int), 1, file);
		fread(&f, sizeof(int), 1, file);
		fread(&s, sizeof(int), 1, file);

		std::string key;
		for (int count = 0; count < i; count++)
		{
			int data;
			fread(&key, sizeof(std::string), 1, file);
			fread(&data, sizeof(int), 1, file);
			m_IntMap[key] = data;
		}
		for (int count = 0; count < f; count++)
		{
			float data;
			fread(&key, sizeof(std::string), 1, file);
			fread(&data, sizeof(float), 1, file);
			m_floatMap[key] = data;
		}
		for (int count = 0; count < s; count++)
		{
			std::string data;
			fread(&key, sizeof(std::string), 1, file);
			fread(&data, sizeof(std::string), 1, file);
			m_StringMap[key] = data;
		}
		fclose(file);
	}

	void Literate::Uninit() {
		PrefsSave(); //�I�����Ƀf�[�^��ۑ�����
		DeleteAll(); //�S�Ẵf�[�^���폜����
	}



	bool  Literate::PrefsSave() {
		FILE* file = nullptr;
		fopen_s(&file, m_filepath.c_str(), "wb");

		//�ǂݍ��ݎ����l�����āA�f�[�^�̃T�C�Y���ŏ��ɏ�������
		int i, f, s;
		i = m_IntMap.size();
		f = m_floatMap.size();
		s = m_StringMap.size();
		fwrite(&i, sizeof(int), 1, file);
		fwrite(&f, sizeof(int), 1, file);
		fwrite(&s, sizeof(int), 1, file);

		for (auto& pair : m_IntMap)
		{
			fwrite(pair.first.c_str(), sizeof(std::string), 1, file);
			fwrite(&pair.second, sizeof(int), 1, file);
		}
		for (auto& pair : m_floatMap)
		{
			fwrite(pair.first.c_str(), sizeof(std::string), 1, file);
			fwrite(&pair.second, sizeof(float), 1, file);
		}
		for (auto& pair : m_StringMap)
		{
			fwrite(pair.first.c_str(), sizeof(std::string), 1, file);
			fwrite(pair.second.c_str(), sizeof(std::string), 1, file);
		}
		fclose(file);
		return true;
	}

	bool  Literate::HasKey(std::string key) {
		unsigned int ch = 0;
		try
		{
			auto l_int = m_IntMap.at(key);
		}
		catch (const std::out_of_range&)
		{
			ch += 1; //�L�[�����݂��Ȃ��ꍇ��1�����Z
		}
		try
		{
			auto l_float = m_floatMap.at(key);
		}
		catch (const std::out_of_range&)
		{
			ch += 1; //�L�[�����݂��Ȃ��ꍇ��1�����Z
		}
		try
		{
			auto l_string = m_StringMap.at(key);
		}
		catch (const std::out_of_range&)
		{
			ch += 1; //�L�[�����݂��Ȃ��ꍇ��1�����Z
		}

		if (ch >= 3) { //�S�Ẵ}�b�v�ŃL�[�����݂��Ȃ��ꍇ
			return false; //�L�[�����݂��Ȃ��ꍇ��false��Ԃ�
		}

		return true; //�L�[�����݂���ꍇ��true��Ԃ�
	}

	void  Literate::DeleteAll() {
		m_IntMap.clear();
		m_floatMap.clear();
		m_StringMap.clear();
	}

	void  Literate::DeleteKey(std::string key) {
		m_IntMap.erase(key);
		m_floatMap.erase(key);
		m_StringMap.erase(key);
	}

	void  Literate::SetInt(std::string key, int value) {
		try
		{
			m_IntMap.at(key) = value;
		}
		catch (const std::out_of_range&)
		{
			m_IntMap[key] = value;
		}
	}
	int  Literate::GetInt(std::string key) {
		int value;
		try
		{
			value = m_IntMap.at(key);
		}
		catch (const std::out_of_range&)
		{
			return 0; //�L�[�����݂��Ȃ��ꍇ��0��Ԃ�
		}
		return value; //�L�[�����݂���ꍇ�͂��̒l��Ԃ�
	}

	void  Literate::SetFloat(std::string key, float value) {
		try
		{
			m_floatMap.at(key) = value;
		}
		catch (const std::out_of_range&)
		{
			m_floatMap[key] = value;
		}
	}

	float  Literate::GetFloat(std::string key) {
		float value;
		try
		{
			value = m_floatMap.at(key);
		}
		catch (const std::out_of_range&)
		{
			return 0.0f; //�L�[�����݂��Ȃ��ꍇ��0��Ԃ�
		}
		return value; //�L�[�����݂���ꍇ�͂��̒l��Ԃ�
	}

	void  Literate::SetString(std::string key, std::string value) {
		try
		{
			m_StringMap.at(key) = value;
		}
		catch (const std::out_of_range&)
		{
			m_StringMap[key] = value;
		}
	}

	std::string  Literate::GetString(std::string key) {
		std::string value;
		try
		{
			value = m_floatMap.at(key);
		}
		catch (const std::out_of_range&)
		{
			return ""; //�L�[�����݂��Ȃ��ꍇ�͋󕶎����Ԃ�
		}
		return value; //�L�[�����݂���ꍇ�͂��̒l��Ԃ�
	}
}