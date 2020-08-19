#ifndef __LIST_TEMPLATE_H__
#define __LIST_TEMPLATE_H__

template<class TYPE> class CTList {

public:
	CTList(int InitialSize, int Inc)
	{
		m_RecSize = sizeof(TYPE);
		m_IncPage = Inc;
		m_Count = 0;
		m_MaxCount = InitialSize;
		m_pList = NULL;

		if (m_MaxCount == 0)
			m_MaxCount = 1;

		/*if (m_IncPage == 0)
			m_MaxCount = 1;*/

		m_pList = new TYPE[m_MaxCount];
		//delete m_pList;
	}

	~CTList()
	{
		Free();
	}

	void Free()
	{
		if (m_pList != NULL) {
			delete m_pList; 
			m_pList = NULL; 
		}

		m_pList = NULL;
		m_Count = 0;
		//	nRecSize	= 0;	
	};


	TYPE* GetAt(int i)
	{
		if (i < m_Count && i >= 0)
			return (TYPE*)(&m_pList[i]);

		return NULL;
	}
	TYPE* GetLast()
	{
		return (TYPE*)(&m_pList[m_Count - 1]);
	}


	bool Add(TYPE* pItem)
	{
		TYPE	*pList;


		if (m_Count >= m_MaxCount)
		{
			if (m_IncPage == 0)
				return FALSE;

			m_MaxCount += m_IncPage;
			pList = new TYPE[m_MaxCount];

			if (!pList)
				return false;

			memcpy(pList, m_pList, m_Count * sizeof(TYPE));

			delete m_pList;

			m_pList = pList;

		}

		m_pList[m_Count] = *pItem;

		m_Count++;

		return true;
	}


	bool SetAt(int i, TYPE* pItem)
	{
		if (i > m_Count || i < 0)
			return false;

		m_pList[i] = *pItem;

		return true;
	}

	bool RemoveAt(int i)
	{
		if (i > m_Count || i < 0)
			return false;

		if (i == m_Count - 1)
		{
			m_Count -= 1;
			return true;
		}

		memcpy(&m_pList[i], &m_pList[i + 1], sizeof(TYPE)*(m_Count - i - 1));
		m_Count = m_Count - 1;
		return true;
	}

	void	CopyArray(TYPE *Array, int ArraySize)
	{
		if (m_MaxCount < ArraySize)
		{
			m_MaxCount = ArraySize;
			delete m_pList;
			m_pList = new TYPE[ArraySize];
		}

		memcpy(m_pList, Array, sizeof(TYPE)*ArraySize);
		m_Count = ArraySize;
	}

	inline void Reset() { m_Count = 0; };
	inline int	GetCount()const { return m_Count; };
	inline void	GetCountPtr(int *CountPtr) { CountPtr = &m_Count; }
	inline BOOL	IsEmpty() { return (m_Count == 0); };
	inline TYPE* GetDataPtr() { return m_pList; };
	inline void DecrementSize(int DecrementValue) { m_Count -= DecrementValue; };

	void	IncrementSize(int IncrementValue)
	{
		TYPE	*pList;

		if (m_Count + IncrementValue > m_MaxCount)
		{
			m_MaxCount += IncrementValue;
			pList = new TYPE[m_MaxCount];

			memcpy(pList, m_pList, m_Count * sizeof(TYPE));

			delete m_pList;

			m_pList = pList;

			m_Count += IncrementValue;
		}
		else
			m_Count += IncrementValue;
	}

	void	Append(TYPE *Array, int ArraySize)
	{
		TYPE	*pList;

		if (m_MaxCount < ArraySize + m_Count)
		{
			pList = new TYPE[m_Count];

			memcpy(pList, m_pList, sizeof(TYPE) * m_Count);
			delete m_pList;
			m_pList = new TYPE[ArraySize + m_Count];
			memcpy(m_pList, pList, sizeof(TYPE) * m_Count);
			delete pList;
			m_MaxCount = ArraySize + m_Count;
		}

		memcpy(&m_pList[m_Count], Array, sizeof(TYPE) * ArraySize);
		m_Count += ArraySize;
	}
	void Copy(CTList *OList)
	{
		this->m_Count = OList->m_Count;
		this->m_RecSize = OList->m_RecSize;
		this->m_MaxCount = OList->m_MaxCount;
		this->m_IncPage = OList->m_IncPage;

		this->m_pList = new TYPE[this->m_MaxCount];

		memcpy(this->m_pList, OList->m_pList, this->m_Count * sizeof(TYPE));
	}

	CTList *Clone()
	{
		return new CTList(*this);
	}

private:


	TYPE	*m_pList;		// pointer to data items

	int		m_Count,		// items count
			m_RecSize,	// item size
			m_MaxCount;	// max count for items to add 
	int		m_IncPage;


};
typedef CTList<int> CIntList;
//typedef CTList<TOKEN_STR>				CTokenList;
//typedef CTList<CANDIDATE_STR>			CCandidateList;
//typedef CTList<DERIVATIVE_STR>			CDerivativeList;
//typedef CTList<EXAMPLE_STR>				CExampleList;
//typedef CTList<EXPRESSION_EXAMPLE_STR>	CExpExampleList;
//typedef CTList<RESPONSE_VALUSE_STR>		CResponseList;
//typedef CTList<DATE_VALUE_STR>			CDateValueList;
#endif  //__LIST_TEMPLATE_H__