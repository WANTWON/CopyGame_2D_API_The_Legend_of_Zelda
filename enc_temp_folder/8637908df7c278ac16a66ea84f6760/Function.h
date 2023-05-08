#pragma once

template<typename T> 
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

template<typename T>
void Safe_Delete_Array(T& Temp)
{
	if (Temp)
	{
		delete[] Temp;
		Temp = nullptr;
	}
}

class CDeleteObj
{
public:
	template<typename T>
	void  operator()(T& temp)
	{
		if (temp)
		{
			delete temp;
			temp = nullptr;
		}
	}
};

class CDeleteMap
{
public:
	template<typename T>
	void operator()(T& Pair)
	{
		if (Pair.second)
		{
			delete Pair.second;
			Pair.second = nullptr;
		}
	}
};

class CTag_Finder
{
private:
	const TCHAR*		m_pTag;

public:
	CTag_Finder(const TCHAR* pTag) : m_pTag(pTag) {}

public:
	template<typename T>
	bool	operator()(T& Pair)
	{
		if (!lstrcmp(m_pTag, Pair.first))
			return true;

		return false;
	}

};

template<typename T>
bool		CompareY(T Dest, T Sour)
{
	return Dest->Get_Info().fY + Dest->Get_Info().fCY < Sour->Get_Info().fY + Sour->Get_Info().fCY;
}